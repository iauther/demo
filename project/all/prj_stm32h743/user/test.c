#include "incs.h"


static U16 data_recved_len=0;
static handle_t tmr_handle=NULL;

#define TEST_BUF_LEN 200
static U8  rxBuffer[TEST_BUF_LEN];
static U8  tmpBuffer[TEST_BUF_LEN];

static void rx_callback(U8 *data, U16 len)
{
    
    if(len<=TEST_BUF_LEN) {
        memcpy(rxBuffer, data, len);
        data_recved_len = len;
    }
}
static void tmr_callback(void *arg)
{
    
}
////////////////////////////////////////////////

#if 0
#define TEST_LEN                  500000
#define TEST_SDRAM_BASE           (0xD3300000)
#define TEST_SDRAM_SIZE           (13*1024*1024-48)
uint64_t sdram_mem[TEST_SDRAM_SIZE/8] __attribute__ ((at(TEST_SDRAM_BASE)));
static int sdram_test(void)
{
    int i,err=0;
    
    for(i=0; i<TEST_SDRAM_SIZE/8; i++) {
        sdram_mem[i] = i;
        if(sdram_mem[i] != i) {
            LOGI("____ wrong sdram rw, %d\n", i);
            err = 1;
            break;
        }
    }
    memset(sdram_mem, 0, TEST_SDRAM_SIZE);
    
    return err;
}
#endif

void test_main(void)
{
    net_cfg_t cfg;
    int err,cnt=0;
    log_init();
    
    //sdram_init();
    
    cfg.callback = NULL;
    net_init(&cfg);
    
    //adc_init();
    //com_init(rx_callback, 100);
    
    while(1) {
        err = 0;//sdram_test();
        LOGI("_____%d, err: %d\n", cnt++, err);
        //delay_ms(200);
    }
}

