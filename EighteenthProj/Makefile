## SHELL=powershell
SHELL=cmd
CXX = g++
CXX = g++
CC = gcc
WINDRES = windres
ASMFLAGS	:=               
RCFLAGS		:= -O coff
CXXFLAGS	:= -fPIE -Wl,--allow-multiple-definition -std=c++20 -m64 -w -O3 -g -static -DWIN32 -D_WIN32 -D__WIN32__ -D_WINDOWS -DWINDOWS -D__WINDOWS__ -D_GLFW_USE_CONFIG_H -D_GLFW_WIN32 -DNANOVG_GLEW -DGLEW_STATIC -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DLUA_COMPAT -DLUA_COMPAT_ALL -DLUA_COMPAT_5_3 -DLUA_COMPAT_5_2  -DFT2_BUILD_LIBRARY -DFT_CONFIG_OPTION_SYSTEM_ZLIB -DBUILDING_LIBCURL -DCURL_HIDDEN_SYMBOLS -DHAVE_CURL_CONFIG_H -DCURL_STATICLIB -DSFML_STATIC -DAL_BUILD_LIBRARY -DAL_LIBTYPE_STATIC -DAL_ALEXT_PROTOTYPES -DFLAC__CPU_X86_64 -DFLAC__HAS_X86INTRIN -DFLAC__ALIGN_MALLOC_DATA -DFLAC__NO_DLL -DFLAC__OVERFLOW_DETECT -DFLAC__HAS_OGG -DFLAC__ENABLE_64_BIT_WORDS -DLOAD_PNG -DLOAD_JPG -DLOAD_WEBP -DLOAD_GIF -DCC_STATIC -DHAVE_FAAD_CONFIG_H -D_USRLUASTATIC -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP=1 -DSOL_NO_COMPAT -DSOL_USING_CXX_LUA=1 -DWINVER=0x0600        
CCFLAGS		:= -fPIE -Wl,--allow-multiple-definition -std=c11 -m64 -w -O3 -g -static -DWIN32 -D_WIN32 -D__WIN32__ -D_WINDOWS -DWINDOWS -D__WINDOWS__ -D_GLFW_USE_CONFIG_H -D_GLFW_WIN32 -DNANOVG_GLEW -DGLEW_STATIC -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -DLUA_COMPAT -DLUA_COMPAT_ALL -DLUA_COMPAT_5_3 -DLUA_COMPAT_5_2  -DFT2_BUILD_LIBRARY -DFT_CONFIG_OPTION_SYSTEM_ZLIB -DBUILDING_LIBCURL -DCURL_HIDDEN_SYMBOLS -DHAVE_CURL_CONFIG_H -DCURL_STATICLIB -DSFML_STATIC -DAL_BUILD_LIBRARY -DAL_LIBTYPE_STATIC -DAL_ALEXT_PROTOTYPES -DFLAC__CPU_X86_64 -DFLAC__HAS_X86INTRIN -DFLAC__ALIGN_MALLOC_DATA -DFLAC__NO_DLL -DFLAC__OVERFLOW_DETECT -DFLAC__HAS_OGG -DFLAC__ENABLE_64_BIT_WORDS -DLOAD_PNG -DLOAD_JPG -DLOAD_WEBP -DLOAD_GIF -DCC_STATIC -DHAVE_FAAD_CONFIG_H -D_USRLUASTATIC -DGRAPHICS_API_OPENGL_33 -DPLATFORM_DESKTOP=1 -DSOL_NO_COMPAT -DSOL_USING_CXX_LUA=1 -DWINVER=0x0600                    
LFLAGS = -lkernel32 -limm32 -lversion -luser32 -lwinspool -lodbc32 -lodbccp32 -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid  -lwinmm -lmingw32 -lMsimg32 -lopengl32 -lglu32 -lgdi32 -lgdiplus -ld3d9 -ldxguid -ld3d11 -lxinput -ldinput8 -ld2d1 -ldwrite -lwindowscodecs -lshlwapi -lWs2_32 -lIphlpapi -lcomctl32 -lpthread -ldsound -lddraw -lm -lbcrypt -lsetupapi -lsecur32 -lcrypt32  -lpsapi -luserenv -ld3dcompiler -ldwmapi  -lwsock32 -lUxTheme -lWininet -lpthread
## LFLAGS = -Wl,--subsystem,console -municode -mconsole -fexec-charset=gbk -finput-charset=gbk
## LFLAGS = -Wl,--subsystem,windows -municode -mwindows
OUTPUT	:= output
SRC		:= src 
INCLUDE	:= include
LIB		:= lib
RC		:= res
ASM		:= asm
3RD		:= 3rd
HEADER  := header

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
RCDIRS		:= $(RC)
ASMDIRS		:= $(ASM)
3RDDIRS		:= $(3RD)
HEADERDIRS		:= $(HEADER)
FIXPATH = $(subst /,\\,$1)
RM			:= del
TARGET 		:=  /s /q /f
MD	:= mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
RCDIRS		:= $(shell find $(RC) -type d)
ASMDIRS		:= $(shell find $(ASM) -type d)
3RDDIRS		:= $(shell find $(3RD) -type d)
HEADERDIRS		:= $(shell find $(HEADER) -type d)
FIXPATH = $1
RM = rm 
TARGET 		:= -f
MD	:= mkdir -p
endif

CURRENT := $(abspath $(lastword $(MAKEFILE_LIST)))# 当前Makefile路径
CURRENTPATH := $(dir $(CURRENT))# 当前Makefile所在目录
# SUBDIRS := $(patsubst %/,%,$(dir $(3RDDIRS))) # 获取子目录
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
HEADERS	:= $(patsubst %,-I%, $(HEADERDIRS:%/=%))
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))
3RDS		:= $(patsubst %/,%,$(wildcard $(3RDDIRS)/*/)) # 动态获取子目录
3RD_CLEAN_DIRS := $(foreach dir,$(3RDS),$(call FIXPATH,$(dir)))
3RDINCLUDES		:= $(patsubst %,-I%, $(3RDS:%/=%))
3RDLIBS_TMP		:= $(notdir $(patsubst %,%, $(3RDS:%/=%)))
3RDLIBS		:= $(patsubst %,-l%, $(3RDLIBS_TMP:%/=%))
ASMSOURCES		:= $(wildcard $(patsubst %,%/*.s, $(ASMDIRS)))
ASMOBJECTS		:= $(ASMSOURCES:.s=.o)
CXXSOURCES		:= $(wildcard $(patsubst %,%/*.cxx, $(SOURCEDIRS)))
CXXOBJECTS		:= $(CXXSOURCES:.cxx=.o)
CPPSOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
CPPOBJECTS		:= $(CPPSOURCES:.cpp=.o)
CCSOURCES		:= $(wildcard $(patsubst %,%/*.cc, $(SOURCEDIRS)))
CCOBJECTS		:= $(CCSOURCES:.cc=.o)
CSOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
COBJECTS		:= $(CSOURCES:.c=.o)
RCSOURCE 		:= $(wildcard $(patsubst %,%/*.rc, $(RCDIRS)))
RCOBJECTS		:= $(RCSOURCE:.rc=.o)
ASMDEPS		:= $(ASMOBJECTS:.o=.d)
CXXDEPS		:= $(CXXOBJECTS:.o=.d)
CPPDEPS		:= $(CPPOBJECTS:.o=.d)
CCDEPS		:= $(CCOBJECTS:.o=.d)
CDEPS		:= $(COBJECTS:.o=.d)
RCDEPS		:= $(RCOBJECTS:.o=.d)

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

# 动态生成子模块编译目标
define GENERATE_3RD_TARGET
	build_$(notdir \$1):
	ifeq ($(OS),Windows_NT)
		@echo 编译子模块: $$@...
		@start /B /WAIT $(MAKE) -C \$1
	else
		@echo "Compiling submodule: $$@"
		$(MAKE) -C \$1 -j$(nproc)
	endif
endef

all: $(OUTPUT) 3rd_build $(MAIN)
	@echo Executing 'all' complete!

# 编译第三方库
3rd_build:
ifeq ($(OS),Windows_NT)
#并行编译子模块
#$(foreach dir,$(3RDS),$(eval $(call GENERATE_3RD_TARGET,$(dir))))
	@echo 正在编译第三方库...
	@for %%d in ($(3RD_CLEAN_DIRS)) do @( \
		if exist "%%d" ( \
			echo 进入目录: %%d... & \
			$(MAKE) -C "%%d" \
		) else ( \
			echo 跳过不存在的目录: %%d \
		) \
	)
	@echo 第三方库编译完成！
else
	@echo 正在编译第三方库...
	@for dir in $(3RDS); do \
		echo 进入目录: $$dir...; \
		$(MAKE) -C $$dir; \
	done
	@echo 第三方库编译完成！
endif

$(OUTPUT):
	$(MD) $(OUTPUT)
$(MAIN): $(ASMOBJECTS)  $(CPPOBJECTS) $(CXXOBJECTS) $(CCOBJECTS) $(COBJECTS) $(RCOBJECTS)
	$(CXX) -o $(OUTPUTMAIN) $(CPPOBJECTS) $(ASMOBJECTS) $(CXXOBJECTS) $(CCOBJECTS) $(COBJECTS) $(RCOBJECTS) $(LIBS) $(3RDLIBS) $(LFLAGS) 
-include   $(CPPDEPS) $(CXXDEPS) $(CCDEPS) $(CDEPS) $(RCDEPS)
$(ASMDIRS)/%.o:$(ASMDIRS)/%.s
	$(CXX) $(ASMFLAGS) $(INCLUDES) -I$(3RDDIRS) $(HEADERS) -c -MMD $< -o $@
$(RCDIRS)/%.o:$(RCDIRS)/%.rc
	$(WINDRES) $(RCFLAGS) $< -o $@
%.o:%.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(3RDDIRS) $(HEADERS) -c -MMD $< -o $@
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(3RDDIRS) $(HEADERS) -c -MMD $< -o $@
%.o:%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(3RDDIRS) $(HEADERS) -c -MMD $< -o $@
%.o:%.c
	$(CC) $(CCFLAGS) $(INCLUDES) -I$(3RDDIRS) $(HEADERS) -c -MMD $< -o $@ 
.PHONY: clean

clean:
# 清理所有子目录
	@echo "Checking CURRENT paths: $(CURRENT)"
	@echo "Checking CURRENTPATH paths: $(CURRENTPATH)"
	@echo "Checking 3RDS paths: $(3RDS)"
ifeq ($(OS),Windows_NT)
	@echo 清理第三方库...
	@echo 待清理目录列表：$(3RD_CLEAN_DIRS)
	@for %%d in ($(3RD_CLEAN_DIRS)) do @( \
		if exist "%%d" ( \
			echo 正在清理 %%d... & \
			$(MAKE) -C "%%d" clean \
		) else ( \
			echo 跳过不存在的目录: %%d \
		) \
	)
	@echo 清理项目文件...
	del /Q $(call FIXPATH,src\*.o) 2>nul
	del /Q $(call FIXPATH,src\*.d) 2>nul
	del /Q $(call FIXPATH,res\*.o) 2>nul
	del /Q $(call FIXPATH,res\*.d) 2>nul
	del /Q $(call FIXPATH,asm\*.o) 2>nul
	del /Q $(call FIXPATH,asm\*.d) 2>nul
	del /Q $(OUTPUTMAIN) 2>nul
	@echo 清理完成!
else
	@for dir in $(3RDS); do \
		$(MAKE) -C $$dir clean; \
	done
	@rm -f $(CXXOBJECTS) $(CPPOBJECTS) $(CCOBJECTS) $(COBJECTS) $(RCOBJECTS) $(ASMOBJECTS)
	@rm -f $(OUTPUTMAIN)
	@echo 清理完成!
endif
# del $(call FIXPATH,src/*.o)
# del $(call FIXPATH,src/*.d)
# del $(call FIXPATH,res/*.d)
# del $(call FIXPATH,res/*.o)
# del $(call FIXPATH,asm/*.d)
# del $(call FIXPATH,asm/*.o)
# del $(OUTPUTMAIN)
	@echo Cleanup complete!
run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!