/*
 * debugSignal.h
 *
 *  Created on: Jul 21, 2021
 *      Author: sheldonvon
 */

#ifndef STATUS_INC_DEBUG_H_
#define STATUS_INC_DEBUG_H_

#include "config.h"
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "usbd_cdc_if.h"
#include "sensors.h"

#define TRANS_START_HIGH		0
#define TRANS_START_LOW			1

#define TRANS_GYRO_ROLL_HIGH	2
#define TRANS_GYRO_ROLL_LOW		3
#define TRANS_GYRO_PITCH_HIGH	4
#define TRANS_GYRO_PITCH_LOW	5
#define TRANS_GYRO_YAW_HIGH		6
#define TRANS_GYRO_YAW_LOW		7

#define TRANS_ANG_ROLL_HIGH		8
#define TRANS_ANG_ROLL_LOW		9
#define TRANS_ANG_PITCH_HIGH	10
#define TRANS_ANG_PITCH_LOW		11
#define TRANS_ANG_YAW_HIGH		12
#define TRANS_ANG_YAW_LOW		13


#define DS_LED_B		GPIO_PIN_13
#define DS_LED_G		GPIO_PIN_14
#define DS_LED_R		GPIO_PIN_15
#define DS_RISE(n) 	GPIOC->ODR |= n
#define DS_FALL(n) 	GPIOC->ODR &= ~n

typedef struct{
	uint8_t high;
	uint8_t low;
} DoubleChar;

typedef struct{
	uint16_t pin;
	uint8_t count;
	uint8_t switchPoint;
	bool on;
	bool start;
}LEDData;

/*
 * Signal full period: 2000ms
 * Interval: 500ms
 * Blink Period: 2000ms-500ms=1500ms
 * Time unit: 50ms
 * */
#define LED_FULL_PERIOD 	2000
#define LED_INTERVAL 		400
#define LED_UNIT_PERIOD 	20
#define LED_BLINK_PERIOD 	(LED_FULL_PERIOD-LED_INTERVAL)/LED_UNIT_PERIOD
#define LED_FREQ_MAX		10
#define LED_FREQ_Min		1

enum LED{
	RED,
	GREEN,
	BLUE,
	ALL_LED
};

void LEDSignalInit();
void _singleLEDSignal(LEDData *led);
void LEDSignal();
void _LEDStartStop(LEDData *led, bool start);
void LEDToggle(enum LED led, bool start);
void _setSingleLEDTimes(LEDData *led, uint8_t times);
void LEDSetTimes(enum LED led, uint8_t times);

void print(char *fmt, ...);
void printFloat(float f);
void d2c(double d, DoubleChar *dc);
void fillDebugBuffer();
void transmitDebugData();
#endif /* STATUS_INC_DEBUG_H_ */
