#ifndef _MOTOR_H
#define _MOTOR_H

#include "Utilities.h"
#include "HardwareInit.h"
#include "Delay.h"

class Motor
{
	private:
		int speed;
		MotorData Motor_Data;
	
	public:
		Motor(int Motornum);
		//void Calibrate();	
		void Go_To_Angle();
		void Set_Speed(int Value);
		void Get_Angle();
		void Move_Step();
		~Motor(){};
};

#endif
