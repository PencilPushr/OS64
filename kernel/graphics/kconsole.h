#ifndef KERNEL_CONSOLE_H
#define KERNEL_CONSOLE_H

#include <stdint.h>
#include "common/font.h"

#define CONSOLE_MAX_COLS 200
#define CONSOLE_MAX_ROWS 100

typedef struct ConsoleCell_t
{
    uint8_t Char;
    uint8_t Fg;
    uint8_t Bg;
    uint8_t Flags;

} ConsoleCell;

typedef struct Console_t
{
    Font* font;

    // Pixel pos of console in FrameBuffer
    uint32_t OriginX;
    uint32_t OriginY;

    // Char dimensions
    uint32_t Cols;
    uint32_t Rows;

    // Cursor pos
    uint32_t CursorX;
    uint32_t CursorY;

    uint32_t FgColour;
    uint32_t BgColour;

    uint32_t Flags;

    ConsoleCell Buffer[ CONSOLE_MAX_ROWS * CONSOLE_MAX_COLS ];
} Console;


#endif // KERNEL_CONSOLE_H