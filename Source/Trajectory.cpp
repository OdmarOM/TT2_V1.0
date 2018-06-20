#include "Trajectory.h"
#include "Usart.h"
#include "math.h"

extern SerialUSART2 usart;
extern float Current_Angles[6];


void TrajectoryInterface :: SetStartPoint(int Start_Point){

	if (Start_Point>this->Min_Trajectory_Point || Start_Point <this->Max_Trajectory_Point)
		{
			this->StartPoint=Start_Point;
			usart.puts("Start Point Ingresado");
		}
	else 
			usart.puts("Start Point Invalido");
	
}


//*******************************************************************************************************
Home_Trajectory::Home_Trajectory() 
{
	usart.puts("\n					Home Trajectory Created");
	this->Min_Trajectory_Point=0;
	this->Max_Trajectory_Point=100;
	this->StartPoint=0;
	this->Trajectory_Resolution=5;
}


void Home_Trajectory::Perform_Trajectory(JointInterface* Joint)
{	
	
	//			|| !(GPIO_ReadInputData(this->Joint->Joint_Motor.Motor_Data.LimExt.Puerto) & this->Joint->Joint_Motor.Motor_Data.LimExt.Pin) )// Señal de los LimitSwitch
		//^^^ Codigo de control de los limit switch
	while(!GPIO_ReadInputDataBit(Config_motor[4].LimCont.Puerto,Config_motor[4].LimCont.Pin))
	{
		Joint->SetRelativePosition(-1);			
	}
	Joint->SetHome();
		
}

float Home_Trajectory::GetTrajectoryAngle(float x)
{
	float Angle;
	
	Angle=-2*x;
	
	return(Angle);

}

int Home_Trajectory::GetTrajectorySpeed(float x)
{
	float Speed;
	
	Speed=2;
	
	return(Speed);

}


Home_Trajectory::~Home_Trajectory()
{
	
	usart.puts("\n					Home Trajectory Deleted");
}

//*******************************************************************************************************
Anatomic_Trajectory::Anatomic_Trajectory()
{
	usart.puts("\n					Anatomic Trajectory Created");
}

void Anatomic_Trajectory::Perform_Trajectory(JointInterface* Joint )
{	int i=0;
	while(i<3)
	{
	//this->Joint->Joint_Motor.Move_Step(Clockwise);
		i++;
	}
}

Anatomic_Trajectory::~Anatomic_Trajectory()
{
	
	usart.puts("\n					Anatomic Trajectory Deleted");
}

//********************************************************************************************************
Null_Trajectory::Null_Trajectory()
{
	usart.puts("\n					Null Trajectory Created");
}

Null_Trajectory::~Null_Trajectory()
{
	usart.puts("\n					Null Trajectory Deleted");
}

void Null_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	usart.printf("\n				Performing null trajectory");
}

//******************************************************************************************************
Hip_Gate_Trajectory::Hip_Gate_Trajectory()
{
		//float Position_Vector[65]={113.25, 111.75,110.2,108.7,107.2,105.2214013,103.9401477,102.2501131,99.71437293,96.96849033,93.7209228,90.4287798,87.15471392,83.89662553,80.4146184,76.97489121,73.55688623,70.10277402,66.82404143,63.57385477,60.47434741,57.53143226,54.62580698,51.82297032,48.92142564,45.96483943,43.15867456,40.43383759,37.70091587,35.04026923,32.69029388,30.62537915,28.91960297,27.67565997,26.81633312,26.17200186,25.814588,25.97699067,26.91057873,28.8397692,31.64874536,35.5934765,40.18912979,45.65320312,51.55350184,58.13683653,64.63506027,71.43291199,77.88053235,84.12047514,90.10795582,95.59281781,100.6394066,105.04194,108.9676772,112.1570168,114.6485675,116.6978531,117.6186305,118.2863836,118.2723582,117.6563129,116.7691332,115.5297133,114.475844};
		//=Hip_Gate_Points;
	usart.printf("\n					Hip Trajectory Created");
			
}
Hip_Gate_Trajectory::~Hip_Gate_Trajectory()
{
	usart.printf("\n					Hip Trajectory Deleted");
}

void Hip_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
		for(int i=0; i<5;i++)
		{
			usart.printf("\n			111111111");
		}
	
}


//****************************************************************************************************


