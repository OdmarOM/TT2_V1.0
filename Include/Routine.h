#ifndef _ROUTINE_H
#define _ROUTINE_H

#include "Phase.h"
#include <vector>


class RoutineInterface
{
	public:
		std::vector<Phase> Phases;			//Phase
		virtual void Perform()=0;
		virtual void Pause()=0;
		virtual void Stop()=0;
		virtual~RoutineInterface(){};
};

class CalibrationRoutine : public RoutineInterface
{
	public:
		CalibrationRoutine(){};
		virtual void Perform(void);
		virtual void Pause(void);
		virtual void Stop(void);
		virtual ~CalibrationRoutine();
};

class StopRoutine : public RoutineInterface
{
	public:
		StopRoutine();
		virtual void Perform(void);
		virtual void Pause(void);
		virtual void Stop(void);
};


#endif //_ROUTINE_H
