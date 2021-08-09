/*
 * controlStatus.h
 *
 *  Created on: 18 Jul 2021
 *      Author: sheldonvon
 */

#ifndef STATUS_CONTROLSTATUS_INC_CONTROLSTATUS_H_
#define STATUS_CONTROLSTATUS_INC_CONTROLSTATUS_H_

#include "receiver.h"
#include <stdbool.h>

enum FLIGHT_BASE_STATUS{
	STANDBY,
	STARTING,
	READY,
	TAKEOFF,
	LANDING,
	SHUTTING
};

enum AUTO_STATUS{
	MANUAL,
	ALTITUDE_HOLD,
	ALTITUDE_POSITION_HOLD,
};

typedef struct{
	enum FLIGHT_BASE_STATUS flightBaseStatus;
	enum AUTO_STATUS autoStatus;
}ControlStatus;

extern ControlStatus controlStatus;

void detectControlStatus();

#endif /* STATUS_CONTROLSTATUS_INC_CONTROLSTATUS_H_ */
