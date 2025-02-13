#ifndef __TINYALLOC_Hx__
#define __TINYALLOC_Hx__

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


bool ta_init(const void *base, const void *limit, const size_t heap_blocks, const size_t split_thresh, const size_t alignment);
void *ta_alloc(size_t num);
void *ta_calloc(size_t num, size_t size);
bool ta_free(void *ptr);

size_t ta_num_free(void);
size_t ta_num_used(void);
size_t ta_num_fresh(void);
bool ta_check(void);

#ifdef __cplusplus
}
#endif

#endif





