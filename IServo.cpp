#include "IServo.h"

IServo::IServo(int _servo)
{
	servo = _servo;
}

//给一个脉冲
void IServo::pulse(int _pulsewidth)
{
	digitalWrite(servo,HIGH);
	delayMicroseconds(_pulsewidth);
	digitalWrite(servo,LOW);
	delayMicroseconds(20000-_pulsewidth);
}


void IServo::init()
{
	pinMode(servo,OUTPUT);
	digitalWrite(servo,LOW);
	
	//初始复位
	angle = 90;
	int pulsewidth = (90*(max_PWM-min_PWM)/angle_range)+min_PWM;
	for(int i=0;i<60;i++) pulse(pulsewidth);

}

//角度范围[0,angle_range]，执行成功返回1
int IServo::rotating(float _des_angle)
{
	if(angle<0 || angle>angle_range)
		return 0;
	int pulsewidth = (_des_angle*(max_PWM-min_PWM)/angle_range)+min_PWM;
	
	float delta_angle = _des_angle-angle;
	delta_angle = abs(delta_angle);//Arduino的abs不能在里面执行算术运算

	//给60个周期足够转180°
	for(int i=0;i<delta_angle*60/angle_range;i++) pulse(pulsewidth);
	angle = _des_angle;
	
	return 1;
}

