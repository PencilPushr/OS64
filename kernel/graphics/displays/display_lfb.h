// kernel/display_lfb.h

#ifndef KERNEL_DISPLAY_LFB_H
#define KERNEL_DISPLAY_LFB_H

#include "common/bootinfo.h"
#include "common/status_codes.h"

// This is shamelessly an efifb ( linux ) / bootvid.dll ( ms ) rip-off 

// Expose the one point of truth for initialising display_lfb, kind of like pimpl, 
// all the functions are closed off in .c, only exposing the init func here
GLOBAL_STATUS
KeDpInitLFB( 
    GOP_FRAMEBUFFER_DESCRIPTOR * pFrameBufferDesc
);

#endif // KERNEL_DISPLAY_LFB_H