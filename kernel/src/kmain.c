#include "common/bootinfo.h"
#include "graphics/display.h"
#include "graphics/displays/display_lfb.h"
#include <stddef.h>

__attribute__((section(".text.kernel_main")))
int 
kmain(
    BOOT_INFO* pBootInfo
)
{

    // This is kind of useless, while we don't have printing. We can use it for serial debugging sooner than I can get the graphics going
    if ( pBootInfo == NULL )
        goto pause;

    GLOBAL_STATUS Status = KeDpInitLFB( &pBootInfo->FrameBufferDescriptor );

    if ( FAILED( Status ) )
        goto pause;

    DisplayDevice *Display = KeDpGetDevice();

    if ( Display == NULL )
        goto pause;

pause:

    while( 1 )
        __asm__ volatile ("pause");

    return 0;
}