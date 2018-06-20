#include "Joint.h"
#include "usart.h"
#include <math.h>

extern SerialUSART2 usart;
extern Linker Linker;

void JointInterface::SetRelativePosition(float Angle)
{	
	int Number_of_Pulses=this->GetMotorPulses(Angle);
	
	
	
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(this->Contraction);
	else
		this->Joint_Motor.Move_Step(!this->Contraction);
		for(int i=0; i<700;i++){} 
	}
	Linker.Set_Current_Position(Linker.Current_Position[this->Joint_Motor.Motor_Data.Id]+Angle,this->Joint_Motor.Motor_Data.Id);
	//usart.printf("%i",Number_of_Pulses);
}

void JointInterface::SetAbsolutePosition(float Angle)
{	
	int Relative_Angle=Angle-Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	this->SetRelativePosition(Relative_Angle);
}
//*********************************************************

void JointInterface::SetRelativePosition(float Angle,int Dt_us)
{	
	int Number_of_Pulses=this->GetMotorPulses(Angle);

	float time_span_of_pulse=8.7; //in microseconds;
	
	float delayus=((Dt_us-Number_of_Pulses*time_span_of_pulse)/Number_of_Pulses)*100; 
	//we muliply by 100 to get houndreds of nanoseconds beacouse thats what each iteration of the for last
			
	if(delayus<0)
			{
				Linker.Pause_Routine();
				while(delayus<0)
				{	Dt_us+=50;
					delayus=((Dt_us-Number_of_Pulses*time_span_of_pulse)/Number_of_Pulses)*100; 
				}
				Linker.Dt_us=Dt_us;
				usart.printf("%i",Dt_us);
				Linker.Start_Routine();
			}
			else
			{
			}
			
	for(int i=0;i<=Number_of_Pulses;i++)
	{
	if(Angle<0) 
		this->Joint_Motor.Move_Step(!this->Contraction);
	else
		this->Joint_Motor.Move_Step(this->Contraction);
		for(int i=0; i<delayus*Linker.Get_Speed();i++){} 
	}
	usart.printf("\n		%i",Number_of_Pulses);
	Linker.Set_Current_Position(Linker.Current_Position[this->Joint_Motor.Motor_Data.Id]+Angle,this->Joint_Motor.Motor_Data.Id);
	
}

void JointInterface::SetAbsolutePosition(float Angle,int Dt_us)
{	
	int Relative_Angle=Angle-Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	this->SetRelativePosition(Relative_Angle,Dt_us);
}

//intervalo total / dt = speed
//**************************************************

Hip_Joint::Hip_Joint(Joint_Motor_Id Motor_Id) : Contraction(Clockwise)
{
		usart.puts("\n					Hip Created");
	
		this->Joint_Motor= Motor(Motor_Id);
		this->Anatomic_Position=0;
}

int Hip_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

	I_A = -0.0002*pow(Initial_Angle,3) + 0.0072*pow(Initial_Angle,2) + 2.4268*Initial_Angle + 61.751;
	F_A = -0.0002*pow(Initial_Angle+Angle,3) + 0.0072*pow(Initial_Angle+Angle,2) + 2.4268*(Initial_Angle+Angle)+ 61.751;
	Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}

void Hip_Joint::SetHome()
{

Linker.Set_Current_Position(-26,this->Joint_Motor.Motor_Data.Id);
}
//**************************************************
Knee_Joint::Knee_Joint(Joint_Motor_Id Motor_Id):Contraction(Clockwise)
{
			usart.puts("\n					Knee Created");
	this->Joint_Motor=Motor(Motor_Id);
	this->Anatomic_Position=0;
}

int Knee_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);

		I_A = 0.0002*pow(Initial_Angle,3) - 0.0141*pow(Initial_Angle,2) + 1.6777*Initial_Angle - 0.0831;
		F_A =  0.0002*pow(Initial_Angle+Angle,3) - 0.0141*pow(Initial_Angle+Angle,2) + 1.6777*(Initial_Angle+Angle) - 0.0831;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}

void Knee_Joint::SetHome()
{

Linker.Set_Current_Position(0,this->Joint_Motor.Motor_Data.Id);
}

//**************************************************
Ankle_Joint::Ankle_Joint(Joint_Motor_Id Motor_Id):Contraction(Clockwise)
{
				usart.puts("\n					Ankle Created");
	this->Joint_Motor=Motor(Motor_Id);
	this->Anatomic_Position=90;
}

int Ankle_Joint::GetMotorPulses(float Angle)
{ 
	float I_A,F_A;
	int Motor_Pulses;
	float Initial_Angle=Linker.Get_Current_Position(this->Joint_Motor.Motor_Data.Id);
	
		I_A = -1.1205*Initial_Angle + 138.33;
		F_A =	-1.1205*(Initial_Angle+Angle) + 138.33;
		Motor_Pulses=((F_A-I_A)/5)*1250;

	return(abs(Motor_Pulses));
}

void Ankle_Joint::SetHome()
{

Linker.Set_Current_Position(70,this->Joint_Motor.Motor_Data.Id);
}
//section to calculate the delay based on the velocity graph of the trajectory
								
								/*float in_min=0; //the inputs represent the values from the graph
								float in_max=7.5;
								float out_min=20;// the outputs are the values we are mapping to and corresponds to the
								float out_max=0;	// time of the delay, less delay faster speed.
							
								int delay=(Speed - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;*/


