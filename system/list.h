#ifndef __LIST_Hx__
#define __LIST_Hx__

#include <stdlib.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif


enum {
    LIST_FULL_FIFO=0,
    LIST_FULL_FILO,
};

enum {
    LIST_SORT_ASCEND=0,
    LIST_SORT_DESCEND,
    
    LIST_SORT_MAX
};

typedef enum {
    ACT_NONE=0,
    ACT_STOP,
    ACT_REMOVE,
    ACT_DELETE,
}LIST_ACT;

typedef struct list_node {
    node_t              data;
    struct list_node    *prev;
    struct list_node    *next;
}list_node_t;

typedef struct {
    U8          log;        //0:disable  1: enable
    U8          mode;
    int         max;        //the max count
}list_cfg_t;



//该函数返回负值是表示结束，将退出迭代循环
//该函数返回值>=0将继续迭代至结束
typedef int (*list_callback_t)(handle_t l, node_t *node, node_t *xd, void *arg, int *act);


handle_t list_init(list_cfg_t *cfg);
int list_free(handle_t l);
int list_get_node(handle_t l, list_node_t **lnode, int index);
int list_set_node(handle_t l, list_node_t  *lnode, int index);

int list_take_node(handle_t l, list_node_t **lnode, int index);
int list_back_node(handle_t l, list_node_t *lnode);
int list_discard_node(handle_t l, list_node_t *lnode);

int list_insert(handle_t l, node_t *node, int index);
int list_insert_node(handle_t l, list_node_t *lnode, int index);

int list_append(handle_t l, U32 tp, void *data, U32 len);
int list_append_node(handle_t l, list_node_t *lnode);

int list_infront(handle_t l, U32 tp, void *data, U32 len);
int list_infront_node(handle_t l, list_node_t *lnode);

int list_remove(handle_t l, int index);
int list_delete(handle_t l, int index);

int list_sort(handle_t l, U8 order);
int list_size(handle_t l);
int list_clear(handle_t l);
int list_iterator(handle_t l, node_t *node, list_callback_t callback, void *arg);

#ifdef __cplusplus
}
#endif

#endif


