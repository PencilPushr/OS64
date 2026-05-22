#ifndef KERNEL_GRAPHICS_H
#define KERNEL_GRAPHICS_H



GLOBAL_STATUS
DrawRect(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN uint32_t x,
    IN uint32_t y,
    IN uint32_t w,
    IN uint32_t h,
    IN uint32_t Colour
);

GLOBAL_STATUS
FillScreen(
    IN GOP_FRAMEBUFFER_DESCRIPTOR* pFrameBufferDesc,
    IN uint32_t Colour
);



#endif // KERNEL_GRAPHICS_H