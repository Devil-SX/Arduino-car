#ifndef __IBEEP_H__
#define __IBEEP_H__


#include "Arduino.h"

class IBeep
{
	private:
	int beep;

	public:
	IBeep(int _beep=A3);//A3不支持PWM
	void init();
	void bi(int mileseconds=200);
};

#endif // __IBEEP_H__