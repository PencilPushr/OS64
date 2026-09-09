#include "common/bootinfo.h"
#include "common/font.h"
#include "graphics/display.h"
#include "graphics/displays/display_lfb.h"
#include "graphics/graphics.h"
#include "graphics/kconsole.h"

#include <stddef.h>

/*
 * Keep these out of the tiny early kernel stack.  Console contains the fixed
 * backing buffer and is therefore intentionally static storage.
 */
static Font g_KernelFont;
static Console g_KernelConsole;

__attribute__((section(".text.kernel_main")))
int
kmain(
    BOOT_INFO *pBootInfo
)
{
    if ( pBootInfo == NULL )
        goto pause;

    GLOBAL_STATUS Status =
        KeDpInitLFB( &pBootInfo->FrameBufferDescriptor );

    if ( FAILED( Status ) )
        goto pause;

    if ( KeDpGetDevice() == NULL )
        goto pause;

    Status = FontInitDefault( &g_KernelFont );

    if ( FAILED( Status ) )
        goto pause;

    /* First direct glyph test: proves Font -> KeGfx -> DisplayOps -> LFB. */
    Status = KeGfxFillScreen( 0x00101010u );

    if ( FAILED( Status ) )
        goto pause;

    Status = KeGfxDrawGlyph(
        &g_KernelFont,
        'A',
        16,
        16,
        0x00FFFFFFu,
        0x00101010u
    );

    if ( FAILED( Status ) )
        goto pause;

    /*
     * Console starts one glyph row lower so the standalone 'A' remains
     * visible as a diagnostic while bringing up the console.
     */
    Status = KeConsoleInit(
        &g_KernelConsole,
        &g_KernelFont,
        16,
        48,
        0x00FFFFFFu,
        0x00101010u
    );

    if ( FAILED( Status ) )
        goto pause;

    Status = KeConsoleWrite(
        &g_KernelConsole,
        "OS64 framebuffer console online.\n"
        "Glyph rendering: OK\n"
    );

    if ( FAILED( Status ) )
        goto pause;


pause:
    while ( 1 )
        __asm__ volatile ("pause");

    return 0;
}
