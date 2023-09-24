#include "task.h"
#include "list.h"
#include "fs.h"
#include "cfg.h"
#include "dal.h"
#include "date.h"
#include "power.h"
#include "dal_rtc.h"
#include "dal_sd.h"
#include "upgrade.h"
#include "paras.h"
#include "dal_adc.h"
#include "dal_delay.h"
#include "aiot_at_api.h"


#define POLL_TIME       1000

#define UPG_FILE        SFLASH_MNT_PT"/app.upg"
#define TMP_LEN         (0x100*8)


#ifdef OS_KERNEL

typedef struct {
    int     id;
    void    *data;
    
}file_node_t;


static U32 tmrCount=0;
static handle_t fList=NULL;
extern at_sig_stat_t sig_stat;



static int upg_file_is_exist(void)
{
    int r,flen;
    handle_t fl;
    fw_info_t info1,info2;
    int upg_file_exist=0;
    
    r = dal_sd_status();
    if(r==0) {  //sd exist
        
        fl = fs_open(UPG_FILE, FS_MODE_RW);
        if(fl) {
            flen = fs_size(fl);
            if(flen>0) {
                
                fs_read(fl, &info1, sizeof(info1));
                upgrade_get_fw_info(&info2);
        
                if(memcmp(&info1, &info2, sizeof(fw_info_t))) {
                    upg_file_exist = 1;
                }   
            }
            
            fs_close(fl);
        }
    }
    
    return upg_file_exist;
}

static void upgrade_polling(U8 loop)
{
    int r,index=0;
    int is_exist=0;
    U8 *pbuf=NULL;
    handle_t fl,fs;
    static int upg_chk_flag=0;
    int rlen,flen,upg_ok_flag=0;
    
    if(!upg_chk_flag) {
        is_exist = upg_file_is_exist();
        if(!is_exist) {
            return;
        }
        
        if(!loop) {
            upg_chk_flag = 1;
        }
    }
        
    pbuf = (U8*)malloc(TMP_LEN);
    if(!pbuf) {
        LOGE("____ upgrade_proc malloc failed\n");
        return;
    }
        
    fl = fs_open(UPG_FILE, FS_MODE_RW);
    if(!fl) {
        LOGE("____ %s open failed\n", UPG_FILE);
        goto fail;
    }
    
    flen = fs_size(fl);
    if(flen<=0) {
        LOGE("____ upgrade file len wrong\n");
        goto fail;
    }
        
    LOGD("____ upgrade file len: %d\n", flen);
    upgrade_erase(flen);
    
    while(1) {
        rlen = fs_read(fl, pbuf, TMP_LEN);
        //LOGD("_____%d, 0x%02x, 0x%02x, \n", rlen, tmp[0], tmp[1]);
        if(rlen>0) {
            if(rlen<TMP_LEN) {
                r = upgrade_write(pbuf, rlen, -1);
                if(r) {
                    LOGE("____ upgrade failed\n");
                }
                else {
                    LOGD("____ upgrade ok\n");
                    upg_ok_flag = 1;
                }
                break;
            }
            
            r = upgrade_write(pbuf, rlen, index++);
            if(r) {
                LOGE("____ upgrade write failed, index: %d\n", index);
                break;
            }
        }
        else {
            LOGE("____ fs_read error\n");
            break;
        }
    }
    fs_close(fl);
    
    if(upg_ok_flag) {
        LOGD("____ reboot now ...\n\n\n");
        dal_reboot();
    }
    
fail:
    free(pbuf);
    fs_close(fl);
}

static U32 get_run_time(void)
{
    U32 t1,t2;
    date_time_t dt1,dt2;
    
    paras_get_datetime(&dt1);
    dal_rtc_get(&dt2);
    
    get_timestamp(&dt1, &t1);
    get_timestamp(&dt2, &t2);
    
    return (t2-t1);
}
static void poweroff_polling(void)
{
    
    U8 mode=allPara.usr.smp.pwr_mode;
    
    switch(mode) {
        
        case 0:
        {
            
        }
        break;
        
        case 1:
        {
            
        }
        break;
            
        case 2:
        {
            
        }
        break;
    }
}
static void stat_polling(void)
{
    //signal strength
    //battery level
    //temperature
    //
}












static void polling_tmr_callback(void *arg)
{
    task_post(TASK_POLLING, NULL, EVT_TIMER, 0, NULL, 0);
}


static int conn_flag=0;
static osThreadId_t connThdId=NULL;
static void task_conn_fn(void *arg)
{
    power_set_dev(POWER_DEV_ECXXX, POWER_MODE_ON);
    conn_flag = api_comm_connect();
    if(!conn_flag) {
        power_set_dev(POWER_DEV_ECXXX, POWER_MODE_OFF);
    }
    
    connThdId = NULL;
}
static void start_conn_task()
{
    smp_para_t *smp=paras_get_smp();
    
    //周期模式采样时，采样完成再启动连接，避免4g对信号造成干扰
    if(smp->smp_mode==0 && api_cap_stoped() && !connThdId) {
        task_simp_new(task_conn_fn, 1024, NULL, &connThdId);
    }
}


void task_polling_fn(void *arg)
{
    int i,r;
    U8  err;
    evt_t e;
    osTimerId_t tmrId;
    task_handle_t *h=(task_handle_t*)arg;
    
    LOGD("_____ task_polling running\n");

    task_tmr_start(TASK_POLLING, polling_tmr_callback, NULL, POLL_TIME, TIME_INFINITE);
    while(1) {
        r = task_recv(TASK_POLLING, &e, sizeof(e));
        if(r==0) {
            switch(e.evt) {
                
                case EVT_TIMER:
                {
                    tmrCount++;
                    
                    stat_polling();
                    poweroff_polling();
                    //upgrade_polling();
                    
                    api_cap_period_start(CH_0);
                    
                    //start_conn_task();
                }
                break;
                
                case EVT_SAVE:
                {
                    paras_save();
                }
                break;
            }
        }
        
        task_yield();
    }
}
#endif


