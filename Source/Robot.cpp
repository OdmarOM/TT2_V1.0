#include "Robot.h"
#include "cmsis_os.h"
extern SerialUSART2 usart;
extern osMutexId mid_serial;

Robot::Robot()
{
	osStatus status = osMutexWait(mid_serial, osWaitForever);
	if(status == osOK)	usart.printf("\n\n	Robot created");	
	osMutexRelease(mid_serial);
	
	this->user = new UsartUser();
}


void Robot::Start(void)
{
	
}
