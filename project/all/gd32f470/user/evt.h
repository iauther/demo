#ifndef __EVT_Hx__
#define __EVT_Hx__

#include "types.h"

#define EVT_DATA_MAX   64

enum {
    EVT_ADS=0,
    EVT_ADC,
    EVT_485,
    EVT_LOG,
    EVT_NET,
    EVT_DATA,
    EVT_FINISH,
    
    EVT_TIMER,
    EVT_SEND,
    EVT_SAVE,
    EVT_CALI,
    
};

typedef struct {
    U32     evt;
    U32     type;
    U32     flag;
    void    *arg;
    U32     dlen;
    U8      data[EVT_DATA_MAX];
}evt_t;

#endif


