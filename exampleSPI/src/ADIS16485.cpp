/*
 * ADIS16485.cpp
 *
 *  Created on: May 27, 2015
 *      Author: Tanmay
 */

#include "ADIS16485.h"


ADIS16485::ADIS16485() {

	imuSPI = new mraa::Spi(0);

	cs0 = mraa_gpio_init(23);

	mraa_gpio_use_mmaped(cs0, 1);
	mraa_gpio_write(cs0, 1);

}

int ADIS16485::initializeIMU() {

	uint8_t page0ID[] = { 0x00, 0x80 };

	if (imuSPI == NULL || imuSPI->mode(mraa::SPI_MODE3) != MRAA_SUCCESS
			|| imuSPI->bitPerWord(16) != MRAA_SUCCESS
			|| imuSPI->frequency(1000000) != MRAA_SUCCESS) {

		std::cerr << "Can't initialize SPI" << std::endl;
		return 0;
	} else {

		imuSPI->write(page0ID, 2);
		return 1;
	}

}

void ADIS16485::getIMUdataLowPrecision(float IMUdataLowPrecision[]) {

	static uint8_t xghighc[] = { 0, xgyrohigh };
	static uint8_t yghighc[] = { 0, ygyrohigh };
	static uint8_t zghighc[] = { 0, zgyrohigh };
	static uint8_t xahighc[] = { 0, xaccelhigh };
	static uint8_t yahighc[] = { 0, yaccelhigh };
	static uint8_t zahighc[] = { 0, zaccelhigh };

	static uint8_t fake[] = { 0, 0 };

	byte2int16 recBuf;

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[0], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[2], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[4], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[6], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[8], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf.byteArray[10], 2);
	mraa_gpio_write(cs0, 1);

	IMUdataLowPrecision[0] = recBuf.data[0] * 0.02;
	IMUdataLowPrecision[1] = recBuf.data[1] * 0.02;
	IMUdataLowPrecision[2] = recBuf.data[2] * 0.02;

	IMUdataLowPrecision[3] =recBuf.data[3] * 0.00025;
	IMUdataLowPrecision[4] =recBuf.data[4] * 0.00025;
	IMUdataLowPrecision[5] =recBuf.data[5] * 0.00025;

}

void ADIS16485::getIMUdataHighPrecision(float IMUdataHighPrecision[]) {

	static uint8_t xghighc[] = { 0, xgyrohigh };
	static uint8_t xglowc[] = { 0, xgyrolow };

	static uint8_t yghighc[] = { 0, ygyrohigh };
	static uint8_t yglowc[] = { 0, ygyrolow };

	static uint8_t zghighc[] = { 0, zgyrohigh };
	static uint8_t zglowc[] = { 0, zgyrolow };

	static uint8_t xahighc[] = { 0, xaccelhigh };
	static uint8_t xalowc[] = { 0, xaccellow };

	static uint8_t yahighc[] = { 0, yaccelhigh };
	static uint8_t yalowc[] = { 0, yaccellow };

	static uint8_t zahighc[] = { 0, zaccelhigh };
	static uint8_t zalowc[] = { 0, zaccellow };

	static uint8_t fake[] = { 0, 0 };

	byte2int32 recBuf32;

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xglowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[0], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[2], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yglowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[4], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[6], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zglowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[8], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zghighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[10], 2);
	mraa_gpio_write(cs0, 1);


	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xalowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[12], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(xahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[14], 2);
	mraa_gpio_write(cs0, 1);


	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yalowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[16], 2);
	mraa_gpio_write(cs0, 1);


	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(yahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[18], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zalowc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[20], 2);
	mraa_gpio_write(cs0, 1);

	mraa_gpio_write(cs0, 0);
	imuSPI->transfer(zahighc, NULL, 2);
	imuSPI->transfer(fake, &recBuf32.byteArray[22], 2);
	mraa_gpio_write(cs0, 1);



	IMUdataHighPrecision[0] =recBuf32.data[0]*3.0518e-07;
	IMUdataHighPrecision[1] =recBuf32.data[1]*3.0518e-07;
	IMUdataHighPrecision[2] =recBuf32.data[2]*3.0518e-07;

	IMUdataHighPrecision[3] = recBuf32.data[3] * 3.8147e-09;
	IMUdataHighPrecision[4] = recBuf32.data[4] * 3.8147e-09;
	IMUdataHighPrecision[5] = recBuf32.data[5] * 3.8147e-09;

}

ADIS16485::~ADIS16485(){

	if(imuSPI){
		delete[] imuSPI;
	}
}



