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
	while(!GPIO_ReadInputDataBit(Joint->Joint_Motor.Motor_Data.LimCont.Puerto,Joint->Joint_Motor.Motor_Data.LimCont.Pin))
	{
		Joint->SetRelativePositionA_C(-1);			
	}
	Joint->SetHome();
	Joint->SetAbsolutePositionA_C(Joint->Anatomic_Position);
		
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
	usart.printf("\n					Hip Trajectory Created");		
}


void Hip_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	//(8582424063315823*x^23)/748288838313422294120286634350736906063837462003712 - (3038523271931747*x^24)/383123885216472214589586756787577295904684780545900544 - (6487034573941711*x^25)/12554203470773361527671578846415332832204710888928069025792 - (5338735268103517*x^22)/730750818665451459101842416358141509827966271488 + (3926044151054443*x^21)/1427247692705959881058285969449495136382746624 - (3736731284028393*x^20)/5575186299632655785383929568162090376495104 + (4580587865220479*x^19)/43556142965880123323311949751266331066368 - (5875161101120683*x^18)/680564733841876926926749214863536422912 - (4036253414031573*x^17)/10633823966279326983230456482242756608 + (5002057774337971*x^16)/20769187434139310514121985316880384 - (6739337681016175*x^15)/162259276829213363391578010288128 + (2931446095000419*x^14)/633825300114114700748351602688 - (3732208955771745*x^13)/9903520314283042199192993792 + (7247913929857687*x^12)/309485009821345068724781056 - (5450779513501953*x^11)/4835703278458516698824704 + (6370187422733199*x^10)/151115727451828646838272 - (5757578681613645*x^9)/4722366482869645213696 + (3979312255033985*x^8)/147573952589676412928 - (8259513285891531*x^7)/18446744073709551616 + (1566419184440997*x^6)/288230376151711744 - (6697548905049279*x^5)/144115188075855872 + (4820951436638917*x^4)/18014398509481984 - (9004403873458841*x^3)/9007199254740992 + (669475098322331*x^2)/281474976710656 - (44755390719461*x)/8796093022208 + 8272991776358171/70368744177664
	
}
//****************************************************************************************************
Knee_Gate_Trajectory::Knee_Gate_Trajectory()
{
	usart.printf("\n					Knee Trajectory Created");		
}


void Knee_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	
	
}
//****************************************************************************************************
Ankle_Gate_Trajectory::Ankle_Gate_Trajectory()
{
	usart.printf("\n					Ankle Trajectory Created");		
}


void Ankle_Gate_Trajectory::Perform_Trajectory(JointInterface* Joint)
{
	
	
}
//****************************************************************************************************


