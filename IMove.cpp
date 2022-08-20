#ifndef __IMOVE_H__
#define __IMOVE_H__

#include "IMove.h"


IMove::IMove(int left_go, int left_back, 
		int right_go, int right_back)
{
	left_motor_go = left_go;
	left_motor_back = left_back;
	right_motor_go = right_go;
	right_motor_back = right_back;
};


void IMove::left_go(int PWM)
{
	digitalWrite(left_motor_go, LOW);
	digitalWrite(left_motor_back, HIGH);
	analogWrite(left_motor_back, PWM);
};

void IMove::left_stop()
{
	digitalWrite(left_motor_go, LOW);
	digitalWrite(left_motor_back, LOW);
};

void IMove::left_back(int PWM)
{
	digitalWrite(left_motor_go, HIGH);
	digitalWrite(left_motor_back, LOW);
	analogWrite(left_motor_go, PWM);
};

void IMove::right_go(int PWM)
{
	digitalWrite(right_motor_go, HIGH);
	digitalWrite(right_motor_back, LOW);
	analogWrite(right_motor_go, PWM);
};

void IMove::right_stop()
{
	digitalWrite(right_motor_go, LOW);
	digitalWrite(right_motor_back, LOW);
};

void IMove::right_back(int PWM)
{
	digitalWrite(right_motor_go, LOW);
	digitalWrite(right_motor_back, HIGH);
	analogWrite(right_motor_back, PWM);
};

void IMove::init()
{
	pinMode(left_motor_go, OUTPUT);
	pinMode(left_motor_back, OUTPUT);
	pinMode(right_motor_go, OUTPUT);
	pinMode(right_motor_back, OUTPUT);
};

void IMove::run(int PWM)
{
	if(status!=RUN)
	{
		left_go();
		right_go();
		delay(firstsetp_time);
		status = RUN;
	}
	left_go(PWM);
	right_go(PWM);
};


void IMove::back(int PWM)
{
	if(status!=BACK)
	{
		left_back();
		right_back();
		delay(firstsetp_time);
		status = BACK;
	}
	left_back(PWM);
	right_back(PWM);
};

//左电机不动，右电机前进
void IMove::left(int PWM)
{
	if(status!=LEFT)
	{
		right_go();
		left_stop();
		delay(firstsetp_time);
		status = LEFT;
	}
	right_go(PWM);
	left_stop();
};

//右电机不动，左电机前进
void IMove::right(int PWM)
{
	if(status!=RIGHT)
	{
		right_stop();
		left_go();
		delay(firstsetp_time);
		status = RIGHT;
	}
	right_stop();
	left_go(PWM);
};

//左电机后退，右电机前进
void IMove::spin_left(int PWM)
{
	if(status!=LEFT)
	{
		left_back();
		right_go();
		delay(firstsetp_time);
		status = LEFT;
	}
	left_back(PWM);
	right_go(PWM);
};

//右电机后退，左电机前进
void IMove::spin_right(int PWM)
{
	if(status!=RIGHT)
	{
		right_back();
		left_go();
		delay(firstsetp_time);
		status = RIGHT;
	}
	right_back(PWM);
	left_go(PWM);
};

void IMove::stop()
{
	left_stop();
	right_stop();
	status = STOP;
};






#endif // __IMOVE_H__