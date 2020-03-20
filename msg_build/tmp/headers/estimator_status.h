/****************************************************************************
 *
 *   Copyright (C) 2013-2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* Auto-generated by genmsg_cpp from file estimator_status.msg */


#pragma once


#include <uORB/uORB.h>


#ifndef __cplusplus
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_GPS_FIX 0
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MIN_SAT_COUNT 1
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MIN_PDOP 2
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_HORZ_ERR 3
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_VERT_ERR 4
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_SPD_ERR 5
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_HORZ_DRIFT 6
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_VERT_DRIFT 7
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_HORZ_SPD_ERR 8
#define ESTIMATOR_STATUS_GPS_CHECK_FAIL_MAX_VERT_SPD_ERR 9
#define ESTIMATOR_STATUS_CS_TILT_ALIGN 0
#define ESTIMATOR_STATUS_CS_YAW_ALIGN 1
#define ESTIMATOR_STATUS_CS_GPS 2
#define ESTIMATOR_STATUS_CS_OPT_FLOW 3
#define ESTIMATOR_STATUS_CS_MAG_HDG 4
#define ESTIMATOR_STATUS_CS_MAG_3D 5
#define ESTIMATOR_STATUS_CS_MAG_DEC 6
#define ESTIMATOR_STATUS_CS_IN_AIR 7
#define ESTIMATOR_STATUS_CS_WIND 8
#define ESTIMATOR_STATUS_CS_BARO_HGT 9
#define ESTIMATOR_STATUS_CS_RNG_HGT 10
#define ESTIMATOR_STATUS_CS_GPS_HGT 11
#define ESTIMATOR_STATUS_CS_EV_POS 12
#define ESTIMATOR_STATUS_CS_EV_YAW 13
#define ESTIMATOR_STATUS_CS_EV_HGT 14
#define ESTIMATOR_STATUS_CS_BETA 15
#define ESTIMATOR_STATUS_CS_MAG_FIELD 16
#define ESTIMATOR_STATUS_CS_FIXED_WING 17
#define ESTIMATOR_STATUS_CS_MAG_FAULT 18
#define ESTIMATOR_STATUS_CS_ASPD 19
#define ESTIMATOR_STATUS_CS_GND_EFFECT 20
#define ESTIMATOR_STATUS_CS_RNG_STUCK 21
#define ESTIMATOR_STATUS_CS_GPS_YAW 22
#define ESTIMATOR_STATUS_CS_MAG_ALIGNED 23

#endif


#ifdef __cplusplus
struct __EXPORT estimator_status_s {

#else
struct estimator_status_s {
#endif
	uint64_t timestamp;
	float states[24];
	float vibe[3];
	float covariances[24];
	float output_tracking_error[3];
	uint32_t control_mode_flags;
	float pos_horiz_accuracy;
	float pos_vert_accuracy;
	float mag_test_ratio;
	float vel_test_ratio;
	float pos_test_ratio;
	float hgt_test_ratio;
	float tas_test_ratio;
	float hagl_test_ratio;
	float beta_test_ratio;
	float time_slip;
	uint16_t gps_check_fail_flags;
	uint16_t filter_fault_flags;
	uint16_t innovation_check_flags;
	uint16_t solution_status_flags;
	uint8_t n_states;
	bool pre_flt_fail_innov_heading;
	bool pre_flt_fail_innov_vel_horiz;
	bool pre_flt_fail_innov_vel_vert;
	bool pre_flt_fail_innov_height;
	bool pre_flt_fail_mag_field_disturbed;
	uint8_t health_flags;
	uint8_t timeout_flags;
	uint8_t _padding0[4]; // required for logger


#ifdef __cplusplus
	static constexpr uint8_t GPS_CHECK_FAIL_GPS_FIX = 0;
	static constexpr uint8_t GPS_CHECK_FAIL_MIN_SAT_COUNT = 1;
	static constexpr uint8_t GPS_CHECK_FAIL_MIN_PDOP = 2;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_HORZ_ERR = 3;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_VERT_ERR = 4;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_SPD_ERR = 5;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_HORZ_DRIFT = 6;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_VERT_DRIFT = 7;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_HORZ_SPD_ERR = 8;
	static constexpr uint8_t GPS_CHECK_FAIL_MAX_VERT_SPD_ERR = 9;
	static constexpr uint8_t CS_TILT_ALIGN = 0;
	static constexpr uint8_t CS_YAW_ALIGN = 1;
	static constexpr uint8_t CS_GPS = 2;
	static constexpr uint8_t CS_OPT_FLOW = 3;
	static constexpr uint8_t CS_MAG_HDG = 4;
	static constexpr uint8_t CS_MAG_3D = 5;
	static constexpr uint8_t CS_MAG_DEC = 6;
	static constexpr uint8_t CS_IN_AIR = 7;
	static constexpr uint8_t CS_WIND = 8;
	static constexpr uint8_t CS_BARO_HGT = 9;
	static constexpr uint8_t CS_RNG_HGT = 10;
	static constexpr uint8_t CS_GPS_HGT = 11;
	static constexpr uint8_t CS_EV_POS = 12;
	static constexpr uint8_t CS_EV_YAW = 13;
	static constexpr uint8_t CS_EV_HGT = 14;
	static constexpr uint8_t CS_BETA = 15;
	static constexpr uint8_t CS_MAG_FIELD = 16;
	static constexpr uint8_t CS_FIXED_WING = 17;
	static constexpr uint8_t CS_MAG_FAULT = 18;
	static constexpr uint8_t CS_ASPD = 19;
	static constexpr uint8_t CS_GND_EFFECT = 20;
	static constexpr uint8_t CS_RNG_STUCK = 21;
	static constexpr uint8_t CS_GPS_YAW = 22;
	static constexpr uint8_t CS_MAG_ALIGNED = 23;

#endif
};

/* register this as object request broker structure */
ORB_DECLARE(estimator_status);


#ifdef __cplusplus
void print_message(const estimator_status_s& message);
#endif
