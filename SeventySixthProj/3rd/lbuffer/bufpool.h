#ifndef __BUF_POOL_H_
#define __BUF_POOL_H_

#include "lbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

LBUFF_API buffer_pool* bufpool_alloc(uint32_t fixsize, uint16_t graw_size);

LBUFF_API void bufpool_close(buffer_pool* pool);

LBUFF_API uint8_t* bufpool_malloc(buffer_pool* pool);

LBUFF_API void bufpool_free(buffer_pool* pool, uint8_t* data);


#ifdef __cplusplus
}
#endif

#endif