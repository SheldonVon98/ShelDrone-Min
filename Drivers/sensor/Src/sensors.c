/*
 * mpu.c
 *
 *  Created on: 20 Jul 2021
 *      Author: sheldonvon
 */

#include "sensors.h"

SensorData sensorData;


void IMU_Init(COM_PROTC *com_porotc){
#ifdef USE_MPU6050
	IMU_CONFIG imu_config;
	imu_config.powerOn = MPU6050_POWERON;
	imu_config.sampleRate = IMU_RATE_250;
	imu_config.DLPF_config = DLPF_43HZ;
	imu_config.ACC_config = ACCEL_RANGE_1000;
	imu_config.GYRO_config = GYRO_RANGE_4G;
#ifdef USE_IT
	imu_config.enable_it = INT_ENABLE_ENABLE;
#else
	imu_config.enable_it = INT_ENABLE_DISABLE;
#endif
	MPU6050_Init(com_porotc, imu_config);
#endif
}

void IMU_Read(){
#ifdef USE_MPU6050
	MPU6050_ReadData(&sensorData);
#endif
}

void IMU_Compose(){
#ifdef USE_MPU6050
	MPU6050_Compose_Export(&sensorData);
#endif
}

