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
	int Angle;
	
		while(1){			
			
			
	command=A.GetCommand();
	if(command==calibration) 
		{//GPIO_SetBits(Joint.Joint_Motor.Motor_Data.Dir.Puerto,Joint.Joint_Motor.Motor_Data.Dir.Pin);
			
		usart.printf("\n\n encendido");
		}
	else if(command==pause) 
		{//GPIO_ResetBits(Joint.Joint_Motor.Motor_Data.Rele.Puerto,Joint.Joint_Motor.Motor_Data.Rele.Pin);
			
		usart.printf("\n\n apagado");
		}
	else if(command==gate) 
		{ 
			osSignalSet(robot_thread_id, 0x01);
			/*Angle+=5;
			Joint.SetAbsolutePosition(Angle);
			GPIO_ResetBits(Joint.Joint_Motor.Motor_Data.Dir.Puerto,Joint.Joint_Motor.Motor_Data.Dir.Pin);
			for(int i=0;i<40000;i++)
			{
			Joint.Joint_Motor.Move_Step(Clockwise);
			}*/
		}
		else {
			
			/*Angle-=5;
			Joint.SetAbsolutePosition(Angle);
			GPIO_SetBits(Joint.Joint_Motor.Motor_Data.Dir.Puerto,Joint.Joint_Motor.Motor_Data.Dir.Pin);
			for(int i=0;i<5000;i++)
				{
				Joint.Joint_Motor.Move_Step(AntiClockwise);
				}*/
			
		}
	}
}	

