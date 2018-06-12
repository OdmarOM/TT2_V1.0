#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H

#include <vector>

class TrajectoryInterface
{
	public:
		float* Position_Vector;
		int StartPoint;
	
		virtual double Forward()=0;
		virtual double Backward()=0;
		virtual void 	 SetStartPoint(int StartPoint)=0;
		virtual ~TrajectoryInterface(){};

};

class Hip_Gate : public TrajectoryInterface
{
	public:	
		Hip_Gate();
			virtual double Forward(void);
		virtual double Backward(void);
		virtual void 	 SetStartPoint(int StartPoint);

};



#endif

