#ifndef KERNEL_CONSOLE_H
#define KERNEL_CONSOLE_H

#include <stdint.h>

#include "common/font.h"
#include "common/status.h"

#define CONSOLE_MAX_COLS 200u
#define CONSOLE_MAX_ROWS 100u
#define CONSOLE_TAB_WIDTH 4u

typedef struct ConsoleCell_t
{
    uint8_t Char;

    /*
     * Reserved for indexed/palette colours and cell attributes.
     * The first console milestone uses Console::FgColour/BgColour globally,
     * while preserving the compact four-byte cell layout already chosen.
     */
    uint8_t Fg;
    uint8_t Bg;
    uint8_t Flags;

} ConsoleCell;

typedef struct Console_t
{
    Font *font;

    /* Pixel position of the console's top-left corner. */
    uint32_t OriginX;
    uint32_t OriginY;

    /* Console dimensions measured in character cells. */
    uint32_t Cols;
    uint32_t Rows;

    /* Cursor position measured in character cells. */
    uint32_t CursorX;
    uint32_t CursorY;

    /* Canonical XRGB colours used by KeGfx. */
    uint32_t FgColour;
    uint32_t BgColour;

    uint32_t Flags;

    ConsoleCell Buffer[ CONSOLE_MAX_ROWS * CONSOLE_MAX_COLS ];
} Console;

/*
 * Initialize a console that occupies the remainder of the active display
 * from (OriginX, OriginY).  Cols/Rows are derived from the font dimensions
 * and clamped to CONSOLE_MAX_*.
 */
GLOBAL_STATUS
KeConsoleInit(
    Console *pConsole,
    Font *pFont,
    uint32_t OriginX,
    uint32_t OriginY,
    uint32_t FgColour,
    uint32_t BgColour
);

GLOBAL_STATUS
KeConsoleClear(
    Console *pConsole
);

GLOBAL_STATUS
KeConsolePutChar(
    Console *pConsole,
    char Character
);

GLOBAL_STATUS
KeConsoleWrite(
    Console *pConsole,
    const char *String
);

GLOBAL_STATUS
KeConsoleScroll(
    Console *pConsole
);

#endif // KERNEL_CONSOLE_H
