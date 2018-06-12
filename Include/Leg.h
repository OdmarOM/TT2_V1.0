#ifndef _LEG_H
#define _LEG_H

#include "Joint.h"

class Leg
{
	private:
		JointInterface* Hip;
		JointInterface* Knee;
		JointInterface*	Ankle;
	
	public:
			Leg();
			void Perform(void);
	
};

#endif
