
#pragma once

#ifdef _MSC_VER
#ifdef LBUFF_EXPORT
#define LBUFF_API _declspec(dllexport)
#else
#define LBUFF_API _declspec(dllimport)
#endif
#else
#ifdef __cplusplus
#define LBUFF_API extern
#else
#define LBUFF_API 
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct varbuffer {
    uint8_t* head;
    uint8_t* tail;
    uint8_t* end;
    uint8_t* data;
    size_t ori_size;
    size_t size;
} var_buffer;

typedef struct shmpool {
    uint32_t used;
    uint32_t fix_size;
    uint8_t* shm_data;
    size_t shm_handle;
    uint16_t block_num;
    uint16_t first_free;
} shm_pool;

typedef struct fixblock {
    uint8_t* data;
    struct fixblock* next;
    struct fixblock* next_free;
} fix_block;

typedef struct bufpool {
    uint32_t used;
    uint32_t capacity;
    uint32_t fix_size;
    uint16_t graw_size;
    fix_block* head;
    fix_block* tail;
    fix_block* first_free;
} buffer_pool;

typedef struct fixbuffer {
    uint32_t len;
    uint32_t end;
    uint32_t begin;
    uint8_t* data;
    struct fixbuffer* next;
} fix_buffer;

typedef struct bufqueue {
    uint32_t size;
    uint32_t fix_size;
    fix_buffer* head;
    fix_buffer* tail;
    shm_pool* sh_pool;
    buffer_pool* buf_pool;
} bufder_queue;


// #ifndef LBUFF_EXPORT
#include "shmpool.h"
#include "bufpool.h"
#include "buffer.h"
#include "bufqueue.h"
#include "serialize.h"
// #endif

#ifdef __cplusplus
}
#endif
