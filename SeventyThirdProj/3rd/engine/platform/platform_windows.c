#include "platform.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <windows.h>

void *platform_load_library(const char *path) {
    return LoadLibrary(path);
}

void *platform_library_func(void *handle, const char *func) {
    return GetProcAddress(handle, func);
}

void platform_free_library(void *handle) {
    FreeLibrary(handle);
}

// const char *platform_get_error() { return GetLastError(); }
const char *platform_get_error() { 
    DWORD errorCode = GetLastError();
    if (errorCode == 0) {
        return "No error";
    }

    LPSTR messageBuffer = NULL;
    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer, // 缓冲区由系统分配
        0,
        NULL
    );

    if (size == 0) {
        return "Failed to format error message";
    }

    // 返回消息字符串（调用者需负责释放内存）
    return (const char*)messageBuffer;
 }

const char *platform_is_path_file_or_dir(const char *path) {
    DWORD attributes = GetFileAttributes(path);

    if (attributes == INVALID_FILE_ATTRIBUTES) {
        return "error";
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY) {
        return "directory";
    } else {
        return "file";
    }
}

#endif
