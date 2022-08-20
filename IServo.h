#ifndef __ISERVO_H__
#define __ISERVO_H__

#include "Arduino.h"

class IServo
{
	private:
	int servo;
	float angle;
	float angle_range=180;
	int min_PWM=500;//单位us
	int max_PWM=2500;
	void pulse(int _pulsewidth);
	
	public:
	IServo(int _servo=2);
	void init();
	int rotating(float _des_angle);
};


#endif // __ISERVO_H__