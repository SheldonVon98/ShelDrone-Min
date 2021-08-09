/*
 * controlStatus.c
 *
 *  Created on: 18 Jul 2021
 *      Author: sheldonvon
 */

#include "controlStatus.h"

ControlStatus controlStatus;

void controlStatusInit(){
	controlStatus.flightBaseStatus = STANDBY;
	controlStatus.autoStatus = MANUAL;
}

#ifdef AUTO_TAKEOFF_LAND
void detectControlStatus(){

	switch(controlStatus.flightBaseStatus){
	case STANDBY:
		if(ATMIN(channels[THROTTLE]) && ATMAX(channels[YAW]) && ATMAX(channels[PITCH]) && ATMIN(channels[ROLL])){
			controlStatus.flightBaseStatus = STARTING;
		}
		break;
	case STARTING:
		if(ATMID(channels[THROTTLE]) && ATMID(channels[YAW]) && ATMID(channels[PITCH]) && ATMID(channels[ROLL])){
			controlStatus.flightBaseStatus = READY;
		}
		break;
	case READY:
		if(false){
			controlStatus.flightBaseStatus = TAKEOFF;
		} else if(ATMIN(channels[THROTTLE])){
			controlStatus.flightBaseStatus = SHUTTING;
		}
		break;
	case TAKEOFF:
		break;
	case LANDING:
		break;
	case SHUTTING:
		if(ATMID(channels[THROTTLE]) && ATMID(channels[YAW])){
			controlStatus.flightBaseStatus = STANDBY;
		}
		break;
	}
	if(ATMIN(channels[SWITCHER])) controlStatus.autoStatus = MANUAL;
	else if(ATMID(channels[SWITCHER])) controlStatus.autoStatus = ALTITUDE_HOLD;
	else if(ATMAX(channels[SWITCHER])) controlStatus.autoStatus = ALTITUDE_POSITION_HOLD;
}
#else
void detectControlStatus(){
	switch(controlStatus.flightBaseStatus){
	case STANDBY:
		if(ATMIN(channels[THROTTLE]) && ATMAX(channels[YAW])){
			controlStatus.flightBaseStatus = STARTING;
		}
		break;
	case STARTING:
		if(ATMIN(channels[THROTTLE]) && ATMID(channels[YAW])){
			controlStatus.flightBaseStatus = READY;
		}
		break;
	case READY:
		if(!ATMIN(channels[THROTTLE])){
			controlStatus.flightBaseStatus = TAKEOFF;
		} else if(ATMIN(channels[THROTTLE]) && ATMIN(channels[YAW])){
			controlStatus.flightBaseStatus = SHUTTING;
		}
		break;
	case TAKEOFF:
		if(ATMIN(channels[THROTTLE])){
			controlStatus.flightBaseStatus = READY;
		}
		break;
	case LANDING:
		break;
	case SHUTTING:
		if(ATMIN(channels[THROTTLE]) && ATMIN(channels[YAW])){
			controlStatus.flightBaseStatus = STANDBY;
		}
		break;
	}
}
#endif
