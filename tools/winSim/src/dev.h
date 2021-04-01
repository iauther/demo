#ifndef __DEV_Hx__
#define __DEV_Hx__

#include "types.h"

int dev_open(int port);
int dev_close(void);
int dev_is_opened(void);

int dev_send(void* data, U16 len);
int dev_recv(void* data, U16 len);




#endif

