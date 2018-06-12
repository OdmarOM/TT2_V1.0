#ifndef _ROBOT_H
#define _ROBOT_H

#include "User.h"
#include "Routine.h"

class Robot	 // En ingles 
{
	private:
		StatusDataType 			robot_status;
		RoutineInterface* 	routine;				//rutina
	public:
		UserInterface*			user;
		Robot();
		void Start(void);
};


#endif
