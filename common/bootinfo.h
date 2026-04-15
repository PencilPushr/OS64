// common/bootinfo.h
// Boot information structure passed from bootloader to kernel
//
// This is the clean interface between bootloader and kernel.
// The kernel doesn't need to know if it was loaded by UEFI or legacy BIOS -
// it just receives this structure with all the information it needs.
#pragma once

#include <stdint.h>