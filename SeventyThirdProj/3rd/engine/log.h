#ifndef ENGINE_LOG
#define ENGINE_LOG

#ifndef __EMSCRIPTEN__
#include "zlog.h"
#endif

static const char *config =
    "[global]\n"
    "strict init = true\n"
    "buffer min = 1024\n"
    "buffer max = 2MB\n"
    "[formats]\n"
    "simple_format = \"%d %T %V - %m%n\"\n"
    "detailed_format = \"%d %T %f:%L [%V] %m%n\"\n"
    "[rules]\n"
    "stdout.*             >stdout; simple_format\n"
    "stderr.ERROR         >stderr; simple_format\n"
    "stderr.CRITICAL      >stderr; simple_format\n"
    "file.DEBUG           \"logs/debug.log\", 10M * 5 ; detailed_format\n"
    "file.INFO            \"logs/info.log\", 10M * 5 ; detailed_format\n"
    "file.ERROR           \"logs/error.log\", 10M * 5 ; detailed_format\n"
    "file.CRITICAL        \"logs/critical.log\", 10M * 5 ; detailed_format\n";

static inline int log_init() {
#ifdef __EMSCRIPTEN__
    zlog_init(config);
    return 1;
#else
    return 0;
#endif
}

static inline void log_free() {
#ifdef __EMSCRIPTEN__
    zlog_finish();
#endif
};

#ifdef __EMSCRIPTEN__
#ifdef DEBUG
#define L_DEBUG(...)                                                         \
    do {                                                                       \
        zlog_debug(zlog_get_category("stdout"), __VA_ARGS__);                  \
        zlog_debug(zlog_get_category("file"), __VA_ARGS__);                    \
    } while (0)
#else
#define L_DEBUG(...)                                                         \
    do {                                                                       \
        zlog_debug(zlog_get_category("file"), __VA_ARGS__);                    \
    } while (0)
#endif
#else
#define L_DEBUG(...)
#endif

#ifdef __EMSCRIPTEN__
#define L_INFO(...)                                                            \
    do {                                                                       \
        zlog_info(zlog_get_category("stdout"), __VA_ARGS__);                   \
        zlog_info(zlog_get_category("file"), __VA_ARGS__);                     \
    } while (0)
#else
#define L_INFO(...)
#endif

#ifdef __EMSCRIPTEN__
#define L_NOTICE(...)                                                          \
    do {                                                                       \
        zlog_notice(zlog_get_category("file"), __VA_ARGS__);                   \
    } while (0)
#else
#define L_NOTICE(...)
#endif

#ifdef __EMSCRIPTEN__
#define L_WARN(...)                                                            \
    do {                                                                       \
        zlog_warn(zlog_get_category("file"), __VA_ARGS__);                     \
    } while (0)
#else
#define L_DEBUG(...)
#endif

#ifdef __EMSCRIPTEN__
#define L_ERROR(...)                                                           \
    do {                                                                       \
        zlog_error(zlog_get_category("stderr"), __VA_ARGS__);                  \
        zlog_error(zlog_get_category("file"), __VA_ARGS__);                    \
    } while (0)
#else
#define L_ERROR(...)
#endif

#ifdef __EMSCRIPTEN__
#define L_FATAL(...)                                                           \
    do {                                                                       \
        zlog_fatal(zlog_get_category("stderr"), __VA_ARGS__);                  \
        zlog_fatal(zlog_get_category("file"), __VA_ARGS__);                    \
    } while (0)
#else
#define L_FATAL(...)
#endif

#endif // ENGINE_LOG
