#ifndef _MOTOR_H
#define _MOTOR_H


#include "Delay.h"
#include "Utilities.h"
#include "HardwareInit.h"
#include <vector>


class Motor
{
	public:
		int speed;
		MotorData Motor_Data;
	
		Motor(){};
		Motor(int Motornum);
		void Go_To_Angle();
		void Set_Speed(int Value);
		void Get_Angle();
		void Move_Step(int,float);
		~Motor();
};


#endif
