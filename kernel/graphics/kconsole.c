#include "graphics/kconsole.h"

#include <stddef.h>

#include "common/status_codes.h"
#include "common/string.h"
#include "graphics/display.h"
#include "graphics/graphics.h"

static inline uint32_t
KeConsoleCellIndex(
    const Console *pConsole,
    uint32_t Col,
    uint32_t Row
)
{
    return Row * pConsole->Cols + Col;
}

static void
KeConsoleResetCell(
    ConsoleCell *pCell
)
{
    pCell->Char  = ' ';
    pCell->Fg    = 0;
    pCell->Bg    = 0;
    pCell->Flags = 0;
}

static GLOBAL_STATUS
KeConsoleDrawCell(
    Console *pConsole,
    uint32_t Col,
    uint32_t Row
)
{
    if ( Col >= pConsole->Cols || Row >= pConsole->Rows )
        return STATUS_INVALID_ARGUMENT;

    const ConsoleCell *Cell =
        &pConsole->Buffer[ KeConsoleCellIndex( pConsole, Col, Row ) ];

    const uint32_t PixelX = pConsole->OriginX + Col * pConsole->font->Width;
    const uint32_t PixelY = pConsole->OriginY + Row * pConsole->font->Height;

    return KeGfxDrawGlyph(
        pConsole->font,
        Cell->Char,
        PixelX,
        PixelY,
        pConsole->FgColour,
        pConsole->BgColour
    );
}

static GLOBAL_STATUS
KeConsoleRedraw(
    Console *pConsole
)
{
    for ( uint32_t Row = 0; Row < pConsole->Rows; ++Row )
    {
        for ( uint32_t Col = 0; Col < pConsole->Cols; ++Col )
        {
            GLOBAL_STATUS Status = KeConsoleDrawCell( pConsole, Col, Row );

            if ( FAILED( Status ) )
                return Status;
        }
    }

    return OK;
}

static GLOBAL_STATUS
KeConsoleAdvanceLine(
    Console *pConsole
)
{
    pConsole->CursorX = 0;
    ++pConsole->CursorY;

    if ( pConsole->CursorY >= pConsole->Rows )
        return KeConsoleScroll( pConsole );

    return OK;
}

GLOBAL_STATUS
KeConsoleInit(
    Console *pConsole,
    Font *pFont,
    uint32_t OriginX,
    uint32_t OriginY,
    uint32_t FgColour,
    uint32_t BgColour
)
{
    if ( pConsole == NULL ||
         pFont == NULL ||
         pFont->GlyphData == NULL ||
         pFont->Width == 0 ||
         pFont->Height == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    DisplayDevice *Device = KeDpGetDevice();

    if ( Device == NULL || OriginX >= Device->Width || OriginY >= Device->Height )
        return STATUS_INVALID_ARGUMENT;

    uint32_t Cols = ( Device->Width  - OriginX ) / pFont->Width;
    uint32_t Rows = ( Device->Height - OriginY ) / pFont->Height;

    if ( Cols == 0 || Rows == 0 )
        return STATUS_INVALID_ARGUMENT;

    if ( Cols > CONSOLE_MAX_COLS )
        Cols = CONSOLE_MAX_COLS;

    if ( Rows > CONSOLE_MAX_ROWS )
        Rows = CONSOLE_MAX_ROWS;

    pConsole->font       = pFont;
    pConsole->OriginX    = OriginX;
    pConsole->OriginY    = OriginY;
    pConsole->Cols       = Cols;
    pConsole->Rows       = Rows;
    pConsole->CursorX    = 0;
    pConsole->CursorY    = 0;
    pConsole->FgColour   = FgColour;
    pConsole->BgColour   = BgColour;
    pConsole->Flags      = 0;

    return KeConsoleClear( pConsole );
}

GLOBAL_STATUS
KeConsoleClear(
    Console *pConsole
)
{
    if ( pConsole == NULL || pConsole->font == NULL ||
         pConsole->Cols == 0 || pConsole->Rows == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    const uint32_t CellCount = pConsole->Cols * pConsole->Rows;

    for ( uint32_t Index = 0; Index < CellCount; ++Index )
        KeConsoleResetCell( &pConsole->Buffer[ Index ] );

    pConsole->CursorX = 0;
    pConsole->CursorY = 0;

    return KeGfxDrawRect(
        pConsole->OriginX,
        pConsole->OriginY,
        pConsole->Cols * pConsole->font->Width,
        pConsole->Rows * pConsole->font->Height,
        pConsole->BgColour
    );
}

GLOBAL_STATUS
KeConsoleScroll(
    Console *pConsole
)
{
    if ( pConsole == NULL || pConsole->font == NULL ||
         pConsole->Cols == 0 || pConsole->Rows == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    if ( pConsole->Rows > 1 )
    {
        const size_t RowSize =
            (size_t)pConsole->Cols * sizeof( ConsoleCell );

        memmove(
            &pConsole->Buffer[ 0 ],
            &pConsole->Buffer[ pConsole->Cols ],
            (size_t)( pConsole->Rows - 1u ) * RowSize
        );
    }

    const uint32_t LastRowStart =
        ( pConsole->Rows - 1u ) * pConsole->Cols;

    for ( uint32_t Col = 0; Col < pConsole->Cols; ++Col )
        KeConsoleResetCell( &pConsole->Buffer[ LastRowStart + Col ] );

    pConsole->CursorX = 0;
    pConsole->CursorY = pConsole->Rows - 1u;

    /*
     * Correctness-first implementation: the text model is authoritative,
     * so scrolling shifts cells and redraws the visible console.  A future
     * CopyRect/bitblt path can optimize this without changing console logic.
     */
    return KeConsoleRedraw( pConsole );
}

GLOBAL_STATUS
KeConsolePutChar(
    Console *pConsole,
    char Character
)
{
    if ( pConsole == NULL || pConsole->font == NULL ||
         pConsole->Cols == 0 || pConsole->Rows == 0 )
    {
        return STATUS_INVALID_ARGUMENT;
    }

    switch ( Character )
    {
        case '\n':
            return KeConsoleAdvanceLine( pConsole );

        case '\r':
            pConsole->CursorX = 0;
            return OK;

        case '\t':
        {
            const uint32_t Spaces =
                CONSOLE_TAB_WIDTH - ( pConsole->CursorX % CONSOLE_TAB_WIDTH );

            for ( uint32_t i = 0; i < Spaces; ++i )
            {
                GLOBAL_STATUS Status = KeConsolePutChar( pConsole, ' ' );

                if ( FAILED( Status ) )
                    return Status;
            }

            return OK;
        }

        case '\b':
        {
            if ( pConsole->CursorX == 0 )
                return OK;

            --pConsole->CursorX;

            ConsoleCell *Cell = &pConsole->Buffer[
                KeConsoleCellIndex(
                    pConsole,
                    pConsole->CursorX,
                    pConsole->CursorY
                )
            ];

            KeConsoleResetCell( Cell );

            return KeConsoleDrawCell(
                pConsole,
                pConsole->CursorX,
                pConsole->CursorY
            );
        }

        default:
            break;
    }

    ConsoleCell *Cell = &pConsole->Buffer[
        KeConsoleCellIndex(
            pConsole,
            pConsole->CursorX,
            pConsole->CursorY
        )
    ];

    Cell->Char = (uint8_t)Character;

    GLOBAL_STATUS Status = KeConsoleDrawCell(
        pConsole,
        pConsole->CursorX,
        pConsole->CursorY
    );

    if ( FAILED( Status ) )
        return Status;

    ++pConsole->CursorX;

    if ( pConsole->CursorX >= pConsole->Cols )
        return KeConsoleAdvanceLine( pConsole );

    return OK;
}

GLOBAL_STATUS
KeConsoleWrite(
    Console *pConsole,
    const char *String
)
{
    if ( pConsole == NULL || String == NULL )
        return STATUS_INVALID_ARGUMENT;

    while ( *String != '\0' )
    {
        GLOBAL_STATUS Status = KeConsolePutChar( pConsole, *String++ );

        if ( FAILED( Status ) )
            return Status;
    }

    return OK;
}
