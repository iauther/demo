#ifndef __DAL_UART_Hx__
#define __DAL_UART_Hx__

#include "types.h"

#define CB_MAX  3


enum {
    UART_0=0,
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_6,
    UART_7,

    UART_MAX
};


typedef struct {
    U8                  mode;
    U8                  port;
    U8                  msb;
    U8                  useDMA;
    U32                 baudrate;
    handle_t            handle;
    
    buf_t               rx;
    rx_cb_t             callback;
}dal_uart_cfg_t;

handle_t dal_uart_init(dal_uart_cfg_t *cfg);
int dal_uart_deinit(handle_t h);
int dal_uart_set_baudrate(handle_t h, int baudrate);
int dal_uart_read(handle_t h, U8 *data, int len);
int dal_uart_write(handle_t h, U8 *data, int len);
int dal_uart_rw(handle_t h, U8 *data, int len, U8 rw);

int dal_uart_set_callback(handle_t h, int id, rx_cb_t cb);
#endif


