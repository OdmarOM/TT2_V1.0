#include "Joint.h"
#include "usart.h"
#include <math.h>

extern SerialUSART2 usart;
float Current_Angles[6]={0,0,0,0,0,0};

void JointInterface::Perform(float Angle,float Speed)
{	
	int Number_of_Pulses=this->GetMotorPulses(Angle);
	
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(this->Contraction,Speed);
	else
		this->Joint_Motor.Move_Step(!this->Contraction,Speed);
	}
	usart.printf("%i",this->Joint_Motor.Motor_Data.Id);
}

//intervalo total / dt = speed
//**************************************************

Hip_Joint::Hip_Joint(Joint_Motor_Id Motor_Id) : Contraction(Clockwise)
{
		usart.puts("\n					Hip Created");
	
		this->Joint_Motor= Motor(Motor_Id);
	
}

int Hip_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Current_Angles[this->Joint_Motor.Motor_Data.Id];

	I_A = -0.0002*pow(Initial_Angle,3) + 0.0072*pow(Initial_Angle,2) + 2.4268*Initial_Angle + 61.751;
	F_A = -0.0002*pow(Initial_Angle+Angle,3) + 0.0072*pow(Initial_Angle+Angle,2) + 2.4268*(Initial_Angle+Angle)+ 61.751;
	Motor_Pulses=((F_A-I_A)/5)*1250;

	return(Motor_Pulses);
}

//**************************************************
Knee_Joint::Knee_Joint(Joint_Motor_Id Motor_Id):Contraction(Clockwise)
{
			usart.puts("\n					Knee Created");
	this->Joint_Motor=Motor(Motor_Id);
}

int Knee_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Current_Angles[this->Joint_Motor.Motor_Data.Id];

		I_A = 0.0002*pow(Initial_Angle,3) - 0.0141*pow(Initial_Angle,2) + 1.6777*Initial_Angle - 0.0831;
		F_A =  0.0002*pow(Initial_Angle+Angle,3) - 0.0141*pow(Initial_Angle+Angle,2) + 1.6777*(Initial_Angle+Angle) - 0.0831;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(Motor_Pulses);
}

//**************************************************
Ankle_Joint::Ankle_Joint(Joint_Motor_Id Motor_Id):Contraction(Clockwise)
{
				usart.puts("\n					Ankle Created");
	this->Joint_Motor=Motor(Motor_Id);
}

int Ankle_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Current_Angles[this->Joint_Motor.Motor_Data.Id];
	
		I_A = -1.1205*Initial_Angle + 138.33;
		F_A =	-1.1205*(Initial_Angle+Angle) + 138.33;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(Motor_Pulses);
}

