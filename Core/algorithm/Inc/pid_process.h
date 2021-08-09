/*
 * pid_process.h
 *
 *  Created on: 18 Jul 2021
 *      Author: sheldonvon
 */

#ifndef ALGORITHM_PID_INC_PID_PROCESS_H_
#define ALGORITHM_PID_INC_PID_PROCESS_H_

#include "pid.h"
#include "controlStatus.h"
#include "sensors.h"

typedef struct{
	float roll;
	float pitch;
	float yaw;
} SetPoints;

void pidsInit();
void pidProcess();
void setPointReset(SetPoints *sp);

#endif /* ALGORITHM_PID_INC_PID_PROCESS_H_ */
