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

	/*while(!GPIO_ReadInputDataBit(Config_motor[4].LimCont.Puerto,Config_motor[4].LimCont.Pin))
		{
				usart.printf("\n\n limit");
		}*/
			
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

