#ifndef _USER_H
#define _USER_H

#include "OsObjects.h"
#include "Usart.h"

//#include "retarget_stm32f3.h"

typedef enum{ok, error}Status;
typedef enum{not_a_command=-1, calibration=1, home, anatomic, pause, stop}commandMapEnumType;
/*
Estructura de datos de estado hacia la interfaz
*/
typedef struct
{
	Status state;
	int Position;
	int Percentage;
}StatusDataType;

typedef struct
{
	int command_index;
	char command;
}CommandMapType;

const CommandMapType CommandMap[15] =
{ 
	{1,'c'},		//calibration
	{2,'h'},		//home
	{3,'a'},		//anatomic
	{4,'p'},
	{5,'s'},
};

class UserInterface
{
	public:		
		virtual int GetCommand()=0;
		virtual void SendData(StatusDataType status)=0;
};

class UsartUser : public UserInterface
{
	private:
		SerialUSART2 serial;
	public:
		UsartUser();
		virtual int GetCommand();
		virtual void SendData(StatusDataType status);
};

#endif // _USER_H

