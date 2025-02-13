#ifndef __DATETIME_Hx__
#define __DATETIME_Hx__

#include "types.h"


int get_week(U16 y, U8 m, U8 d);
int get_weekn(U16 y, U8 m, U8 d);
int get_date(char *date_s, date_s_t *date);
int get_tm(char *time_s, time_s_t *time);

int get_date_str(void *str, int len);
int get_time_str(void *str, int len);
int get_datetime_str(void *str, int len);
    
int date_is_valid(date_s_t *date);
int get_datetime(char *datetime, datetime_t *dt);

int tm_to_ts(datetime_t *dt, U64 *ts_ms);
int ts_to_tm(U64 ts_ms, datetime_t *dt);

#endif

