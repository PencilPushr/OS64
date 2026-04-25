#ifndef BOOTLOADER_FONTS_H
#define BOOTLOADER_FONTS_H

#include "boot.h"

#define PSF2_MAGIC_BYTES_LE 0x864AB572u
#define PSF2_MAGIC_BYTES_BE 0x72B54A86u

typedef struct PSF2_t
{
    uint8_t  MagicBytes[4];
    uint32_t Version;
    uint32_t HeaderSz;
    uint32_t Flags;
    uint32_t Length;
    uint32_t GlyphSz;
    uint32_t Height;
    uint32_t Width;

} PSF2;

#endif // BOOTLOADER_FONTS_H