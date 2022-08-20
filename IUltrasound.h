#ifndef __IULTRASOUND_H__
#define __IULTRASOUND_H__

#include "Arduino.h"

class IUltrasound
{
	private:
	int trig;
	int echo;
	int max_distance=500;

	public:
	IUltrasound(int _trig=A0,int _echo=A1);
	void init();
	void set_max_distance(int _max);
	float distance();
};

#endif // __IULTRASOUND_H__
