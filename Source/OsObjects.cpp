#include "OsObjects.h"
#include "Robot.h"
#include "Linker.h"
#include <vector>

extern SerialUSART2 usart;
Linker Linker;

std::vector<TrajectoryInterface*> Global_Trajectories;

osMutexId mid_serial;
osMutexDef(Serial);



osThreadId Routine_Thread_Id;
osThreadId Phase_Id;

osThreadId robot_thread_id;
osThreadId Phase_Thread_Id;
osThreadId Right_Hip_Thread_Id;
osThreadId Right_Knee_Thread_Id;
osThreadId Right_Ankle_Thread_Id;
osThreadId Left_Hip_Thread_Id;
osThreadId Left_Knee_Thread_Id;
osThreadId Left_Ankle_Thread_Id;

osThreadDef(RobotThread, osPriorityNormal, 1, 0);
osThreadDef(Routine_Thread, osPriorityAboveNormal, 1, 0);
osThreadDef(Phase_Thread, osPriorityHigh, 1, 0);
osThreadDef(Right_Hip_Thread, osPriorityNormal, 1, 0);
osThreadDef(Right_Knee_Thread, osPriorityNormal, 1, 0);
osThreadDef(Right_Ankle_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Hip_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Knee_Thread, osPriorityNormal, 1, 0);
osThreadDef(Left_Ankle_Thread, osPriorityNormal, 1, 0);


int InitThreads(void)
{
	mid_serial =   osMutexCreate(osMutex(Serial));
	robot_thread_id = osThreadCreate(osThread(RobotThread), NULL);
	Right_Hip_Thread_Id = osThreadCreate(osThread(Right_Hip_Thread), NULL);
	Right_Knee_Thread_Id = osThreadCreate(osThread(Right_Knee_Thread), NULL);
	Right_Ankle_Thread_Id = osThreadCreate(osThread(Right_Ankle_Thread), NULL);
	Left_Hip_Thread_Id = osThreadCreate(osThread(Left_Hip_Thread), NULL);
	Left_Knee_Thread_Id = osThreadCreate(osThread(Left_Knee_Thread), NULL);
	Left_Ankle_Thread_Id = osThreadCreate(osThread(Left_Ankle_Thread), NULL);
	Routine_Thread_Id = osThreadCreate(osThread(Routine_Thread), NULL);
	Phase_Thread_Id = osThreadCreate(osThread(Phase_Thread),NULL);
	

	if(!mid_serial)return(-1);
	if(!robot_thread_id)return(-1);
	if(!Right_Hip_Thread_Id) return(-1);
	if(!Right_Knee_Thread_Id) return(-1);
	if(!Right_Ankle_Thread_Id) return(-1);
	if(!Left_Hip_Thread_Id) return(-1);
	if(!Left_Knee_Thread_Id) return(-1);
	if(!Left_Ankle_Thread_Id) return(-1);
	if(!Routine_Thread_Id) return(-1);
	if(!Phase_Thread_Id) return(-1);
	usart.printf("\nThreads Created");
	return(0);
}

void RobotThread(void const *argument)
{	
	Robot exo;
	osSignalWait(0x01, osWaitForever);
	
	osStatus status = osMutexWait(mid_serial, osWaitForever);
	if(status == osOK)	usart.printf("\n		Robot started");
	osMutexRelease(mid_serial);
		
	while(1)
	{
		
		Linker.Set_Current_Command(exo.user->GetCommand());
		
		if(Linker.Get_Current_Command()==not_a_command)
		{
			status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)		usart.printf("\r*****Not a Valid Comand");
			osMutexRelease(mid_serial);
		}
		else if(Linker.Get_Current_Command()==pause && !Linker.Is_Paused() )			Linker.Pause_Routine();
		else if(Linker.Get_Current_Command()==start &&  Linker.Is_Paused() )			Linker.Start_Routine();
		else if(Linker.Get_Current_Command()==stop && Linker.Routine!=NULL)
		{
				if(Linker.Get_Current_Routine_Command()!= calibration){ //<---------unstopable routines
					
				Linker.Set_Current_Routine_Command(Linker.Get_Current_Command());
				Linker.Routine->Stop();
				Linker.Routine=NULL;}
		}
		else if(Linker.Get_Current_Command()!=Linker.Current_Routine_Command && Linker.Routine==NULL)
		{
			Linker.Set_Current_Routine_Command(Linker.Get_Current_Command());
			
			switch(Linker.Get_Current_Command())
		{
			case calibration:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n		Calibration Routine selected");
					osMutexRelease(mid_serial);
					
					exo.Set_Routine(new CalibrationRoutine());
					Linker.Pause_Routine();
					Linker.Routine=exo.routine;
					osSignalSet(Routine_Thread_Id,0x01);
			break;
			case gate:
				status = osMutexWait(mid_serial, osWaitForever);
				if(status == osOK)	usart.printf("\n	Gate Routine selected");
				osMutexRelease(mid_serial);
					
					exo.Set_Routine(new GateRoutine());
					Linker.Pause_Routine();
					Linker.Routine=exo.routine;
					osSignalSet(Routine_Thread_Id,0x01);
			break;
			default:	
			break;	
			}
			
		}
		else
		{}
		
	}
}



void Routine_Thread (void const *argument){
	int cycles;
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		if(Linker.Get_Current_Routine_Command()==calibration)cycles=1;
		else cycles=5;
			
		for(int i=0;i<cycles;i++){ 
		
			Linker.Routine->LoadRoutine();
			Linker.Routine->PerformRoutine();
		}
			Linker.Routine->Stop();
			Linker.Set_Current_Routine_Command(0);
			Linker.Routine=NULL;
			
	}
}

void Phase_Thread (void const* argument)
{
while(1)
	{
		osSignalWait(0x01,osWaitForever);
			//usart.printf("\n		 Thread Phase");
		
		osSignalSet(Right_Hip_Thread_Id,0x01);
		osSignalSet(Right_Knee_Thread_Id,0x01);		
		osSignalSet(Right_Ankle_Thread_Id,0x01);
		osSignalSet(Left_Hip_Thread_Id,0x01);
		osSignalSet(Left_Knee_Thread_Id,0x01);
		osSignalSet(Left_Ankle_Thread_Id,0x01);
		
		
		for(int i=0;i<6;i++)
		{
		osSignalWait(0x01,osWaitForever);
		}
		
		osSignalSet(Phase_Id,0x01);
	}	
}

void Right_Hip_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[0]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Right_Knee_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[1]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Right_Ankle_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[2]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}


void Left_Hip_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[3]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Left_Knee_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[4]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

void Left_Ankle_Thread (void const *argument){
	
	while(1){
		osSignalWait(0x01,osWaitForever);
		
		//	Global_Trayectories[5]->Perform_Trajectory();
		osSignalSet(Phase_Thread_Id,0x01);
	}
}

