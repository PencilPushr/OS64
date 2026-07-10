#include "common/bootinfo.h"
#include "graphics/"

__attribute__((section(".text.kernel_main")))
int 
kmain(
    BOOT_INFO* pBootInfo
)
{
    KeDpInitLFB(&pBootInfo->FrameBufferDescriptor);

    DisplayDevice *Display = KeDpGetDevice();

    return 0;
}