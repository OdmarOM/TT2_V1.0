#include "Linker.h"
#include "user.h"
extern SerialUSART2 usart;
extern osMutexId mid_serial;

Linker::Linker()
{
	int Sampling=650;
	this->Dt_us=1000000/Sampling;
	
	this->Current_Command=0;
	this->Speed=0;
	this->Current_State=0;
	
	for(int i=0;i<6;i++){
	this->Current_Position[i]=0;
	}
	this->Pause=true;
}

void 	Linker::Set_Current_State(int Command)
{
	this->Current_State=Command;
}

int Linker::Get_Current_State()
{
	return(this->Current_State);
}

void 	Linker::Set_Current_Command(int Command)
{
		this->Current_Command=Command;
}

int 	Linker::Get_Current_Command()
{
		
	return(this->Current_Command);
}

		
void	Linker::Set_Speed(float speed)
{
	if(speed>1)	this->Speed=speed;
	else speed=1;
}

float	Linker::Get_Speed()
{
	return(this->Speed);
}

void 	Linker::Set_Current_Position(float Position,int i)
{
		this->Current_Position[i]=Position;
}

float	Linker::Get_Current_Position(int i)
{
	return(this->Current_Position[i]);
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


