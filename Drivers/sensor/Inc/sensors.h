/*
 * mpu.h
 *
 *  Created on: 20 Jul 2021
 *      Author: sheldonvon
 */

#ifndef IMU_INC_MPU_H_
#define IMU_INC_MPU_H_

#include "config.h"
#include "controlStatus.h"

#define USE_MPU6050

#define RAD_TO_DEG 57.295779513082320876798154814105
#define DEG2RAD 	0.017453292519943295
#define I2C_TIMEOUT 0xFF
typedef struct{
	double gyro_roll;
	double gyro_pitch;
	double gyro_yaw;

	double angle_pitch;
	double angle_roll;
	double angle_yaw;
} SensorData;

#ifdef USE_MPU6050
#include "mpu6050.h"
typedef I2C_HandleTypeDef 	COM_PROTC;
typedef MPU6050_CONFIG		IMU_CONFIG;
#endif

void IMU_Init(COM_PROTC *com_porotc);
void IMU_Read();
void IMU_Compose();


extern SensorData sensorData;
#endif /* IMU_INC_MPU_H_ */
