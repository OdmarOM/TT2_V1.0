#include "Joint.h"
#include "usart.h"
#include <math.h>

extern SerialUSART2 usart;
extern Linker Linker;

void JointInterface::SetRelativePosition(float Angle)
{	
	int Number_of_Pulses=this->GetMotorPulses(Angle);
	int time_span_of_pulse=15; //in microseconds;
	
	int delayus=((Linker.Dt_us-Number_of_Pulses*time_span_of_pulse)/Number_of_Pulses)*Linker.Get_Speed(); // 15 
	
							//section to calculate the delay based on the velocity graph of the trajectory
								
								/*float in_min=0; //the inputs represent the values from the graph
								float in_max=7.5;
								float out_min=20;// the outputs are the values we are mapping to and corresponds to the
								float out_max=0;	// time of the delay, less delay faster speed.
							
								int delay=(Speed - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;*/
	
	
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(this->Contraction);
	else
		this->Joint_Motor.Move_Step(!this->Contraction);
	
		//DelayUs(delayus);
	}
	usart.printf("%i",this->Joint_Motor.Motor_Data.Id);
}

void JointInterface::SetAbsolutePosition(float Angle)
{	
	int Relative_Angle=Angle-Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	this->SetRelativePosition(Relative_Angle);
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
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

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
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

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
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	
		I_A = -1.1205*Initial_Angle + 138.33;
		F_A =	-1.1205*(Initial_Angle+Angle) + 138.33;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(Motor_Pulses);
}

