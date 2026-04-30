#include "bootloader/file.h"
#include "bootloader/graphics.h"
#include "bootloader/mem.h"
#include "bootloader/fonts.h"
#include "bootloader/elfldr.h"

EFI_STATUS
efi_main(
    IN EFI_HANDLE ImageHandle, 
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    UNREFERENCED_PARAMETER(SystemTable);

    // Don't actually have to call this as this gets called in _entry 
    // InitializeLib( ImageHandle, SystemTable );

    uefi_call_wrapper( ST->ConOut->ClearScreen, 1, ST->ConOut );
    Print(L"Hello from OS64 bootloader\r\n");

    // When working in less-forgiving enviroments always zero-intialise, 
    // this avoids issues of accidentally overwriting valid memory/values and causing issues.

    EFI_STATUS         Status = EFI_SUCCESS;
    BOOTLOADER_CONTEXT BootloaderContext = { .ImageHandle = ImageHandle };
    BOOT_INFO*         pBootInfo = NULL;

    pBootInfo = (BOOT_INFO*)AllocateZeroPool( sizeof( *pBootInfo ) );
    if( pBootInfo == NULL )
    {
        Print( L"[EFI_OUT_OF_RESOURCES] Failed to allocate for boot info\n" );
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

    // Getting the kernel file

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
        Print( L"[%r] Failed to open file\n", Status );
        goto spinlock;
    }

    VOID*  KernelFileBuffer = NULL;
    UINT64 KernelFileBufferSize; 
    Status = BlFsReadFullFile( KernelFileHandle, &KernelFileBuffer, &KernelFileBufferSize );
    if( EFI_ERROR( Status ) ) 
    {
        Print( L"[%r] Failed to read kernel file\n", Status );
        goto spinlock;
    }

    Print( L"Read kernel.elf [%lx]\n", KernelFileBufferSize );

    Status = BlMmGetMemoryMap( 
        &pBootInfo->MemoryMap.MapSize,
        (EFI_MEMORY_DESCRIPTOR**)&pBootInfo->MemoryMap.Descriptor,
        &pBootInfo->MemoryMap.Key,
        &pBootInfo->MemoryMap.DescriptorSize,
        &pBootInfo->MemoryMap.Version
    );
    if( EFI_ERROR( Status ) )
    {
        Print( L"[%r] Failed to get memory map\n", Status );
        goto spinlock;
    }

    Print( L"Memory map key: %lx\n", pBootInfo->MemoryMap.Key );

    BlElfLoadImage( KernelFileBuffer, KernelFileBufferSize );

spinlock: 
    Print( L"Made it to spinlock\n" );
    while( 1 )
    {
        continue;
    }

    return EFI_SUCCESS;
}