/*! \file ch_common.h
 *
 * \brief Internal driver functions for operation with the Chirp ultrasonic sensor.
 *
 * This file contains common implementations of sensor support routines.  These are
 * suitable for use with most standard sensor firmware images.  The firmware-specific
 * init function will set up various function pointers to either the common implementations
 * in this file, or corresponding firmware-specific implementations.
 *
 * You should not need to edit this file or call the driver functions directly.  Doing so
 * will reduce your ability to benefit from future enhancements and releases from Chirp.
 *
 */

/*
 * Copyright � 2016-2020, Chirp Microsystems.  All rights reserved.
 *
 * Chirp Microsystems CONFIDENTIAL
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CHIRP MICROSYSTEMS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You can contact the authors of this program by email at support@chirpmicro.com
 * or by mail at 2560 Ninth Street, Suite 220, Berkeley, CA 94710.
 */

#ifndef CH_COMMON_H_
#define CH_COMMON_H_

#include "dev/ch101/inc/soniclib.h"
#include <stdint.h>

/* CH-101 common definitions */

#define CH101_COMMON_REG_OPMODE 		0x01
#define CH101_COMMON_REG_TICK_INTERVAL 	0x02
#define CH101_COMMON_REG_PERIOD 		0x05
#define CH101_COMMON_REG_CAL_TRIG 		0x06
#define CH101_COMMON_REG_MAX_RANGE 		0x07
#define CH101_COMMON_REG_TIME_PLAN 		0x09
#define CH101_COMMON_REG_CAL_RESULT 	0x0A
#define CH101_COMMON_REG_RX_HOLDOFF		0x11
#define CH101_COMMON_REG_STAT_RANGE 	0x12
#define CH101_COMMON_REG_STAT_COEFF		0x13
#define CH101_COMMON_REG_READY 			0x14
#define CH101_COMMON_REG_TOF_SF 		0x16
#define CH101_COMMON_REG_TOF 			0x18
#define CH101_COMMON_REG_AMPLITUDE		0x1A
#define CH101_COMMON_REG_DATA 			0x1C

#define CH101_COMMON_I2CREGS_OFFSET		0

#define CH101_COMMON_READY_FREQ_LOCKED	(0x02)		// XXX need more values (?)

#define CH101_COMMON_FREQCOUNTERCYCLES (128)

#define	CH101_COMMON_STAT_COEFF_DEFAULT	(6)		// default value for stationary target coefficient
#define CH101_COMMON_NUM_THRESHOLDS	(6)		// total number of thresholds

/* CH-201 common definitions */

#define CH201_COMMON_REG_OPMODE 		0x01
#define CH201_COMMON_REG_TICK_INTERVAL 	0x02
#define CH201_COMMON_REG_PERIOD 		0x05
#define CH201_COMMON_REG_CAL_TRIG 		0x06
#define CH201_COMMON_REG_MAX_RANGE 		0x07
#define CH201_COMMON_REG_THRESH_LEN_0 	0x08
#define CH201_COMMON_REG_THRESH_LEN_1 	0x09
#define CH201_COMMON_REG_CAL_RESULT		0x0A
#define CH201_COMMON_REG_THRESH_LEN_2 	0x0C
#define CH201_COMMON_REG_THRESH_LEN_3 	0x0D
#define CH201_COMMON_REG_RX_HOLDOFF		0x11
#define CH201_COMMON_REG_ST_RANGE 		0x12
#define CH201_COMMON_REG_READY 			0x14
#define CH201_COMMON_REG_THRESH_LEN_4 	0x15
#define CH201_COMMON_REG_THRESHOLDS		0x16	// start of array of six 2-byte threshold levels
#define CH201_COMMON_REG_TOF_SF 		0x22
#define CH201_COMMON_REG_TOF 			0x24
#define CH201_COMMON_REG_AMPLITUDE 		0x26
#define CH201_COMMON_REG_DATA 			0x28

#define CH201_COMMON_I2CREGS_OFFSET		0

#define CH201_COMMON_READY_FREQ_LOCKED	(0x02)		// XXX need more values (?)

#define CH201_COMMON_FREQCOUNTERCYCLES (128)

#define CH201_COMMON_NUM_THRESHOLDS		(6)		// total number of thresholds


/* Function prototypes */

uint8_t ch_common_set_mode(ch_dev_t *dev_ptr, ch_mode_t mode);

uint8_t ch_common_fw_load(ch_dev_t *dev_ptr);

uint8_t ch_common_set_sample_interval(ch_dev_t *dev_ptr, uint16_t interval_ms);

uint8_t ch_common_set_num_samples( ch_dev_t* dev_ptr, uint16_t num_samples );

uint8_t ch_common_set_max_range(ch_dev_t *dev_ptr, uint16_t max_range_mm);

uint8_t ch_common_set_static_range(ch_dev_t *dev_ptr, uint16_t samples);

uint32_t ch_common_get_range(ch_dev_t *dev_ptr, ch_range_t range_type);

uint16_t ch_common_get_amplitude(ch_dev_t *dev_ptr);

uint8_t ch_common_get_locked_state(ch_dev_t *dev_ptr);

uint32_t ch_common_get_op_freq(ch_dev_t *dev_ptr);

void ch_common_prepare_pulse_timer(ch_dev_t *dev_ptr);

void ch_common_store_pt_result(ch_dev_t *dev_ptr);

void ch_common_store_op_freq(ch_dev_t *dev_ptr);

void ch_common_store_bandwidth(ch_dev_t *dev_ptr);

void ch_common_store_scale_factor(ch_dev_t *dev_ptr);

uint8_t ch_common_set_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresholds_ptr);

uint8_t ch_common_get_thresholds(ch_dev_t *dev_ptr, ch_thresholds_t *thresholds_ptr);

uint16_t ch_common_mm_to_samples(ch_dev_t *dev_ptr, uint16_t num_mm);

uint16_t ch_common_samples_to_mm(ch_dev_t *dev_ptr, uint16_t num_samples);

uint8_t ch_common_get_iq_data(ch_dev_t *dev_ptr, ch_iq_sample_t *buf_ptr, uint16_t start_sample, uint16_t num_samples, ch_io_mode_t nonblock);

uint8_t	 ch_common_set_sample_window(ch_dev_t *dev_ptr, uint16_t start_sample, uint16_t end_sample);

uint8_t ch_common_set_time_plan(ch_dev_t *dev_ptr, ch_time_plan_t time_plan);

ch_time_plan_t ch_common_get_time_plan(ch_dev_t *dev_ptr);
uint16_t ch_common_get_amplitude_avg(ch_dev_t *dev_ptr);

uint8_t ch_common_get_amplitude_data(ch_dev_t *dev_ptr, uint16_t *buf_ptr, uint16_t start_sample, uint16_t num_samples, 
									 ch_io_mode_t mode);

uint8_t ch_common_set_rx_holdoff(ch_dev_t *dev_ptr, uint16_t rx_holdoff);

uint16_t ch_common_get_rx_holdoff(ch_dev_t *dev_ptr);
#endif

