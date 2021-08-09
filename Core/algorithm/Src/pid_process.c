/*
 * pid_process.c
 *
 *  Created on: 18 Jul 2021
 *      Author: sheldonvon
 */

#include "pid_process.h"

PIDObject pid_pitch;
PIDObject pid_roll;
PIDObject pid_yaw;

pidInit_t pit_pitch_param;
pidInit_t pit_roll_param;
pidInit_t pit_yaw_param;

SetPoints setpoints;

float pitch_level_adjust, roll_level_adjust;
void pidsInit(){
	pit_pitch_param.kp = 1.1;
	pit_pitch_param.ki = .02;
	pit_pitch_param.kd = 0.01;
	pidInit(&pid_pitch, pit_pitch_param, 0.004);

	pit_roll_param.kp = 1.1;
	pit_roll_param.ki = .02;
	pit_roll_param.kd = 0.01;
	pidInit(&pid_roll, pit_roll_param, 0.004);

	pit_yaw_param.kp = 2.0;
	pit_yaw_param.ki = 0.008;
	pit_yaw_param.kd = 0;
	pidInit(&pid_yaw, pit_yaw_param, 0.004);
}

void pidProcess(){
	if(controlStatus.flightBaseStatus == STANDBY){
		pidReset(&pid_pitch);
		pidReset(&pid_roll);
		pidReset(&pid_yaw);
	} else if (controlStatus.flightBaseStatus == TAKEOFF){

		setPointReset(&setpoints);

		roll_level_adjust = 15 * sensorData.angle_roll;
		if(ATHIGH(channels[ROLL])) setpoints.roll = channels[ROLL] - CHANNEL_MID_MAX;
		else if(ATLOW(channels[ROLL])) setpoints.roll = channels[ROLL] - CHANNEL_MID_MIN;
		setpoints.roll -= roll_level_adjust;
		setpoints.roll /= 3.0;


		pitch_level_adjust = 15 * sensorData.angle_pitch;
		if(ATHIGH(channels[PITCH])) setpoints.pitch = CHANNEL_MID_MAX - channels[PITCH];
		else if(ATLOW(channels[PITCH])) setpoints.pitch = CHANNEL_MID_MIN - channels[PITCH];
		setpoints.pitch -= pitch_level_adjust;
		setpoints.pitch /= 3.0;

		if(ATHIGH(channels[YAW])) setpoints.yaw = CHANNEL_MID_MAX - channels[YAW];
		else if(ATLOW(channels[YAW])) setpoints.yaw = CHANNEL_MID_MIN - channels[YAW];
		setpoints.yaw /= 3;

		pidUpdate(&pid_pitch, sensorData.gyro_pitch, setpoints.pitch);
		pidUpdate(&pid_roll, sensorData.gyro_roll, setpoints.roll);
		pidUpdate(&pid_yaw, sensorData.gyro_yaw, setpoints.yaw);
	}
}

void setPointReset(SetPoints *sp){
	sp->roll = 0;
	sp->pitch = 0;
	sp->yaw = 0;
}
