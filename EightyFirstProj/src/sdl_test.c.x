#include <sdl/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	
    
    // 或者使用编译器特定的方式
    #ifdef _MSC_VER
	// 设置栈大小为 8MB
    SetThreadStackGuarantee(&(ULONG){ 8 * 1024 * 1024 });
    #pragma comment(linker, "/STACK:8388608")
    #endif
	
    printf("Starting SDL test...\n");
    
    // 只初始化最基本的子系统
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    
    printf("SDL initialized successfully\n");
    
    // 立即退出
    SDL_Quit();
    return 0;
}