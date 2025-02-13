#include "dal_uart.h"
#include "dal_gpio.h"
#include "lock.h"
#include "gd32f4xx_usart.h"

#if defined(__CC_ARM)
#pragma diag_suppress       1296
#endif

//https://blog.csdn.net/qq_36720691/article/details/126712637


typedef struct {
    rcu_periph_enum     rcu;
    
    U32                 grp;
    U32                 pin;
    U32                 af;
}uart_pin_t;


typedef struct {
    U32                 dma;
    rcu_periph_enum     rcu;
    dma_channel_enum    chn;
    dma_subperipheral_enum sub;
    U32                 IRQn;
}dma_info_t;

typedef struct {
    
    U32                 urt;
    rcu_periph_enum     rcu;
    
    uart_pin_t          rx;
    uart_pin_t          tx;
    U32                 IRQn;
    
    dma_info_t          dmaRx;
    dma_info_t          dmaTx;
}uart_info_t;

   
const uart_info_t uartInfo[UART_MAX]={
    
    {USART0, RCU_USART0, {RCU_GPIOA, GPIOA, GPIO_PIN_10, GPIO_AF_7}, {RCU_GPIOA, GPIOA, GPIO_PIN_9,  GPIO_AF_7}, USART0_IRQn, {DMA1, RCU_DMA1, DMA_CH2, DMA_SUBPERI4, DMA0_Channel2_IRQn}, {DMA1, RCU_DMA1, DMA_CH7, DMA_SUBPERI4, DMA0_Channel7_IRQn}},
    {USART1, RCU_USART1, {RCU_GPIOA, GPIOA, GPIO_PIN_3,  GPIO_AF_7}, {RCU_GPIOA, GPIOA, GPIO_PIN_2,  GPIO_AF_7}, USART1_IRQn, {DMA0, RCU_DMA0, DMA_CH5, DMA_SUBPERI4, DMA0_Channel5_IRQn}, {DMA0, RCU_DMA0, DMA_CH6, DMA_SUBPERI4, DMA0_Channel6_IRQn}},
    {USART2, RCU_USART2, {RCU_GPIOB, GPIOB, GPIO_PIN_11, GPIO_AF_7}, {RCU_GPIOB, GPIOB, GPIO_PIN_10, GPIO_AF_7}, USART2_IRQn, {DMA0, RCU_DMA0, DMA_CH1, DMA_SUBPERI4, DMA0_Channel1_IRQn}, {DMA0, RCU_DMA0, DMA_CH3, DMA_SUBPERI4, DMA0_Channel3_IRQn}},
    {UART3,  RCU_UART3,  {RCU_GPIOB, GPIOB, GPIO_PIN_0,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_0,  GPIO_AF_8}, UART3_IRQn,  {DMA0, RCU_DMA0, DMA_CH2, DMA_SUBPERI4, DMA0_Channel2_IRQn}, {DMA0, RCU_DMA0, DMA_CH4, DMA_SUBPERI4, DMA0_Channel4_IRQn}},
    {UART4,  RCU_UART4,  {RCU_GPIOB, GPIOB, GPIO_PIN_0,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_0,  GPIO_AF_8}, UART4_IRQn,  {DMA0, RCU_DMA0, DMA_CH0, DMA_SUBPERI4, DMA0_Channel0_IRQn}, {DMA0, RCU_DMA0, DMA_CH7, DMA_SUBPERI4, DMA0_Channel7_IRQn}},
    //{USART5, RCU_USART5, {RCU_GPIOB, GPIOB, GPIO_PIN_0,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_0,  GPIO_AF_8}, USART5_IRQn, {DMA1, RCU_DMA1, DMA_CH1, DMA_SUBPERI5, DMA0_Channel1_IRQn}, {DMA1, RCU_DMA1, DMA_CH6, DMA_SUBPERI5, DMA0_Channel6_IRQn}},
    {USART5, RCU_USART5, {RCU_GPIOC, GPIOC, GPIO_PIN_7,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_6,  GPIO_AF_8}, USART5_IRQn, {DMA1, RCU_DMA1, DMA_CH1, DMA_SUBPERI5, DMA0_Channel1_IRQn}, {DMA1, RCU_DMA1, DMA_CH6, DMA_SUBPERI5, DMA0_Channel6_IRQn}},
    {UART6,  RCU_UART6,  {RCU_GPIOB, GPIOB, GPIO_PIN_0,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_0,  GPIO_AF_8}, UART6_IRQn,  {DMA0, RCU_DMA0, DMA_CH3, DMA_SUBPERI5, DMA0_Channel3_IRQn}, {DMA0, RCU_DMA0, DMA_CH1, DMA_SUBPERI5, DMA0_Channel1_IRQn}},
    {UART7,  RCU_UART7,  {RCU_GPIOB, GPIOB, GPIO_PIN_0,  GPIO_AF_8}, {RCU_GPIOC, GPIOC, GPIO_PIN_0,  GPIO_AF_8}, UART7_IRQn,  {DMA0, RCU_DMA0, DMA_CH6, DMA_SUBPERI5, DMA0_Channel6_IRQn}, {DMA0, RCU_DMA0, DMA_CH0, DMA_SUBPERI5, DMA0_Channel0_IRQn}},
};
    

typedef struct {
    dal_uart_cfg_t cfg;
    rx_cb_t        callback[CB_MAX+1];
}dal_uart_handle_t;

static dal_uart_handle_t* uartHandle[UART_MAX]={NULL};

static void uart_dma_init(dal_uart_handle_t *h)
{
    uart_info_t *info=(uart_info_t*)&uartInfo[h->cfg.port];
    dma_single_data_parameter_struct init;
    dma_info_t *dma;
    
    dma = &info->dmaRx;
    rcu_periph_clock_enable(dma->rcu);
    dma_deinit(dma->dma, dma->chn);
    init.direction = DMA_PERIPH_TO_MEMORY;
    init.memory0_addr = (U32)h->cfg.rx.buf;
    init.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    init.number = h->cfg.rx.blen;
    init.periph_addr = (U32)(&USART_DATA(info->urt));
    init.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    init.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    init.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(dma->dma, dma->chn, &init);
    dma_channel_subperipheral_select(dma->dma, dma->chn, dma->sub);
    dma_circulation_disable(dma->dma, dma->chn);
    dma_channel_enable(dma->dma, dma->chn);

#if 0
    dma = &info->dmaTx;
    rcu_periph_clock_enable(dma->rcu);
    dma_deinit(dma->dma, dma->chn);
    init.direction = DMA_MEMORY_TO_PERIPH;
    init.memory0_addr = (U32)h->tx.buf;
    init.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    init.number = h->tx.blen;
    init.periph_addr = (U32)(&USART_DATA(info->urt));
    init.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    init.periph_memory_width = DMA_PERIPH_WIDTH_8BIT;
    init.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_single_data_mode_init(dma->dma, dma->chn, &init);
    dma_channel_subperipheral_select(dma->dma, dma->chn, dma->sub);
    dma_circulation_disable(dma->dma, dma->chn);
    dma_channel_enable(dma->dma, dma->chn);
#endif
}
static inline void uart_data_callback(dal_uart_handle_t *h, int idle)
{
    int i;
    
    if(h->cfg.rx.buf && h->cfg.rx.dlen>0 && (idle || h->cfg.rx.dlen>=100)) {
        for(i=CB_MAX; i>=0; i--) {
            if(h->callback[i]) {
                h->callback[i](h->cfg.handle, NULL, 0, h->cfg.rx.buf, h->cfg.rx.dlen, idle);
            }
        }
        h->cfg.rx.dlen = 0;
    }
}

static void uart_dma_send(dal_uart_handle_t *h, U8 *data, int len)
{
    uart_info_t *info=(uart_info_t*)&uartInfo[h->cfg.port];
    dma_info_t *dma=&info->dmaTx;
    
    usart_flag_clear(info->urt, USART_FLAG_TC);

	dma_channel_disable(dma->dma, dma->chn);
	dma_flag_clear(dma->dma, dma->chn, DMA_FLAG_FTF);
	dma_memory_address_config(dma->dma, dma->chn, DMA_MEMORY_0, (uint32_t)data);
	dma_transfer_number_config(dma->dma, dma->chn, len);
	dma_channel_enable(dma->dma, dma->chn);
	while (usart_flag_get(info->urt, USART_FLAG_TC)!=RESET);
}

static void uart_dma_deinit(dal_uart_handle_t *h)
{
    uart_info_t *info=(uart_info_t*)&uartInfo[h->cfg.port];
    dma_channel_disable(info->dmaRx.dma, info->dmaRx.chn);
    dma_channel_disable(info->dmaTx.dma, info->dmaTx.chn);
    
    
}
static void uart_dma_rx_proc(dal_uart_handle_t *h)
{
    int i,recv_len=0;
    uart_info_t *info=(uart_info_t*)&uartInfo[h->cfg.port];
    dma_info_t *dma=&info->dmaRx;;
    
    if(usart_interrupt_flag_get(info->urt,USART_INT_FLAG_IDLE) != RESET) {
        usart_interrupt_flag_clear(info->urt, USART_INT_FLAG_IDLE);
        USART_STAT0(info->urt);  USART_DATA(info->urt);
        dma_channel_disable(dma->dma, dma->chn);
        recv_len = h->cfg.rx.blen - dma_transfer_number_get(dma->dma, dma->chn);
        if(recv_len>0 && recv_len<=h->cfg.rx.blen && h->cfg.rx.buf) {
            
            dma_memory_address_config(dma->dma, dma->chn, DMA_MEMORY_0, (U32)h->cfg.rx.buf);
            dma_transfer_number_config(dma->dma, dma->chn, h->cfg.rx.blen);
            uart_data_callback(h, 1);
            
            dma_flag_clear(dma->dma, dma->chn, DMA_FLAG_FTF);
            dma_channel_enable(dma->dma, dma->chn);		///* 开启DMA传输 
        }
    }
}
static void uart_it_rx_proc(dal_uart_handle_t *h)
{
    int i;
    FlagStatus fs;
    U8 port=h->cfg.port;
    uart_info_t *info=(uart_info_t*)&uartInfo[port];
    
    if (RESET != usart_interrupt_flag_get(info->urt, USART_INT_FLAG_RBNE) && 
        (RESET != usart_flag_get(info->urt, USART_FLAG_RBNE))) {
        usart_interrupt_flag_clear(info->urt, USART_INT_FLAG_RBNE);           //清中断标志
        
        if(h->cfg.rx.buf && h->cfg.rx.dlen<h->cfg.rx.blen) {
            h->cfg.rx.buf[h->cfg.rx.dlen] = usart_data_receive(info->urt);
            h->cfg.rx.dlen++;   
        }
        uart_data_callback(h, 0);
    }
    else if (RESET != usart_interrupt_flag_get(info->urt, USART_INT_FLAG_IDLE)) {
        usart_interrupt_flag_clear(info->urt, USART_INT_FLAG_IDLE);
        usart_data_receive(info->urt);                                        // 清除接收完成标志位
        
        uart_data_callback(h, 1);
    }
}


////////////////////////////////////////////////////////
handle_t dal_uart_init(dal_uart_cfg_t *cfg)
{   
    U32 urt;
    uart_info_t *info=NULL;
    dal_uart_handle_t *h=NULL;
    
    if(!cfg || cfg->port>UART_7) {
        return NULL;
    }
    
    if(uartHandle[cfg->port]) {
        return uartHandle[cfg->port];
    }
    
    h = malloc(sizeof(dal_uart_handle_t));
    if(!h) {
        return NULL;
    }
    h->cfg = *cfg;
    h->callback[CB_MAX] = cfg->callback;
    
    info = (uart_info_t*)&uartInfo[h->cfg.port];
    
    /* 开启时钟 */
    rcu_periph_clock_enable(info->rx.rcu); 
    rcu_periph_clock_enable(info->tx.rcu); 
    rcu_periph_clock_enable(info->rcu); 

    /* 配置GPIO复用功能 */
    gpio_af_set(info->rx.grp,info->rx.af,info->rx.pin);	
    gpio_af_set(info->tx.grp,info->tx.af,info->tx.pin);	

    /* 配置GPIO的模式 */
    gpio_mode_set(info->rx.grp,GPIO_MODE_AF,GPIO_PUPD_PULLUP,info->rx.pin);
    gpio_mode_set(info->tx.grp, GPIO_MODE_AF,GPIO_PUPD_PULLUP,info->tx.pin);

    gpio_output_options_set(info->rx.grp,GPIO_OTYPE_PP,GPIO_OSPEED_25MHZ,info->rx.pin);
    gpio_output_options_set(info->tx.grp,GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, info->tx.pin);

    /* 配置串口的参数 */
    usart_deinit(info->urt);
    usart_baudrate_set(info->urt,h->cfg.baudrate);
    usart_parity_config(info->urt,USART_PM_NONE);
    usart_word_length_set(info->urt,USART_WL_8BIT);
    usart_stop_bit_set(info->urt,USART_STB_1BIT);
	//usart_hardware_flow_coherence_config(info->urt,USART_HCM_NONE);
    if(h->cfg.msb) {
        usart_data_first_config(info->urt,USART_MSBF_MSB);
    }
    else {
        usart_data_first_config(info->urt,USART_MSBF_LSB);
    }
    
    if(h->cfg.mode==MODE_DMA) {
        usart_dma_transmit_config(info->urt, USART_DENT_ENABLE);    //打开串口DMA发送
        usart_dma_receive_config(info->urt,  USART_DENR_ENABLE);     //打开串口DMA接收
        uart_dma_init(h);
    }
    
    if(h->cfg.mode==MODE_IT || h->cfg.mode==MODE_DMA) {
        //usart_flag_clear(info->urt, USART_FLAG_TC);
        //usart_interrupt_enable(info->urt, USART_INT_TC);                    //发送完成中断
        
        usart_interrupt_enable(info->urt, USART_INT_RBNE);                  //使能读区非空中断  
        usart_interrupt_enable(info->urt, USART_INT_IDLE);                  //使能空闲中断
        
        nvic_irq_enable(info->IRQn,5,0);
    }
    
    usart_receive_config(info->urt,USART_RECEIVE_ENABLE);
    usart_transmit_config(info->urt,USART_TRANSMIT_ENABLE);
    usart_enable(info->urt);

    uartHandle[cfg->port] = h;
    
    return h;
}



int dal_uart_deinit(handle_t h)
{
    U32 urt;
    dal_uart_handle_t *dh=(dal_uart_handle_t*)h;
    
    if(!dh) {
        return -1;
    }
    uart_info_t *info=(uart_info_t*)&uartInfo[dh->cfg.port];
    
    if(dh->cfg.mode!=MODE_POLL) {
        usart_interrupt_disable(info->urt, USART_INT_RBNE);
        usart_interrupt_disable(info->urt, USART_INT_IDLE);
        nvic_irq_disable(info->IRQn);
        
        if(dh->cfg.mode==MODE_DMA) {
            uart_dma_deinit(dh);
        }
    }
    usart_receive_config(info->urt,USART_RECEIVE_DISABLE);
    usart_transmit_config(info->urt,USART_TRANSMIT_DISABLE);
    
    usart_disable(info->urt);
    usart_deinit(info->urt);
    uartHandle[dh->cfg.port] = NULL;
    
    free(dh);
    
    return 0;
}


int dal_uart_set_baudrate(handle_t h, int baudrate)
{
    dal_uart_handle_t *dh=(dal_uart_handle_t*)h;
    
    if(!dh) {
        return -1;
    }
    
    usart_baudrate_set(uartInfo[dh->cfg.port].urt, baudrate);
    
    return 0;
}


int dal_uart_read(handle_t h, U8 *data, int len)
{
    int i;
    U32 urt;
    dal_uart_handle_t *dh=(dal_uart_handle_t*)h;
    
    if(!dh || !data || !len) {
        return -1;
    }
    
    urt = uartInfo[dh->cfg.port].urt;
    if(dh->cfg.mode==MODE_POLL) {
        for(i=0; i<len; i++) {
            data[i] = (U8)usart_data_receive(urt);
            while(RESET == usart_flag_get(urt,USART_FLAG_TBE));
        }
    }
    
    return 0;
}


int dal_uart_write(handle_t h, U8 *data, int len)
{
    int i;
    U32 urt;
    dal_uart_handle_t *dh=(dal_uart_handle_t*)h;
    
    if(!h || !data || !len) {
        return -1;
    }
    
    urt = uartInfo[dh->cfg.port].urt;
    if(dh->cfg.mode==MODE_DMA) {
        uart_dma_send(dh, data, len);
    }
    else {
        for(i=0; i<len; i++) {
            while(usart_flag_get(urt,USART_FLAG_TBE) == RESET);
            usart_data_transmit(urt, data[i]);
        }
    }
    
    return 0;
}


int dal_uart_rw(handle_t h, U8 *data, int len, U8 rw)
{
    if(rw) {
        return dal_uart_write(h, data, len);
    }
    else {
        return dal_uart_read(h, data, len);
    }
}



int dal_uart_set_callback(handle_t h, int id, rx_cb_t cb)
{
    dal_uart_handle_t *dh=(dal_uart_handle_t*)h;
    
    if(!dh || id<0 || id>=CB_MAX) {
        return -1;
    }
    
    dh->callback[id] = cb;
    
    return 0;
}



static void uartx_handler(U8 port)
{
    dal_uart_handle_t *h=uartHandle[port];
    uart_info_t *info=(uart_info_t*)&uartInfo[port];
    
#if 1
    if(usart_interrupt_flag_get(info->urt,USART_INT_FLAG_ERR_ORERR)
	   ||usart_interrupt_flag_get(info->urt,USART_INT_FLAG_ERR_NERR)
	   ||usart_interrupt_flag_get(info->urt,USART_INT_FLAG_ERR_FERR)) {
    
        USART_DATA(info->urt);
		usart_interrupt_flag_clear(info->urt,USART_INT_FLAG_ERR_ORERR);
		usart_interrupt_flag_clear(info->urt,USART_INT_FLAG_ERR_NERR);
		usart_interrupt_flag_clear(info->urt,USART_INT_FLAG_ERR_FERR);
		return;
	}
#endif
    
    if(h->cfg.mode==MODE_DMA) {
        uart_dma_rx_proc(h);
    }
    else if(h->cfg.mode==MODE_IT) {
        uart_it_rx_proc(h);
    }
}

void USART0_IRQHandler(void) {    uartx_handler(UART_0);    }
void USART1_IRQHandler(void) {    uartx_handler(UART_1);    }
void USART2_IRQHandler(void) {    uartx_handler(UART_2);    }
void UART3_IRQHandler(void)  {    uartx_handler(UART_3);    }
void UART4_IRQHandler(void)  {    uartx_handler(UART_4);    }
void USART5_IRQHandler(void) {    uartx_handler(UART_5);    }
void UART6_IRQHandler(void)  {    uartx_handler(UART_6);    }
void UART7_IRQHandler(void)  {    uartx_handler(UART_7);    }










