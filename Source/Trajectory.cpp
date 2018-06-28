#include "Trajectory.h"
#include "Usart.h"
#include "math.h"

extern SerialUSART2 usart;
extern Linker Linker;


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
	this->StartPoint=65;
	this->Trajectory_Resolution=5;
}


void Home_Trajectory::Perform_Trajectory(JointInterface* Joint)
{	
	
	//			|| !(GPIO_ReadInputData(this->Joint->Joint_Motor.Motor_Data.LimExt.Puerto) & this->Joint->Joint_Motor.Motor_Data.LimExt.Pin) )// Señal de los LimitSwitch
		//^^^ Codigo de control de los limit switch
	while(!GPIO_ReadInputDataBit(Joint->Joint_Motor.Motor_Data.LimCont.Puerto,Joint->Joint_Motor.Motor_Data.LimCont.Pin))
	{
		Joint->SetRelativePosition_C(-1);			
	}
	Joint->SetHome();

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
{	
	
	Joint->SetAbsolutePosition_C(Joint->Anatomic_Position);
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
	usart.printf("\n					Hip Trajectory Created");	

	this->Min_Trajectory_Point=32;
	this->Max_Trajectory_Point=97; //65 points of difference
	this->StartPoint=65;	
}


void Hip_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
//pow(x,3.)
	float y;
	float x=this->StartPoint;
	
	y=-pow(6.1632,-25)*pow(x,15)+pow(7.8123,-22)*pow(x,14)-pow(4.4507,-19)*pow(x,13)+pow(1.5015,-16)*pow(x,12)-pow(3.3320,-14)*pow(x,11)+pow(5.1157,-12)*pow(x,10)-pow(5.5676,-10)*pow(x,9)+pow(4.3303,-8)*pow(x,8)-pow(2.3967,-6)*pow(x,7)+pow(9.2940,-5)*pow(x,6)-pow(2.4564,-3)*pow(x,5)+pow(4.2402,-2)*pow(x,4)-pow(4.4661,-1)*pow(x,3)+2.5297*pow(x,2)-6.8272*x+24.843;
	Joint->SetAbsolutePosition_C(y);
	
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
		while(!Linker.Is_Paused())
		{	x+=Linker.Sampling;
			if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
			
			y=-pow(6.1632,-25)*pow(x,15)+pow(7.8123,-22)*pow(x,14)-pow(4.4507,-19)*pow(x,13)+pow(1.5015,-16)*pow(x,12)-pow(3.3320,-14)*pow(x,11)+pow(5.1157,-12)*pow(x,10)-pow(5.5676,-10)*pow(x,9)+pow(4.3303,-8)*pow(x,8)-pow(2.3967,-6)*pow(x,7)+pow(9.2940,-5)*pow(x,6)-pow(2.4564,-3)*pow(x,5)+pow(4.2402,-2)*pow(x,4)-pow(4.4661,-1)*pow(x,3)+2.5297*pow(x,2)-6.8272*x+24.843;
			Joint->SetAbsolutePosition_V(y);
		}
	}
}
//****************************************************************************************************
Knee_Gate_Trajectory::Knee_Gate_Trajectory()
{
	usart.printf("\n					Knee Trajectory Created");	

	this->Min_Trajectory_Point=25;
	this->Max_Trajectory_Point=90; //65 points of difference
	this->StartPoint=71;		
}


void Knee_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
		float y;
	float x=this->StartPoint;
	
	y=-pow(1.2742,-23)*pow(x,15)+pow(1.3881,-20)*pow(x,14)-pow(6.8125,-18)*pow(x,13)+pow(1.9889,-15)*pow(x,12)-pow(3.8419,-13)*pow(x,11)+pow(5.1675,-11)*pow(x,10)-pow(4.9605,-9)*pow(x,9)+pow(3.4274,-7)*pow(x,8)-pow(1.6985,-5)*pow(x,7)+pow(5.9502,-4)*pow(x,6)-pow(1.4358,-2)*pow(x,5)+pow(2.2914,-1)*pow(x,4)-2.2682*pow(x,3)+12.436*pow(x,2)-29.648*x+25.153;
	Joint->SetAbsolutePosition_C(y);
	
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
		while(!Linker.Is_Paused())
		{	x+=Linker.Sampling;
			if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
			
			y=-pow(1.2742,-23)*pow(x,15)+pow(1.3881,-20)*pow(x,14)-pow(6.8125,-18)*pow(x,13)+pow(1.9889,-15)*pow(x,12)-pow(3.8419,-13)*pow(x,11)+pow(5.1675,-11)*pow(x,10)-pow(4.9605,-9)*pow(x,9)+pow(3.4274,-7)*pow(x,8)-pow(1.6985,-5)*pow(x,7)+pow(5.9502,-4)*pow(x,6)-pow(1.4358,-2)*pow(x,5)+pow(2.2914,-1)*pow(x,4)-2.2682*pow(x,3)+12.436*pow(x,2)-29.648*x+25.153;
			Joint->SetAbsolutePosition_V(y);
		}
	}
	
}
//****************************************************************************************************
Ankle_Gate_Trajectory::Ankle_Gate_Trajectory()
{
	usart.printf("\n					Ankle Trajectory Created");		
}


void Ankle_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
		float y;
	float x=this->StartPoint;
	
	y=-pow(1.9493,-23)*pow(x,15)+pow(1.9219,-20)*pow(x,14)-pow(8.5355,-18)*pow(x,13)+pow(2.2548,-15)*pow(x,12)-pow(3.9398,-13)*pow(x,11)+pow(4.7903,-11)*pow(x,10)-pow(4.1510,-9)*pow(x,9)+pow(2.5825,-7)*pow(x,8)-pow(1.1472,-5)*pow(x,7)+pow(3.5742,-4)*pow(x,6)-pow(7.5643,-3)*pow(x,5)+pow(1.0321,-1)*pow(x,4)-pow(8.3086,-1)*pow(x,3)+3.3186*pow(x,2)-4.5541*x+ 97.195;
	Joint->SetAbsolutePosition_C(y);
	
	while(!Linker.Is_Performing())
	{} //wait until starts perfomring
		
	while(Linker.Is_Performing())
	{
		while(!Linker.Is_Paused())
		{	x+=Linker.Sampling;
			if(x>this->Max_Trajectory_Point)	x=this->Min_Trajectory_Point;
			
			y=-pow(1.9493,-23)*pow(x,15)+pow(1.9219,-20)*pow(x,14)-pow(8.5355,-18)*pow(x,13)+pow(2.2548,-15)*pow(x,12)-pow(3.9398,-13)*pow(x,11)+pow(4.7903,-11)*pow(x,10)-pow(4.1510,-9)*pow(x,9)+pow(2.5825,-7)*pow(x,8)-pow(1.1472,-5)*pow(x,7)+pow(3.5742,-4)*pow(x,6)-pow(7.5643,-3)*pow(x,5)+pow(1.0321,-1)*pow(x,4)-pow(8.3086,-1)*pow(x,3)+3.3186*pow(x,2)-4.5541*x+ 97.195;
			Joint->SetAbsolutePosition_V(y);
		}
	}
	
}
//****************************************************************************************************


