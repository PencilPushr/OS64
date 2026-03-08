#include "../include/filesystem.h"

EFI_STATUS         FILE_SYSTEM_STATUS;

static EFI_GUID                   __FileSystemProtoclGUID__ = SIMPLE_FILE_SYSTEM_PROTOCOL;
//static CHAR16*                    CurrentDirectoryString;
static EFI_FILE_PROTOCOL*         CurrentDirectory;
//static EFI_HANDLE*                CurrentFileSystemHandle;
static EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;

EFI_STATUS
BlEfiInitFileSystem(
    VOID
)
{
    EFI_GUID LoadedImageProtocolGUID = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    FILE_SYSTEM_STATUS = gBS->HandleProtocol( gImageHandle, &LoadedImageProtocolGUID, ( VOID** )&LoadedImage );

    if( EFI_ERROR( FILE_SYSTEM_STATUS ) )
    {
        Print( L"[%r] Failed to get loaded image protocol\n", FILE_SYSTEM_STATUS );
        return FILE_SYSTEM_STATUS;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
BlGetRootDirectory(
    OUT OPTIONAL EFI_FILE_PROTOCOL** Directory
)
{
    if( !LoadedImage )
    {
        EFI_STATUS LastError = BlGetLastFileError( );
        Print( L"[%r] Loaded image was null, did you initialise file system?\n", LastError );
        return LastError;
    }

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileProtocol;
    FILE_SYSTEM_STATUS = gBS->HandleProtocol( LoadedImage->DeviceHandle, &__FileSystemProtoclGUID__, ( VOID** )&FileProtocol );

    if( EFI_ERROR( FILE_SYSTEM_STATUS ) )
    {
        Print( L"[%r] Could not get file protocol\n", FILE_SYSTEM_STATUS );
        return FILE_SYSTEM_STATUS;
    }

    EFI_FILE_PROTOCOL* Root;
    FILE_SYSTEM_STATUS = FileProtocol->OpenVolume( FileProtocol, &Root );

    if( EFI_ERROR( FILE_SYSTEM_STATUS ) )
    {
        Print( L"[%r] Could not open the root directory\n", FILE_SYSTEM_STATUS );
        return FILE_SYSTEM_STATUS;
    }

    CurrentDirectory = Root;

    if( Directory )
    {
        *Directory = Root;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
BlGetLastFileError(
    VOID
)
{
    return FILE_SYSTEM_STATUS;
}


EFI_STATUS
BlListDirectoryRecursive(
    IN EFI_FILE_PROTOCOL* Directory,
    IN UINT64 Depth
)
{
    if( Directory == NULL )
    {
        return FALSE;
    }

    // reset position so we read from the start
    FILE_SYSTEM_STATUS = Directory->SetPosition( Directory, 0 );
    if( EFI_ERROR( FILE_SYSTEM_STATUS ) )
    {
        //DBG_ERROR( L"Failed to SetPosition on directory\n" );
        return FALSE;
    }

    // allocate a buffer for EFI_FILE_INFO. Sketchy as won't work for longer names.
    UINT64 BufferSize = 0x128;
    EFI_FILE_INFO* FileInfo = AllocateZeroPool( BufferSize );
    if( !FileInfo )
    {
        //probably out of resources?
        FILE_SYSTEM_STATUS = EFI_OUT_OF_RESOURCES;
        return FALSE;
    }

    // Keep reading entries until we reach the end of the directory
    while( TRUE )
    {
        UINT64 Size = BufferSize;
        FILE_SYSTEM_STATUS = Directory->Read( Directory, &Size, FileInfo );
        if( EFI_ERROR( FILE_SYSTEM_STATUS ) )
        {
            Print( L"[%r] Failed to read directory(s)'\n", FILE_SYSTEM_STATUS, FileInfo->FileName );
            FreePool( FileInfo );
            return FALSE;
        }

        if( Size == 0 )
        {
            //no more to read
            break;
        }

        // skip the '.' and '..' at the start of directories to avoid infinite recursion
        if( ( StrCmp( FileInfo->FileName, L"." ) == 0 ) ||
            ( StrCmp( FileInfo->FileName, L".." ) == 0 ) )
        {
            continue;
        }

        // just add indentation
        for( UINT64 i = 0; i < Depth; i++ )
        {
            Print( L"  " );
        }

        //check if its directory and list its contents
        if( FileInfo->Attribute & EFI_FILE_DIRECTORY )
        {
            Print( L"<DIR> %s\n", FileInfo->FileName );

            // try to open the subdirectory
            EFI_FILE_PROTOCOL* SubDirectory = NULL;
            FILE_SYSTEM_STATUS = Directory->Open(
                Directory,
                &SubDirectory,
                FileInfo->FileName,
                EFI_FILE_MODE_READ,
                0
            );

            if( EFI_ERROR( FILE_SYSTEM_STATUS ) && !SubDirectory )
            {
                Print( L"[%r] Cannot open subdirectory %s\n", FILE_SYSTEM_STATUS, FileInfo->FileName );
                FreePool( FileInfo );
                return FALSE;
            }

            // recursive call
            BlListDirectoryRecursive( SubDirectory, Depth + 1 );
            // make sure to close
            SubDirectory->Close( SubDirectory );
        }
        else
        {
            //if its a file then display contents
            Print( L"%-6d  %s\n", FileInfo->FileSize, FileInfo->FileName );
        }
    }

    FreePool( FileInfo );
    return TRUE;
}


EFI_STATUS
BlListAllFiles(
    VOID
)
{
    if( !CurrentDirectory )
    {
        //try get current directory
        BlGetRootDirectory( NULL );

        //well that is just nice
        if( !CurrentDirectory )
        {
            return FALSE;
        }
    }

    Print( L"\nDirectory listing -> \n" );
    return BlListDirectoryRecursive( CurrentDirectory, 0 );
}