ROOT_DIR_WIN          := $(shell cygpath -aw "$(ROOT_DIR)")
EDK2_DIR_WIN          := $(shell cygpath -aw "$(EDK2_DIR)")
EDK2_BUILD_SCRIPT_WIN := $(shell cygpath -aw "$(ROOT_DIR)/build/edk2buildwindows.cmd")

LLVM_BIN_WIN         ?= C:\Program Files\LLVM\bin
PYTHON_COMMAND_WIN   ?= $(ROOT_DIR_WIN)\.venv-edk2\Scripts\python.exe
PYTHON_HOME_WIN      ?=

QEMU ?= $(ROOT_DIR)/debugger/windows/qemu.exe
OVMF ?= $(ROOT_DIR)/OVMF.fd