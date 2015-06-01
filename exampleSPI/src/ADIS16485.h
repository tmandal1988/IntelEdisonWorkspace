/*
 * ADIS16485.h
 *
 *  Created on: May 26, 2015
 *      Author: Tanmay
 */

#ifndef ADIS16485_H_
#define ADIS16485_H_

#include "mraa.hpp"
#include <iostream>
#include <unistd.h>

class ADIS16485 {
private:

	union  __attribute__((__aligned__)) byte2int16  {
		uint8_t byteArray[12];
		int16_t data[6];
	}__attribute__ ((__packed__)) ;

	union __attribute__((__aligned__)) byte2int32   {
		uint8_t byteArray[24];
		int32_t data[6];
	}__attribute__ ((__packed__));

	static const uint8_t xgyrolow = 0x10;
	static const uint8_t xgyrohigh = 0x12;
	static const uint8_t ygyrolow = 0x14;
	static const uint8_t ygyrohigh = 0x16;
	static const uint8_t zgyrolow = 0x18;
	static const uint8_t zgyrohigh = 0x1A;

	static const uint8_t xaccellow = 0x1C;
	static const uint8_t xaccelhigh = 0x1E;
	static const uint8_t yaccellow = 0x20;
	static const uint8_t yaccelhigh = 0x22;
	static const uint8_t zaccellow = 0x24;
	static const uint8_t zaccelhigh = 0x26;

	static const uint8_t xdeltaAngleLow = 0x40;
	static const uint8_t xdeltaAngleHigh = 0x42;
	static const uint8_t ydeltaAngleLow = 0x44;
	static const uint8_t ydeltaAngleHigh = 0x46;
	static const uint8_t zdeltaAngleLow = 0x48;
	static const uint8_t zdeltaAngleHigh = 0x4A;

	static const uint8_t xdeltaVelLow = 0x4C;
	static const uint8_t xdeltaVelHigh = 0x4E;
	static const uint8_t ydeltaVelLow = 0x50;
	static const uint8_t ydeltaVelHigh = 0x52;
	static const uint8_t zdeltaVelLow = 0x54;
	static const uint8_t zdeltaVelHigh = 0x56;

	mraa::Spi* imuSPI;

	mraa_gpio_context cs0;

public:
	ADIS16485();
	int initializeIMU();
	void getIMUdataLowPrecision(float IMUdataLowPrecision[]);
	void getIMUdataHighPrecision(float IMUdataHighPrecision[]);
	~ADIS16485();
};

#endif /* ADIS16485_H_ */
