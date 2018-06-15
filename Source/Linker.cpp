#include "Linker.h"
#include "user.h"
extern SerialUSART2 usart;
extern osMutexId mid_serial;

Linker::Linker()
{
	this->Previous_Command=0;
	this->Current_Command=0;
	this->Speed=0;
	this->Current_Routine_Command=0;
	
	for(int i=0;i<6;i++){
	this->Current_Position[i]=0;
	this->Future_Position[i]=0;
	}
	this->Pause=true;
	this->Routine=NULL;
}

void 	Linker::Set_Current_Routine_Command(int Command)
{
	this->Current_Routine_Command=Command;
}

int Linker::Get_Current_Routine_Command()
{
	return(this->Current_Routine_Command);
}

void 	Linker::Set_Current_Command(int Command)
{

			this->Previous_Command=this->Current_Command;
		this->Current_Command=Command;
	
}

int 	Linker::Get_Current_Command()
{
		
	return(this->Current_Command);
}

int 	Linker::Get_Previous_Command()
{
		
	return(this->Previous_Command);
}
		
void	Linker::Set_Speed(int speed)
{
	this->Speed=speed;
}

int	Linker::Get_Speed()
{
	return(this->Speed);
}

void 	Linker::Set_Current_Position(float Position[])
{
	for(int i=0;i<6;i++){
		this->Current_Position[i]=Position[i];
	}
}

float*	Linker::Get_Current_Position()
{
	return(this->Current_Position);
}

void 	Linker::Set_Future_Position(float Position[])
{
	for(int i=0;i<6;i++){
			this->Future_Position[i]=Position[i];
		}
}

void	Linker::Pause_Routine(void)
{
	this->Pause=true;
	
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
	usart.printf("\n			Routine Paused");
	//osMutexRelease(mid_serial);
}

void	Linker::Start_Routine(void)
{
	this->Pause=false;
	
	//osStatus status = osMutexWait(mid_serial, osWaitForever);
	//if(status == osOK)	
		usart.printf("\n			Routine Started");
	//osMutexRelease(mid_serial);
}

bool Linker::Is_Paused(void)
{
	return(this->Pause);
}


