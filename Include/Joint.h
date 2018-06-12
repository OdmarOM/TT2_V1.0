#ifndef _JOINT_H
#define _JOINT_H

#include "Trajectory.h"

class JointInterface
{
	private:
		TrajectoryInterface* Trajectory;
		//motor
	public:
		virtual void Perform(void)=0;
		virtual ~JointInterface(){};

};

class Hip : public JointInterface
{
	public:
		Hip();
		virtual void Perform(void);

};

#endif
