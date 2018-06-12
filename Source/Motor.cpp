#include "Motor.h"
#include "usart.h"
#include "cmsis_os.h"
#include "stm32f10x.h"

extern SerialUSART2 usart;
//**************************************************
Motor::Motor(int Motornum)
{
			Motor_Data=Config_motor[Motornum-1];
			speed=0;
}

//**************************************************
void Motor::Set_Speed(int Value)
{
	speed=Value;
}

//**************************************************
void Motor::Move_Step()
{
for(int i=0; i<4;i++){
		GPIO_SetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		DelayUs(1);
		GPIO_ResetBits(Motor_Data.Sig.Puerto,Motor_Data.Sig.Pin);
		DelayUs(1);
		}
		DelayUs(speed);
}

//**************************************************




