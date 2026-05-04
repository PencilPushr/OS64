#ifndef BOOTLOADER_FONTS_H
#define BOOTLOADER_FONTS_H

#include <stdint.h>
#include <stddef.h>

#define PSF2_MAGIC_BYTES { 0x72, 0xB5, 0x4A, 0x86 }

#define PSF2_FLAG_UNICODE   0x01       // Font has Unicode mapping table

// Reasonable upper bounds — reject obviously broken headers early.
#define PSF2_MAX_WIDTH          32u
#define PSF2_MAX_HEIGHT         64u


typedef struct __attribute__((packed)) PSF2_Header_t
{
    uint8_t  MagicBytes[4];
    uint32_t Version;
    uint32_t HeaderSz;
    uint32_t Flags;
    uint32_t Length;    // Number of glyphs in font
    uint32_t GlyphSz;   // Size of each glyph
    uint32_t Height;
    uint32_t Width;

} PSF2_Header;

/**
 * @brief Format agnostic structure for font rendering:
 * Any font backend (PSF2, VGA built-in, future formats) populates
 * this struct.  Renderers only depend on Font — never on a specific
 * file-format header.
 * 
 */
typedef struct Font_t
{
    const uint8_t *GlyphData;       /* pointer to first glyph bitmap   */
    const uint8_t *UnicodeTable;    /* NULL when absent                 */
    uint32_t       Width;           /* glyph width  in pixels           */
    uint32_t       Height;          /* glyph height in pixels           */
    uint32_t       BytesPerGlyph;
    uint32_t       BytesPerRow;     /* (Width + 7) / 8  — precomputed  */
    uint32_t       NumGlyphs;

} Font;

#include "status.h"
 
GLOBAL_STATUS FontInitDefault(Font *OutFont);
GLOBAL_STATUS FontInitPSF2(Font *OutFont, const void *pData, size_t Size);


// Direct access to the built-in VGA 8x16 font data (256 glyphs × 16 bytes)
extern const uint8_t vga_font_8x16[256 * 16];
 
#define VGA_FONT_WIDTH          8
#define VGA_FONT_HEIGHT         16
#define VGA_FONT_BYTES_PER_ROW  1
#define VGA_FONT_BYTES_PER_GLYPH (VGA_FONT_BYTES_PER_ROW * VGA_FONT_HEIGHT)
#define VGA_FONT_NUM_GLYPHS     256


#endif // BOOTLOADER_FONTS_H