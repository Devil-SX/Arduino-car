#include "IBeep.h"

IBeep::IBeep(int _beep)
{
	beep = _beep;
}

void IBeep::init()
{
	pinMode(beep,OUTPUT);
	digitalWrite(beep,LOW);
}

void IBeep::bi(int mileseconds)
{
	digitalWrite(beep,HIGH);
	delay(mileseconds);
	digitalWrite(beep,LOW);
}

