#include "main.h"

extern osMutexId mid_serial;
extern osThreadId robot_thread_id;
Robot exo = Robot();

int main()
{
	usart.printf("\n\n::Main::");
	
	osKernelInitialize();
	InitThreads();
	osKernelStart();
	osSignalSet(robot_thread_id, 0x01);
	
	while(1){}
}	

