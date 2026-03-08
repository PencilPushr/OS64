ROOT_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

HOST ?= auto
ARCH ?= x64
CONFIG ?= debug

ifeq ($(HOST),auto)
  ifeq ($(OS),Windows_NT)
    HOST := windows
  else
    HOST := linux
  endif
endif

.PHONY: all build bootstrap run clean info kernel bootloader

ifeq ($(HOST),windows)

all: build
build:
	cmd.exe /C build\buildwindows.cmd

bootstrap:
	cmd.exe /C build\bootstrapwindows.cmd

run:
	cmd.exe /C build\runwindows.cmd

clean:
	cmd.exe /C build\cleanwindows.cmd

info:
	@echo ROOT_DIR=$(ROOT_DIR)
	@echo HOST=$(HOST)
	@echo ARCH=$(ARCH)
	@echo CONFIG=$(CONFIG)
	@echo Windows build uses native batch wrappers plus edk2 build

else

include build/common.mk
include build/linux.mk

all: build

build: kernel bootloader

bootstrap:
	git submodule update --init --recursive

info:
	@echo ROOT_DIR=$(ROOT_DIR)
	@echo HOST=$(HOST)
	@echo ARCH=$(ARCH)
	@echo CONFIG=$(CONFIG)
	@echo OUT_DIR=$(OUT_DIR)
	@echo EDK2_DIR=$(EDK2_DIR)
	@echo EDK2_TARGET=$(EDK2_TARGET)
	@echo EDK2_ARCH=$(EDK2_ARCH)

kernel:
	$(MAKE) -C kernel \
		ROOT_DIR="$(ROOT_DIR)" \
		HOST="$(HOST)" \
		ARCH="$(ARCH)" \
		CONFIG="$(CONFIG)"

bootloader: kernel
	$(MAKE) -C bootloader \
		ROOT_DIR="$(ROOT_DIR)" \
		HOST="$(HOST)" \
		ARCH="$(ARCH)" \
		CONFIG="$(CONFIG)"

run: build
	$(QEMU) $(QEMU_FLAGS)

clean:
	$(MAKE) -C kernel \
		ROOT_DIR="$(ROOT_DIR)" \
		HOST="$(HOST)" \
		ARCH="$(ARCH)" \
		CONFIG="$(CONFIG)" \
		clean

	$(MAKE) -C bootloader \
		ROOT_DIR="$(ROOT_DIR)" \
		HOST="$(HOST)" \
		ARCH="$(ARCH)" \
		CONFIG="$(CONFIG)" \
		clean

	$(RM_RF) "$(OUT_DIR)"

endif