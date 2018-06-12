#ifndef _PHASE_H
#define _PHASE_H

#include "Leg.h"

class Phase
{
	private:
		//Leg 				Right_Leg,Left_Leg;// leg
		int x;
	public:
		 void Perform(void);
		 Phase();
		 Phase(const Phase &cpy){x=0;};
		~Phase();
};


#endif

