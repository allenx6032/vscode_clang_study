#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef DEBUG_C
#pragma once
#define ASSERT_C
#define BREAKPOINT_C
#define BUILD_C
#define CRASH_C
#define DEBUGGER_C
#define DIALOG_C
#define HEXDUMP_C
#define LOGGER_C
#define PANIC_C
#define TEST_C
#endif

#include "debug_assert.c.h"
#include "debug_breakpoint.c.h"
#include "debug_build.c.h"
#include "debug_crash.c.h"
#include "debug_debugger.c.h"
#include "debug_dialog.c.h"
#include "debug_hexdump.c.h"
#include "debug_logger.c.h"
#include "debug_panic.c.h"
#include "debug_test.c.h"
