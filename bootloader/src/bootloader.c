#include "bootloader/file.h"
#include "bootloader/graphics.h"
#include "bootloader/mem.h"
#include "bootloader/elfldr.h"
#include "common/status_codes.h"

extern GLOBAL_STATUS
FillScreen(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN int Colour
);

typedef int (*KERNEL_ENTRY)(BOOT_INFO* pBootInfo);

EFI_STATUS
efi_main(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    UNREFERENCED_PARAMETER(SystemTable);

    uefi_call_wrapper( ST->ConOut->ClearScreen, 1, ST->ConOut );
    Print( L"Hello from OS64 bootloader\r\n" );

    EFI_STATUS         Status = EFI_SUCCESS;
    BOOTLOADER_CONTEXT BootloaderContext = { .ImageHandle = ImageHandle };
    BOOT_INFO*         pBootInfo = NULL;

    pBootInfo = (BOOT_INFO*)AllocateZeroPool( sizeof( *pBootInfo ) );
    if( pBootInfo == NULL )
    {
        Print( L"[EFI_OUT_OF_RESOURCES] Failed to allocate boot info\n" );
        goto spinlock;
    }

    Status = BlEfiInitialiseLoadedImage( &BootloaderContext );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get loaded image.\n", Status );
        goto spinlock;
    }

    Status = BlFsInitialiseFileSystem( &BootloaderContext );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get root volume handle\n", Status );
        goto spinlock;
    }

    Status = BlGfxInitialiseFrameBuffer( &pBootInfo->FrameBufferDescriptor );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to initialise framebuffer\n", Status );
        goto spinlock;
    }

    EFI_FILE_HANDLE KernelFileHandle = NULL;

    Status = BlFsOpenFile(
        BootloaderContext.BootVolume.RootDirectory,
        L"\\efi\\os64\\kernel.elf",
        EFI_FILE_MODE_READ,
        0,
        &KernelFileHandle
    );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to open kernel.elf\n", Status );
        goto spinlock;
    }

    VOID*  KernelFileBuffer     = NULL;
    UINT64 KernelFileBufferSize = 0;

    Status = BlFsReadFullFile(
        KernelFileHandle,
        &KernelFileBuffer,
        &KernelFileBufferSize
    );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to read kernel.elf\n", Status );
        goto spinlock;
    }

    Print( L"Read kernel.elf [%lx bytes]\n", KernelFileBufferSize );

    /*
     * IMPORTANT: load the ELF before taking the final memory map.
     * BlElfLoadImage() calls AllocatePages(), and any memory-map mutation
     * invalidates a previously returned ExitBootServices map key.
     */
    UINT64 KernelEntryAddress = 0;

    Status = BlElfLoadImage(
        KernelFileBuffer,
        KernelFileBufferSize,
        &KernelEntryAddress
    );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to load kernel ELF\n", Status );
        goto spinlock;
    }

    Print( L"Kernel loaded. Entry point = 0x%lx\n", KernelEntryAddress );

    /* The file image is no longer needed after the PT_LOAD segments are copied. */
    if( KernelFileHandle != NULL )
    {
        uefi_call_wrapper( KernelFileHandle->Close, 1, KernelFileHandle );
        KernelFileHandle = NULL;
    }

    if( KernelFileBuffer != NULL )
    {
        FreePool( KernelFileBuffer );
        KernelFileBuffer = NULL;
    }

    /*
     * Take the final memory map and immediately try ExitBootServices().
     * EFI_INVALID_PARAMETER here usually means the map key became stale.
     * Reacquire the map and retry; importantly, there is no Print() or other
     * boot-service activity between a successful GetMemoryMap() and its
     * matching ExitBootServices() call.
     */
    for( UINTN Attempt = 0; Attempt < 3; ++Attempt )
    {
        if( pBootInfo->MemoryMap.Descriptor != NULL )
        {
            FreePool( pBootInfo->MemoryMap.Descriptor );
            pBootInfo->MemoryMap.Descriptor = NULL;
        }

        Status = BlMmGetMemoryMap(
            &pBootInfo->MemoryMap.MapSize,
            (EFI_MEMORY_DESCRIPTOR**)&pBootInfo->MemoryMap.Descriptor,
            &pBootInfo->MemoryMap.Key,
            &pBootInfo->MemoryMap.DescriptorSize,
            &pBootInfo->MemoryMap.Version
        );
        if( EFI_ERROR( Status ) )
        {
            Print( L"[%r] Failed to get final memory map\n", Status );
            goto spinlock;
        }

        Status = uefi_call_wrapper(
            BS->ExitBootServices,
            2,
            ImageHandle,
            pBootInfo->MemoryMap.Key
        );

        if( !EFI_ERROR( Status ) )
        {
            break;
        }

        if( Status != EFI_INVALID_PARAMETER )
        {
            Print( L"[%r] ExitBootServices failed\n", Status );
            goto spinlock;
        }
    }

    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] ExitBootServices failed after retries\n", Status );
        goto spinlock;
    }

    /*
     * UEFI boot services are gone from here onward.  Do not Print(),
     * AllocatePool(), FreePool(), use filesystem handles, etc.
     */
    KERNEL_ENTRY KernelEntry = (KERNEL_ENTRY)(UINTN)KernelEntryAddress;

    int KernelReturn = KernelEntry( pBootInfo );

    /* A kernel should not return.  Halt if it does. */
    UNREFERENCED_PARAMETER( KernelReturn );
    for( ;; )
    {
        __asm__ volatile ( "cli; hlt" );
    }

spinlock:
    Print( L"Bootloader halted\n" );
    for( ;; )
    {
        __asm__ volatile ( "pause" );
    }

    return EFI_SUCCESS;
}
