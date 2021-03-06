/*Tanmay Kumar Mandal
 * Data: 05/20/2015
 * Testing the SPI functionality
 */

#include "ADIS16485.h"
#include <signal.h>
#include <eigen3/Eigen/Dense>
#include <thread>

using namespace Eigen;

int running = 0;

void sig_handler(int signo) {
	if (signo == SIGINT) {
		printf("closing spi nicely\n");
		running = -1;
	}
}

void readSerial() {

	std::cout << "Serial Reading Thread created" << std::endl;

	char recBuf[100]={0};

/*	mraa::Uart* serial1 = new mraa::Uart(0);

	if (serial1 == NULL || serial1->setBaudRate(115200) != MRAA_SUCCESS) {
		std::cout << "Failed to open serial port" << std::endl;
	}*/

	mraa_gpio_context serialMultiplex1 = mraa_gpio_init(45);
	mraa_gpio_context serialMultiplex2 = mraa_gpio_init(32);
	mraa_gpio_context serialMultiplex3 = mraa_gpio_init(15);

	mraa_gpio_write(serialMultiplex1, 0);
	mraa_gpio_write(serialMultiplex2, 0);
	mraa_gpio_write(serialMultiplex3, 0);

	mraa::Gpio* d_pin = new mraa::Gpio(26);
	if (d_pin == NULL) {
		std::cerr << "Can't create mraa::Gpio object, exiting" << std::endl;
	}

	// set the pin as input
	if (d_pin->dir(mraa::DIR_OUT) != MRAA_SUCCESS) {
		std::cerr << "Can't set digital pin as input, exiting" << std::endl;
	}

	while (running == 0) {

/*		int length=serial1->read(recBuf,1);
		std::cout<<length<<std::endl;*/

		d_pin->write(1);
		sleep(1);
		d_pin->write(0);
		sleep(1);


	}


}

int main() {

	signal(SIGINT, sig_handler);

	std::thread readSerialThread(readSerial);

	mraa::Gpio* ledOut = new mraa::Gpio(48, true, false);
	if (ledOut->dir(mraa::DIR_OUT) != MRAA_SUCCESS) {
		std::cerr << "Can't set digital pin as output, exiting" << std::endl;
		return MRAA_ERROR_UNSPECIFIED;
	}

	ADIS16485* imuObject = new ADIS16485();

	if (imuObject->initializeIMU() == 0)
		return MRAA_ERROR_UNSPECIFIED;

	ledOut->write(1);

	float IMUdataLowPrecision[6] = { 0 };
	float IMUdataHighPrecision[6] = { 0 };
	float IMUdeltaDataLowPrecision[6] = { 0 };

	std::cout<<"I am here"<<std::endl;

	while (running == 0) {

		imuObject->getIMUdataLowPrecision(IMUdataLowPrecision);
		/*printf("%g, %g, %g, %g, %g, %g \n", IMUdataLowPrecision[0],
		 IMUdataLowPrecision[1], IMUdataLowPrecision[2],
		 IMUdataLowPrecision[3], IMUdataLowPrecision[4],
		 IMUdataLowPrecision[5]);
		 */
		imuObject->getIMUdataHighPrecision(IMUdataHighPrecision);
		/*		printf("%g, %g, %g, %g, %g, %g \n", IMUdataHighPrecision[0],
		 IMUdataHighPrecision[1], IMUdataHighPrecision[2],
		 IMUdataHighPrecision[3], IMUdataHighPrecision[4],
		 IMUdataHighPrecision[5]);*/

	}

	readSerialThread.join();
	std::cout << "Thread Joined" << std::endl;

	return MRAA_SUCCESS;
}
