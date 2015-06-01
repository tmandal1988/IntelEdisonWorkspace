
#include "mraa.hpp"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <signal.h>

int running = 0;

void sig_handler(int signo) {
	if (signo == SIGINT) {
		printf("closing spi nicely\n");
		running = -1;
	}
}

void thread1(){

	std::cout<<"Thread1 created"<<std::endl;
}

int main() {

	signal(SIGINT, sig_handler);

	std::thread t1(thread1);
	t1.join();

	return MRAA_SUCCESS;
}
