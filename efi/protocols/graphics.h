// efi/protocols/graphics.h
// Graphics Output Protocol (GOP) from UEFI Specification 2.10, Section 12.9
//
// GOP replaces the older UGA (Universal Graphics Adapter) protocol.
// It provides a simple way to get a framebuffer for graphics output.
#pragma once

#include "../types.h"

// Forward declaration
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL;

//=============================================================================
// GOP GUID
// 9042a9de-23dc-4a38-96fb-7aded080516a
//=============================================================================

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
    EFI_GUID_VALUE(0x9042a9de, 0x23dc, 0x4a38, \
                   0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a)