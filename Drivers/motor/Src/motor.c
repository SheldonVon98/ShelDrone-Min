/*
 * motor.c
 *
 *  Created on: Jul 17, 2021
 *      Author: sheldonvon
 */

#include "motor.h"

__IO uint32_t *M1, *M2, *M3, *M4;
uint16_t *throttleManual;

void motorInit(TIM_HandleTypeDef *tim, uint16_t *throttleChannel){
	M1 = &tim->Instance->CCR1;
	M2 = &tim->Instance->CCR2;
	M3 = &tim->Instance->CCR3;
	M4 = &tim->Instance->CCR4;
	throttleManual = throttleChannel;
}

void setMotorThrottle(__IO uint32_t *m, uint16_t throttle){
	if(controlStatus.flightBaseStatus == STANDBY || controlStatus.flightBaseStatus == STARTING || controlStatus.flightBaseStatus == SHUTTING){
		*m = MOTOR_STOP;
	} else {
#ifdef AUTO_TAKEOFF_LAND
		if(controlStatus.flightBaseStatus == READY){
			throttle = MOTOR_READY;
		}else if(controlStatus.flightBaseStatus == TAKEOFF){
		}
#else
		if(controlStatus.flightBaseStatus == READY || controlStatus.flightBaseStatus == TAKEOFF){
			if(throttle < MOTOR_READY) throttle = MOTOR_READY;
			else if(throttle > MOTOR_MAX) throttle = MOTOR_MAX;
		}
#endif
		*m = throttle;
	}
}

void mapChannel2Motor(){
	*M1 = *throttleManual;
	*M2 = *throttleManual;
	*M3 = *throttleManual;
	*M4 = *throttleManual;
}

void setMotors3D(int16_t pitch,
				int16_t roll,
				int16_t yaw){

	setMotorThrottle(M1, *throttleManual+pitch-roll-yaw);
	setMotorThrottle(M2, *throttleManual+pitch+roll+yaw);
	setMotorThrottle(M3, *throttleManual-pitch-roll+yaw);
	setMotorThrottle(M4, *throttleManual-pitch+roll-yaw);

}

void setMotors6D(int16_t pitch,
				int16_t roll,
				int16_t yaw,
				int16_t x,
				int16_t y,
				int16_t z){

}
