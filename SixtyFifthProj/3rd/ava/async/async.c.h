#ifdef CONFIG_H
#include CONFIG_H
#endif

#ifdef ASYNC_C
#pragma once
#define ATOMIC_C
#define CHANNEL_C
#define CONDV_C
#define LFQ_C
#define MUTEX_C
#define REALLOC_C
#define SEMAPHORE_C
#define SLEEP_C
#define SYSTEM_C
#define THREAD_C
#define TLS_C
#endif

#include "../detect/detect.c.h"
#include "../memory/memory.c.h" // realloc

#include "async_atomic.c.h"
#include "async_channel.c.h"
#include "async_condv.c.h"
#include "async_lfq.c.h"
#include "async_mutex.c.h"
#include "async_semaphore.c.h"
#include "async_sleep.c.h"
#include "async_thread.c.h"
#include "async_tls.c.h"
