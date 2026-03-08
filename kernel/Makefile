include $(ROOT_DIR)/build/common.mk
include $(ROOT_DIR)/build/$(HOST).mk

KERNEL_SRCS := kmain.c
KERNEL_OBJS := $(addprefix $(KERNEL_OUT_DIR)/,$(notdir $(KERNEL_SRCS:.c=.o)))

.PHONY: all clean

all: $(KERNEL_ELF)

$(KERNEL_OUT_DIR):
	$(MKDIR_P) "$(KERNEL_OUT_DIR)"

$(KERNEL_OUT_DIR)/%.o: %.c | $(KERNEL_OUT_DIR)
	$(KERNEL_CC) $(KERNEL_CFLAGS_COMMON) $(KERNEL_CFLAGS_HOST) -c $< -o $@

$(KERNEL_ELF): $(KERNEL_OBJS) linker.ld | $(KERNEL_OUT_DIR)
	$(KERNEL_LD) $(KERNEL_LDFLAGS_COMMON) $(KERNEL_LDFLAGS_HOST) -T linker.ld -o $@ $(KERNEL_OBJS)

clean:
	$(RM_RF) "$(KERNEL_OUT_DIR)"