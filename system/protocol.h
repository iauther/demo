#ifndef __PROTOCOL_Hx__
#define __PROTOCOL_Hx__

#include "types.h"
#include "dsp.h"
#include "dal_adc.h"

#define FW_MAGIC            0xFACEBEAD
#define PKT_MAGIC           0xDEADBEEF
#define UPG_HEAD_MAGIC      0xABCD1234
#define UPG_TAIL_MAGIC      0x1234ABCD

enum {
    OBJ_BOOT=0,
    OBJ_APP,
};

enum {
    UPG_FLAG_NORMAL=0,
    UPG_FLAG_START,
    UPG_FLAG_FINISH,
    
    UPG_FLAG_MAX=0x0f,
};


enum {
    STAT_STOP=0,
    STAT_CALI,              //calibration
    STAT_CAP,
    STAT_TEST,
    STAT_UPGRADE,
    
    STAT_POWEROFF=0x10,
    STAT_MAX
};


enum {
    TYPE_CAP=0,       //channel capture data
    TYPE_CALI,        //calibration
    TYPE_ACK,
    TYPE_STAT,
    TYPE_SETT,
    TYPE_PARA,
    TYPE_FILE,
    TYPE_TIME,
    TYPE_HBEAT,
    TYPE_ERROR,
    
    TYPE_MAX
};



enum {
    FILE_PARA=0,
    
    FILE_CAP,       //adc data
    FILE_UPG,
    FILE_LOG,
    
    FILE_MAX
};

#ifdef _WIN32
#pragma warning(disable : 4200)
#endif

#pragma pack (1)

typedef F32     raw_t;
typedef F32     ev_t;

typedef struct {
    char ip[40];
    U16  port;
}tcp_para_t;
typedef struct {
    char host[100];
    U16  port;
    char prdKey[20];
    char prdSecret[64];
    char devKey[32];
    char devSecret[64];
}plat_para_t;
typedef struct {
    U8   mode;              //0: tcp, 1: plat
    union {
        tcp_para_t  tcp;
        plat_para_t plat;
    }para;
}net_para_t;
typedef struct {
    U8   addr;
}mbus_para_t;
typedef struct {
    U8   type;
    U8   auth;              //0: None 1: PAP  2: CHAP
    char apn[20];
}card_para_t;
typedef struct {
    U8   to;
    U8   level;
    U8   enable;
}dbg_para_t;
typedef struct {
    U8   enable;
    U32  fdiv;              //freq divider
}dac_para_t;
typedef struct {
    U8   pwr_mode;          //0:no powerdown    1: period powerdown
    U8   smp_mode;          //0: period sample  1: threshold trigger sample   2: continuous sample
    U32  smp_period;        //unit: second
}smp_para_t;
typedef struct {
    F32     a;
    F32     b;
}coef_t;
typedef struct {
    U8      ch;
    U32     smpFreq;        //hz
    U32     smpTime;        //ms
    U8      ev[EV_NUM];
    U8      n_ev;
    U8      upway;         //0: upload realtime   1: delay upload together
    U8      upwav;
    U8      savwav;
    U32     evCalcCnt;
    
    coef_t  coef;
}ch_para_t;
typedef struct {
    net_para_t  net;
    dac_para_t  dac;
    smp_para_t  smp;
    dbg_para_t  dbg;
    mbus_para_t mbus;
    card_para_t card;
    ch_para_t   ch[CH_MAX];
}usr_para_t;

typedef struct {
    U32             tp;
    U64             time;
    F32             data;
}ev_data_t;

typedef struct {
    U32             ch;
    U64             time;
    U32             wavlen;
    U32             evlen;
    F32             data[0];
}ch_data_t;

typedef struct {
    U8              batt;
    S8              temp;
    F32             sig_s;      //strength
    F32             sig_q;      //quality
    U64             time;
}stat_data_t;

typedef struct {
    U8              ch;
    U8              enable;
}capture_t;

typedef struct {
    U32             cntdown;
}powerdown_t;

typedef struct {
    U8              xx;
    
}sett_t;

typedef struct {
    U8              mode;
    U8              state;
    date_time_t     dt;
}state_t;

typedef struct {
    U8              type;
    U8              error;      //refer to error.h
}error_t;

typedef struct {
    U8              type;
    U8              error;      //refer to error.h
}ack_t;

typedef struct {
    U32             magic;          //PKT_MAGIC
    U8              type;
    U8              flag;
    U8              askAck;         //1: need ack     0: no need ack
    U16             dataLen;
    U8              data[0];
    //U8            checksum;
}pkt_hdr_t;

/////////////upgrade define////////////////////
typedef struct {
    U8              ftype;
    U16             pkts;
    U16             pid;
    U16             dataLen;
    U8              data[0];
}file_hdr_t;

typedef struct {
    U32             magic;           //FW_MAGIC
    U8              version[20];     //V10.00.00
    U8              bldtime[20];     //20220810_162208
    U32             length;          
}fw_info_t;                          
                                     
typedef struct {                     
    U8              obj;             //0: boot       1: app
    U8              force;           
    U8              erase;           //0: no erase   1: do erase
    U8              flag;
    U32             jumpAddr;
    U8              padd[72];
}upg_ctl_t;

typedef struct {
    U32             head;            //UPG_HEAD_MAGIC
    U32             upgCnt;
    U32             fwAddr;          //app fw header offset in flash
    U32             runAddr;         //the boot jump offset
    U32             facFillFlag;     //0: not fill  1: already fill
    U32             upgFlag;         //UPG_FLAG_NONE etc.
    U32             tail;            //UPG_TAIL_MAGIC
}upg_info_t;

//make sure sizeof(upg_hdr_t)==128 bytes
typedef struct {
    fw_info_t       fwInfo;
    upg_ctl_t       upgCtl;
    U8              data[0];
}upg_hdr_t;

typedef struct {
    U8              digit[32];
}md5_t;

typedef struct {
    fw_info_t       fwInfo;
    sett_t          sett;
}para_t;

typedef struct {
    state_t         stat;
    para_t          para;
}sys_para_t;

typedef struct {
    U16             tms;        //times
    U16             ch;
    F32             rms;        //mv
    U32             freq;
    F32             bias;
}cali_sig_t;
typedef struct {
    F32         in;
    F32         out;
}cali_rms_t;
typedef struct {
    U32             cnt;
    cali_rms_t      rms[2];
    cali_sig_t      sig;
}cali_t;
typedef struct {
    cali_t          cali[CH_MAX];
}gbl_var_t;

typedef struct {
    sys_para_t      sys;
    usr_para_t      usr;
    gbl_var_t       var;
}all_para_t;


#pragma pack ()


#define PKT_HDR_LENGTH      sizeof(pkt_hdr_t)


#endif

