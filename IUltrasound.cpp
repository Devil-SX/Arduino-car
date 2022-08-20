#include "IUltrasound.h"

IUltrasound::IUltrasound(int _trig,int _echo)
{
	trig = _trig;
	echo = _echo;
}

void IUltrasound::init()
{
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trig, LOW);
}

void IUltrasound::set_max_distance(int _max)
{
	max_distance = _max;
}

//测量距离（厘米），超出距离则返回0
float IUltrasound::distance()
{
	float distance = 0;
	
	//取5次测量结果的平均值
	for(int i=0;i<5;i++)
	{
		//发射超声波脉冲
		digitalWrite(trig, LOW);
		digitalWrite(trig,HIGH);
		delayMicroseconds(3);
		digitalWrite(trig,LOW);

		float d = pulseIn(echo,HIGH,max_distance*58.)/58;
		if(d==0)
			return 0;
		distance += d;
	}

	return distance/5;
}
