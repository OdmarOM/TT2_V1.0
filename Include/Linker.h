#ifndef _LINKER_H
#define _LINKER_H

#include "Robot.h"

class Linker
{
	public:
		RoutineInterface* Routine;
		int Current_Routine_Command;
		int Current_Command;
		int Previous_Command;
		int Speed;
		float Current_Position[6];
		float Future_Position[6];
		bool Pause;
		bool Performing;

		Linker();
		void	Set_Current_Routine_Command(int);
		int		Get_Current_Routine_Command();
		void 	Set_Current_Command(int);
		int 	Get_Current_Command();
		int 	Get_Previous_Command();
		void	Set_Speed(int);
		int		Get_Speed();
		void 	Set_Current_Position(float[]);
		float*	Get_Current_Position();
		void 	Set_Future_Position(float[]);
		void	Pause_Routine(void);
		void	Start_Routine(void);
		bool	Is_Paused(void);
};






#endif
