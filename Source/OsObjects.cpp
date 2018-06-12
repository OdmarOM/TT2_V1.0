#include "OsObjects.h"
#include "Robot.h"

extern SerialUSART2 usart;
extern osThreadId Routine_Id;
extern Robot exo;

osMutexId mid_serial;
osMutexDef(Serial);

osThreadId robot_thread_id;

osThreadDef(RobotThread, osPriorityNormal, 1, 0);

int InitThreads(void)
{
	mid_serial =   osMutexCreate(osMutex(Serial));	
	if(!mid_serial)return(-1);
	robot_thread_id = osThreadCreate(osThread(RobotThread), NULL);
	
	if(!robot_thread_id)return(-1);
	return(0);
}

void RobotThread(void const *argument)
{	
	int command;
	
	osSignalWait(0x01, osWaitForever);
	
	osStatus status = osMutexWait(mid_serial, osWaitForever);
	if(status == osOK)	usart.printf("\n	Robot started");
	osMutexRelease(mid_serial);
		
	while(1){
		command = exo.user->GetCommand();
		
		switch(command)
		{
			case calibration:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Calibration Routine selected");
				osMutexRelease(mid_serial);
			break;
			
			case home:	
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Home Routine selected");
				osMutexRelease(mid_serial);
			break;
			
			case anatomic:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Anatomic Routine selected");
				osMutexRelease(mid_serial);
			break;
			
			case pause:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Pause Routine selected");
				osMutexRelease(mid_serial);
			break;	
			
			case stop:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Stop Routine selected");
				osMutexRelease(mid_serial);
			break;
			
			default:	
			break;
		}
	}
}









//osThreadId Security_Thread_Id;
//osThreadId Phase_Thread_Id;
//osThreadId Right_Hip_Thread_Id;
//osThreadId Right_Knee_Thread_Id;
//osThreadId Right_Ankle_Thread_Id;
//osThreadId Left_Hip_Thread_Id;
//osThreadId Left_Knee_Thread_Id;
//osThreadId Left_Ankle_Thread_Id;

//osThreadDef(Security_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Phase_Thread, osPriorityAboveNormal, 1, 0);
//osThreadDef(Right_Hip_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Right_Knee_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Right_Ankle_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Left_Hip_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Left_Knee_Thread, osPriorityNormal, 1, 0);
//osThreadDef(Left_Ankle_Thread, osPriorityNormal, 1, 0);

//int InitThreads(void)
//{
//	mid_serial =   osMutexCreate(osMutex(Serial));
//	Right_Hip_Thread_Id = osThreadCreate(osThread(Right_Hip_Thread), NULL);
//	Right_Knee_Thread_Id = osThreadCreate(osThread(Right_Knee_Thread), NULL);
//	Right_Ankle_Thread_Id = osThreadCreate(osThread(Right_Ankle_Thread), NULL);
//	Left_Hip_Thread_Id = osThreadCreate(osThread(Left_Hip_Thread), NULL);
//	Left_Knee_Thread_Id = osThreadCreate(osThread(Left_Knee_Thread), NULL);
//	Left_Ankle_Thread_Id = osThreadCreate(osThread(Left_Ankle_Thread), NULL);
//	Security_Thread_Id = osThreadCreate(osThread(Security_Thread), NULL);
//	Phase_Thread_Id = osThreadCreate(osThread(Phase_Thread),NULL);
//	
//	
//	if(!mid_serial)return(-1);
//	if(!Right_Hip_Thread_Id) return(-1);
//	if(!Right_Knee_Thread_Id) return(-1);
//	if(!Right_Ankle_Thread_Id) return(-1);
//	if(!Left_Hip_Thread_Id) return(-1);
//	if(!Left_Knee_Thread_Id) return(-1);
//	if(!Left_Ankle_Thread_Id) return(-1);
//	if(!Security_Thread_Id) return(-1);
//	if(!Phase_Thread_Id) return(-1);
//	usart.printf("\nThreads Created");
//	return(0);
//}

//void Security_Thread (void const *argument){
//	
//	osSignalWait(0x1, osWaitForever);
//	
//	UserInterface* user = new UsartUser();
//	int command;
//	
//	while(1){
//		
//	command =user->GetCommand();
//	
//	switch(command)
//	{
//		case 2:   //Pause Rutine
//			usart.printf("Pausado...");
//		case 3:		//Stop  Rutine
//			
//		break;
//		
//		default:
//			
//		break;
//	}
//	}
//}

//void Phase_Thread (void const* argument)
//{
//while(1)
//	{
//		osSignalWait(0x01,osWaitForever);
//			//usart.printf("\n		 Thread Phase");
//		
//		osSignalSet(Right_Hip_Thread_Id,0x01);
//		osSignalSet(Right_Knee_Thread_Id,0x01);		
//		osSignalSet(Right_Ankle_Thread_Id,0x01);
//		osSignalSet(Left_Hip_Thread_Id,0x01);
//		osSignalSet(Left_Knee_Thread_Id,0x01);
//		osSignalSet(Left_Ankle_Thread_Id,0x01);
//		

//		for(int i=0;i<6;i++)
//		{
//		osSignalWait(0x01,osWaitForever);
//		}
//		
//		osSignalSet(Routine_Id,0x01);
//	}	
//}

//void Right_Hip_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[0]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}

//void Right_Knee_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[1]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}

//void Right_Ankle_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[2]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}


//void Left_Hip_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[3]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}

//void Left_Knee_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[4]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}

//void Left_Ankle_Thread (void const *argument){
//	
//	while(1){
//		osSignalWait(0x01,osWaitForever);
//		
//			Global_Trayectories[5]->Perform_Trajectory();
//		osSignalSet(Phase_Thread_Id,0x01);
//	}
//}

