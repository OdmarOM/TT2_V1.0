#include "Routine.h"
#include "Usart.h"

//extern SerialUSART2 usart;


//**************************************************
//CalibrationRoutine::CalibrationRoutine()
//{
//	usart.printf("\n\n		CalibrationRoutine created");
//	
//	Phase Phase1=Phase();
//	
//		this->Phases.push_back(Phase1);
//}

void CalibrationRoutine::Perform(void)
{
//	usart.printf("\n		CalibrationRoutine Performing");			
			//Phases[0].Perform();
			//Phases[1].Perform();
}

void CalibrationRoutine::Pause(void)
{
//	usart.printf("\n Pause");
}

void CalibrationRoutine::Stop(void)
{
//	usart.printf("\n Stop");
}

CalibrationRoutine::~CalibrationRoutine()
{
//usart.printf("\n		Calibration routine deleted");
}

//**************************************************
StopRoutine::StopRoutine()
{
//	usart.printf("\n		Stop routine created");
}

void StopRoutine::Perform(void)
{
	
}

void StopRoutine::Pause(void)
{
//	usart.printf("\n Pause");
}

void StopRoutine::Stop(void)
{
//	usart.printf("\n Stop");
}


