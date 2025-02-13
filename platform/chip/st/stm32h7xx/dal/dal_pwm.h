#ifndef __DAL_PWM_Hx__
#define __DAL_PWM_Hx__

#include "dal_gpio.h"

#define PWM_CH_MAX     4

enum {
    PWM_PIN_A0,
    PWM_PIN_A1,
    PWM_PIN_A2,
    PWM_PIN_A3,
    
    PWM_PIN_A6,
    PWM_PIN_A7,
    PWM_PIN_B0,
    PWM_PIN_B1,
    
    PWM_PIN_D12,
    PWM_PIN_D13,
    PWM_PIN_D14,
    PWM_PIN_D15,
    
    PWM_PIN_F3,
    PWM_PIN_F4,
    PWM_PIN_F5,
    PWM_PIN_F10,
    
    PWM_PIN_MAX
};



enum {
    TYPE_NO=0,
    TYPE_OC,
    TYPE_IC,
    
};
enum {
    MODE_PP=0,
    MODE_OD,
};


typedef void (*pwm_callback_t)(handle_t h, U8 pwm_pin, U32 freq, F32 dr);

typedef struct {
    U8              pwm_pin;
    U8              type;
    U8              mode;
}pwm_ch_t;

typedef struct {
    pwm_ch_t        pwmCh[PWM_CH_MAX];
    
    U32             freq;
    F32             dr;     //duty ratio
}pwm_para_t;

typedef struct {
    pwm_para_t      para;
    U8              useDMA;
    pwm_callback_t  callback;
}pwm_cfg_t;


handle_t dal_pwm_init(pwm_cfg_t *cfg);
int dal_pwm_deinit(handle_t h);
int dal_pwm_start(handle_t h, U8 pwm_pin);
int dal_pwm_stop(handle_t h, U8 pwm_pin);
int dal_pwm_set(handle_t h, U8 pwm_pin, U32 freq, F32 dr);

#endif
