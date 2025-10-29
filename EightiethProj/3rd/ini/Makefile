# 编译器和工具
ifeq ($(OS),Windows_NT)
    # Windows 使用 PowerShell 获取时间
    BUILD_DATE := $(shell powershell -Command "Get-Date -Format 'yyyy-MM-ddTHH:mm:ss'")
    BUILD_ARCH	:= Windows_NT
	BUILD_TIME	:= $(shell powershell Get-Date)
	SHELL := powershell.exe
else
    # 类Unix系统使用 date 命令
    BUILD_DATE := $(shell date "+%Y-%m-%dT%H:%M:%S")
	BUILD_ARCH	:= $(shell uname -a)
	BUILD_TIME	:= $(shell date)
endif

CC = gcc
CXX =g++
AR = ar
MLFLAG = /c /coff 
SFLAGS = 
CFLAGS = -fPIE -Wl,--allow-multiple-definition -std=c11 -w -O3 -g -static -D_UNICODE -DUNICODE -D__UNICODE__ -DWIN32 -D_WIN32 -D__WIN32__ -D_WINDOWS -DWINDOWS -D__WINDOWS__ -D_GLFW_WIN32 -DNANOVG_GLEW -DGLEW_STATIC -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DLUA_COMPAT -DLUA_COMPAT_ALL -DLUA_COMPAT_5_3 -DLUA_COMPAT_5_2  -DFT2_BUILD_LIBRARY -DFT_CONFIG_OPTION_SYSTEM_ZLIB -DBUILDING_LIBCURL -DCURL_HIDDEN_SYMBOLS -DHAVE_CURL_CONFIG_H -DCURL_STATICLIB -DSFML_STATIC -DAL_BUILD_LIBRARY -DAL_LIBTYPE_STATIC -DAL_ALEXT_PROTOTYPES -DFLAC__CPU_X86_64 -DFLAC__HAS_X86INTRIN -DFLAC__ALIGN_MALLOC_DATA -DFLAC__NO_DLL -DFLAC__OVERFLOW_DETECT -DFLAC__HAS_OGG -DFLAC__ENABLE_64_BIT_WORDS  -DLOAD_PNG -DLOAD_JPG -DLOAD_WEBP -DLOAD_GIF -DCC_STATIC -DHAVE_FAAD_CONFIG_H -DSFML_STATIC -DSFML_SYSTEM_WINDOWS -DSFML_GRAPHICS_EXPORTS -DSTBI_FAILURE_USERMSG -DSFML_VULKAN_IMPLEMENTATION_NOT_AVAILABLE -DVAR_ARRAYS -DLPUGL_BUILD_DATE=\"$(BUILD_DATE)\" -DWIN32_LEAN_AND_MEAN
CXXFLAGS = -fPIE -Wl,--allow-multiple-definition -std=c++14 -w -O3 -g -static -D_UNICODE -DUNICODE -D__UNICODE__ -DWIN32 -D_WIN32 -D__WIN32__ -D_WINDOWS -DWINDOWS -D__WINDOWS__ -D_GLFW_WIN32 -DNANOVG_GLEW -DGLEW_STATIC -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DLUA_COMPAT -DLUA_COMPAT_ALL -DLUA_COMPAT_5_3 -DLUA_COMPAT_5_2  -DFT2_BUILD_LIBRARY -DFT_CONFIG_OPTION_SYSTEM_ZLIB -DBUILDING_LIBCURL -DCURL_HIDDEN_SYMBOLS -DHAVE_CURL_CONFIG_H -DCURL_STATICLIB -DSFML_STATIC -DAL_BUILD_LIBRARY -DAL_LIBTYPE_STATIC -DAL_ALEXT_PROTOTYPES -DFLAC__CPU_X86_64 -DFLAC__HAS_X86INTRIN -DFLAC__ALIGN_MALLOC_DATA -DFLAC__NO_DLL -DFLAC__OVERFLOW_DETECT -DFLAC__HAS_OGG -DFLAC__ENABLE_64_BIT_WORDS  -DLOAD_PNG -DLOAD_JPG -DLOAD_WEBP -DLOAD_GIF -DCC_STATIC -DHAVE_FAAD_CONFIG_H -DSFML_STATIC -DSFML_SYSTEM_WINDOWS -DSFML_GRAPHICS_EXPORTS -DSTBI_FAILURE_USERMSG -DSFML_VULKAN_IMPLEMENTATION_NOT_AVAILABLE -DVAR_ARRAYS -DLPUGL_BUILD_DATE=\"$(BUILD_DATE)\" -DWIN32_LEAN_AND_MEAN 
ARFLAGS = rcs

# 目录和文件
SRC_DIR = .
OBJ_DIR = .
LIB_DIR = ../../lib
INCLUDE_DIR = ../
INCLUDE_DIR += ../../header
LIB_NAME = ini
CACHE_EXTENSIONS := .o .d

ifeq ($(OS),Windows_NT)
SOURCEDIRS	:= $(SRC_DIR)
SOURCEDIRS	+= $(shell powershell -Command "Get-ChildItem -LiteralPath '$(SRC_DIR)' -Directory -Recurse -Force | Resolve-Path -Relative")
# ESCAPED_SRC_DIR := $(subst \, \\\\, $(SRC_DIR))
# SOURCEDIRS := $(shell dir /s /b /ad "$(SRC_DIR)" | findstr /i /r "^$(ESCAPED_SRC_DIR)\\\\.*")
INCLUDEDIRS	:= $(INCLUDE_DIR)
LIBDIRS		:= $(LIB_DIR)
FIXPATH = $(subst /,\,$1)
RM			:= del
TARGET 		:=  /s /q 
MD	:= mkdir
SHELL := cmd.exe
RM_CMD := del /S /Q
CACHE_PATTERNS := $(foreach ext,$(CACHE_EXTENSIONS),"*$(ext)")
else
SOURCEDIRS	:= $(shell find $(SRC_DIR) -type d) 
SOURCEDIRS	+= $(shell find $(SRC_DIR) -maxdepth 3 -type d) #递归查找3层
INCLUDEDIRS	:= $(shell find $(INCLUDE_DIR) -type d)
LIBDIRS		:= $(shell find $(LIB_DIR) -type d)
FIXPATH = $1
RM = rm 
TARGET 		:= -f
MD	:= mkdir -p
SHELL := /bin/bash
RM_CMD := rm -f
CACHE_PATTERNS := $(foreach ext,$(CACHE_EXTENSIONS),-name '*$(ext)')
endif

C_SRCS = $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.c, $(dir))))
CPP_SRCS = $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.cpp, $(dir))))
CXX_SRCS = $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.cxx, $(dir))))
CC_SRCS = $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.cc, $(dir))))
S_SRCS := $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.s, $(dir))))
ASM_SRCS := $(foreach dir,$(SOURCEDIRS), $(wildcard $(patsubst %,%/*.asm, $(dir))))
C_OBJS = $(C_SRCS:.c=.o)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
CXX_OBJS = $(CXX_SRCS:.cxx=.o)
CC_OBJS = $(CC_SRCS:.cc=.o)
S_OBJS = $(S_SRCS:.s=.o)
ASM_OBJS = $(ASM_SRCS:.asm=.o)
C_DEPS	:= $(C_OBJS:.o=.d)
CPP_DEPS:= $(CPP_OBJS:.o=.d)
CXX_DEPS:= $(CXX_OBJS:.o=.d)
CC_DEPS	:= $(CC_OBJS:.o=.d)
S_DEPS	:= $(S_OBJS:.o=.d)
ASM_DEPS	:= $(ASM_OBJS:.o=.d)
# INCLUDES_TMP_DIRS := $(foreach dir,$(INCLUDEDIRS),$(call FIXPATH,$(dir)))
# INCLUDES:= $(patsubst %,-I%, $(INCLUDES_TMP_DIRS:%/=%))
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS	:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
LIB = $(LIB_DIR)/lib$(LIB_NAME).a

# 默认目标
all: $(LIB)

# 生成静态库
$(LIB): $(C_OBJS) $(S_OBJS) $(ASM_OBJS) $(CPP_OBJS) $(CXX_OBJS) $(CC_OBJS)
	$(AR) $(ARFLAGS) $@ $^

-include $(C_DEPS) $(S_DEPS) $(ASM_DEPS) $(CPP_DEPS) $(CXX_DEPS) $(CC_DEPS)
# 生成目标文件
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -MMD $< -o $@
%.o:%.s
	$(CC) $(SFLAGS) $(INCLUDES) -c -MMD $< -o $@
%.o:%.asm
	$(CC) $(SFLAGS) $(INCLUDES) -c -MMD $< -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $< -o $@
%.o:%.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $< -o $@
%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $< -o $@

# 声明支持的源文件后缀
.SUFFIXES: .cc .cxx .s .asm .o
	
# 清理生成的文件
clean:
ifeq ($(OS),Windows_NT)
	@echo "清理开始"
	@for %%d in ($(SOURCEDIRS)) do ( \
        if exist "%%d" ( \
            echo 扫描目录: %%d & \
            $(RM_CMD) %%d\$(CACHE_PATTERNS) & \
            echo 已清除 %%d 中的缓存文件 \
        ) else ( \
            echo 跳过不存在目录: %%d \
        ) \
    )
	del /q /s /f $(call FIXPATH,$(LIB))
	@echo "清理完成"
else
	@echo "清理开始"
	@for dir in $(SOURCEDIRS); do \
        if [ -d "$$dir" ]; then \
            echo "扫描目录: $$dir" && \
            find "$$dir" -type f \( $(CACHE_PATTERNS) \) -delete && \
            echo "已清除 $$dir 中的缓存文件"; \
        else \
            echo "跳过不存在目录: $$dir"; \
        fi; \
    done
	rm -rf $(LIB)
	@echo "清理完成"
endif
.PHONY: all clean

