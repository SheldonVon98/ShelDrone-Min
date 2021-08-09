/*
 * debug.c
 *
 *  Created on: Jul 22, 2021
 *      Author: sheldonvon
 */


#include "debug.h"


char transfer_buffer[14];
extern USBD_HandleTypeDef hUsbDeviceFS;
DoubleChar dc;
double check;
int16_t temp;

LEDData ledR, ledG, ledB;

void LEDSignalInit(){
	DS_FALL(DS_LED_R);
	DS_FALL(DS_LED_G);
	DS_FALL(DS_LED_B);
	ledR.pin = DS_LED_R;
	ledG.pin = DS_LED_G;
	ledB.pin = DS_LED_B;
	LEDToggle(ALL_LED, false);
}

void _singleLEDSignal(LEDData *led){
	if(led->start){
		if(led->count <= LED_BLINK_PERIOD){
			if(led->count>0&&led->count%led->switchPoint==0) led->on = !led->on;
		} else led->on = false;
		if(led->on) DS_RISE(led->pin);
		else DS_FALL(led->pin);
		if(led->count == LED_FULL_PERIOD/LED_UNIT_PERIOD){
			led->count = 0;
			led->on = true;
		} else {
			led->count++;
		}
	}
}

void LEDSignal(){
	_singleLEDSignal(&ledR);
	_singleLEDSignal(&ledG);
	_singleLEDSignal(&ledB);
}

void _LEDStartStop(LEDData *led, bool start){
	led->start = start;
	led->on = start;
}

void LEDToggle(enum LED led, bool start){
	switch (led) {
		case RED:
			_LEDStartStop(&ledR, start);
			break;
		case GREEN:
			_LEDStartStop(&ledG, start);
			break;
		case BLUE:
			_LEDStartStop(&ledB, start);
			break;
		case ALL_LED:
			_LEDStartStop(&ledR, start);
			_LEDStartStop(&ledG, start);
			_LEDStartStop(&ledB, start);
			break;
	}
}

void _setSingleLEDTimes(LEDData *led, uint8_t times){
	led->switchPoint = LED_BLINK_PERIOD/(times*2-1);
}

void LEDSetTimes(enum LED led, uint8_t times){
	if(times > LED_FREQ_MAX) times = LED_FREQ_MAX;
	if(times < LED_FREQ_Min) times = LED_FREQ_Min;
	switch (led) {
		case RED:
			_setSingleLEDTimes(&ledR, times);
			break;
		case GREEN:
			_setSingleLEDTimes(&ledG, times);
			break;
		case BLUE:
			_setSingleLEDTimes(&ledB, times);
			break;
		case ALL_LED:
			_setSingleLEDTimes(&ledR, times);
			_setSingleLEDTimes(&ledG, times);
			_setSingleLEDTimes(&ledB, times);
			break;
	}
}

void print(char *fmt, ...){
	while(((USBD_CDC_HandleTypeDef*)(hUsbDeviceFS.pClassData))->TxState!=USBD_OK);
	va_list args;
	va_start(args, fmt);
	vsprintf((char *)transfer_buffer, fmt, args);
	va_end(args);
	CDC_Transmit_FS((uint8_t *)transfer_buffer, strlen(transfer_buffer));
}

void printFloat(float f){
	d2c(f, &dc);
	print("%d.%d", dc.high, dc.low);
}

void d2c(double d, DoubleChar *dc){
	temp = d*100;
	dc->low = temp & 0xFF;
	dc->high = (temp >> 8) & 0xFF;
}

void fillDebugBuffer(){
	transfer_buffer[TRANS_START_HIGH] = 'S';
	transfer_buffer[TRANS_START_LOW] = 'V';

	d2c(sensorData.gyro_roll, &dc);
	transfer_buffer[TRANS_GYRO_ROLL_HIGH] = dc.high;
	transfer_buffer[TRANS_GYRO_ROLL_LOW] = dc.low;

	d2c(sensorData.gyro_pitch, &dc);
	transfer_buffer[TRANS_GYRO_PITCH_HIGH] = dc.high;
	transfer_buffer[TRANS_GYRO_PITCH_LOW] = dc.low;

	d2c(sensorData.gyro_yaw, &dc);
	transfer_buffer[TRANS_GYRO_YAW_HIGH] = dc.high;
	transfer_buffer[TRANS_GYRO_YAW_LOW] = dc.low;


	d2c(sensorData.angle_roll, &dc);
	transfer_buffer[TRANS_ANG_ROLL_HIGH] = dc.high;
	transfer_buffer[TRANS_ANG_ROLL_LOW] = dc.low;
//	check = (double)((int16_t)(dc.high << 8 | dc.low))/100;


	d2c(sensorData.angle_pitch, &dc);
	transfer_buffer[TRANS_ANG_PITCH_HIGH] = dc.high;
	transfer_buffer[TRANS_ANG_PITCH_LOW] = dc.low;

	d2c(sensorData.angle_yaw, &dc);
	transfer_buffer[TRANS_ANG_YAW_HIGH] = dc.high;
	transfer_buffer[TRANS_ANG_YAW_LOW] = dc.low;
}

void transmitDebugData(){
	fillDebugBuffer();
	if(((USBD_CDC_HandleTypeDef*)(hUsbDeviceFS.pClassData))->TxState==USBD_OK){
		CDC_Transmit_FS((uint8_t *)transfer_buffer, 14);
	}
}

