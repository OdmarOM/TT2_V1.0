#ifndef _JOINT_H
#define _JOINT_H

#include "Motor.h"



class JointInterface
{
	public:
		Motor_Rotation Contraction;
		Motor Joint_Motor;
		virtual void SetAbsolutePosition(float);
		virtual void SetRelativePosition(float);
		virtual int GetMotorPulses(float)=0;
		virtual ~JointInterface(){};

};

class Hip_Joint: public JointInterface
{
	public:
		Motor_Rotation Contraction;
		Hip_Joint(Joint_Motor_Id);
		virtual int GetMotorPulses(float);

};

class Knee_Joint: public JointInterface
{
	public:
		Motor_Rotation Contraction;
		Knee_Joint(Joint_Motor_Id);
		virtual int GetMotorPulses(float);

};

class Ankle_Joint: public JointInterface
{
	public:
		Motor_Rotation Contraction;
		Ankle_Joint(Joint_Motor_Id);
		virtual int GetMotorPulses(float);

};

#endif
