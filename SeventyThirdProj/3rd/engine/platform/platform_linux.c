#include "platform.h"

#ifdef __linux__

#include <dlfcn.h>
#include <sys/stat.h>

void *platform_load_library(const char *path) {
    return dlopen(path, RTLD_LAZY | RTLD_GLOBAL);
}

void *platform_library_func(void *handle, const char *func) {
    return dlsym(handle, func);
}

void platform_free_library(void *handle) { dlclose(handle); }

const char *platform_get_error() { return dlerror(); }

const char *platform_is_path_file_or_dir(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        return "error";
    }

    if (path_stat.st_mode & S_IFREG) {
        return "file";
    } else if (path_stat.st_mode & S_IFDIR) {
        return "directory";
    } else {
        return "unknown";
    }
}

#endif
