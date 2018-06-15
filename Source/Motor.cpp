#include "Motor.h"
#include "usart.h"
#include "cmsis_os.h"
#include "stm32f10x.h"

#include "Utilities.h"
#include "HardwareInit.h"
#include "Delay.h"
#include "Linker.h"

extern SerialUSART2 usart;
//**************************************************
Motor::Motor(int Motornum)
{
			Motor_Data=Config_motor[Motornum];
			speed=0;
	usart.printf("\n						Motor %i Created",this->Motor_Data.Id);
}

Motor::~Motor()
{
usart.printf("\n						Motor %i Deleted",this->Motor_Data.Id);
}


void Motor::Set_Speed(int Value)
{
	speed=Value;
}


void Motor::Move_Step(int Type,float speed)
{
	/*if(Type==Clockwise)	GPIO_ResetBits(Motor_Data.Dir.Puerto,Motor_Data.Dir.Pin);
	else							GPIO_SetBits(Motor_Data.Dir.Puerto,Motor_Data.Dir.Pin);
	
		//section to calculate the delay based on the velocity graph of the trajectory
		
		float in_min=0; //the inputs represent the values from the graph
		float in_max=7.5;
		float out_min=20;// the outputs are the values we are mapping to and corresponds to the
		float out_max=0;	// time of the delay, less delay faster speed.
	
		int delay=(speed - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	
		for(int i=0; i<4;i++){
		GPIO_SetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		DelayUs(1);
		GPIO_ResetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		DelayUs(1);
		}
		DelayUs(delay);*/
}

//**************************************************




