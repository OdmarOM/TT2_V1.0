#include "main.h"

extern osMutexId mid_serial;
extern osThreadId robot_thread_id;
extern Linker Linker;

int main()
{
	int command;
	DelayInit();
	GPIO_Initialize();
	usart.printf("\n\n::Main::");
	osKernelInitialize();
	InitThreads();
	osKernelStart();
	UsartUser A;
	
		while(1){			
				
		
	command=A.GetCommand();
	if(command==calibration) 
		{
			
		}
	else if(command==pause) 
		{
			
		usart.printf("\n\n apagado");
		}
	else if(command==gate) 
		{ 
			osSignalSet(robot_thread_id, 0x01);
		}
		else 
			{	
			}
	}
}	

