#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <raylib/raylib.h>
#include <lua/lua_includes.h>
#include <string.h>
#include "raylua.h"



// #ifdef __linux__
// #include <unistd.h>  // Linux 的 readlink
// char* get_executable_path() {
//     char path[1024];
//     ssize_t len = readlink("/proc/self/exe", path, sizeof(path)-1);
//     if (len != -1) {
//         path[len] = '\0';
//         return strdup(path);
//     }
//     return NULL;
// }
// #else 
// #ifdef __WIN32__
// #include <windows.h>  // Windows 的 GetModuleFileName
// char* get_executable_path() {
//     char path[MAX_PATH];
//     if (GetModuleFileNameA(NULL, path, MAX_PATH) != 0) {
//         return strdup(path);
//     }
//     return NULL;
// }
// #else 
// #include <mach-o/dyld.h>  // macOS 特有头文件
// // 使用 _NSGetExecutablePath 的实现
// char *get_executable_path() {
//     char *executable_path = NULL;
//     uint32_t size = 0;

//     // Get the size of the executable path buffer
//     _NSGetExecutablePath(NULL, &size);

//     // Allocate the executable path buffer
//     executable_path = (char*)malloc(sizeof(char) * size);

//     // Get the executable path
//     if (_NSGetExecutablePath(executable_path, &size) == 0) {
//         // Find the last occurrence of '/' character
//         char *last_slash = strrchr(executable_path, '/');
//         if (last_slash != NULL) {
//             // Replace the '/' character with null character
//             *(last_slash) = '\0';
//         } else {
//             // Error: executable path does not contain '/'
//             free(executable_path);
//             return NULL;
//         }
//     } else {
//         // Error: unable to get executable path
//         free(executable_path);
//         return NULL;
//     }

//     return executable_path;
// }
// #endif
// #endif



#ifdef _WIN32
    extern char* argv[];
    extern int argc;
#else
    #include <unistd.h>
    #include <limits.h>
#endif

char* get_executable_path() {
#ifdef _WIN32
    char* path = NULL;
    // Windows: 使用命令行参数
    // return strdup("");
    // 方法2: 使用环境变量
    const char* env_path = getenv("_");
    if (env_path != NULL) {
        path = strdup(env_path);
    }
    
    // 方法3: 如果环境变量不可用，返回相对路径（当前目录）
    if (path == NULL) {
        // 在 Windows 下，如果没有更好的方法，可以返回一个默认值
        // 或者返回 NULL 表示无法确定路径
        path = strdup(".\\"); // 默认值
    }
    return path;
#else
    // Unix-like: 尝试多种方法
    char path[PATH_MAX];
    ssize_t len = -1;
    
    // 按优先级尝试不同的方法
    const char* methods[] = {
        "/proc/self/exe",           // Linux
        "/proc/curproc/file",       // FreeBSD
        "/proc/curproc/exe",        // NetBSD
        "/proc/self/path/a.out",    // Solaris
        NULL
    };
    
    for (int i = 0; methods[i] != NULL; i++) {
        len = readlink(methods[i], path, sizeof(path) - 1);
        if (len > 0) break;
    }
    
    if (len > 0) {
        path[len] = '\0';
        return strdup(path);
    }
    
    // 最后尝试环境变量
    const char* env_path = getenv("_");
    return env_path ? strdup(env_path) : NULL;
#endif
}

int main(void) {
    char *executable_path = get_executable_path();
    if (executable_path == NULL) {
        fprintf(stderr, "Error: unable to get executable path\n");
        return 1;
    }

    // Remove trailing slash from executable path
    size_t len = strlen(executable_path);
    if (len > 0 && executable_path[len-1] == '/') {
        executable_path[len-1] = '\0';
    }

    char *script_path = (char*)malloc(sizeof(char) * (strlen(executable_path) + strlen("/scripts/main.lua") + 1));
    sprintf(script_path, "%s/scripts/main.lua", executable_path);
    free(executable_path);
    //printf("script path: %s\n", script_path);

    lua_State *L = luaL_newstate();
    
    registerBindings(L);
    
    doScript(script_path, L);
    
    lua_close(L);
    free(script_path);
    return 0;
}