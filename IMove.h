#include "Arduino.h"

//引脚8没有PWM功能，所以左轮后退的功能无法PWM调制（back,spin_left)

enum car_status
{
	RUN,
	LEFT,
	RIGHT,
	BACK,
	STOP
};


class IMove
{
	private:
	car_status status = STOP;
	int firstsetp_time = 100;//起步加速时间，克服静摩擦力，单位ms
	int left_motor_go;
	int left_motor_back;
	int right_motor_go;
	int right_motor_back;

	//牺牲程序运行速度提高程序美观性和可读性
	//对左右电机的分别控制
	void left_go(int PWM=255);
	void left_stop();
	void left_back(int PWM=255);
	void right_go(int PWM=255);
	void right_stop();
	void right_back(int PWM=255);

	public:
	IMove(int left_go=8, int left_back=9, 
		int right_go=10, int right_back=11);
	void init();
	//通过左右电机运动组合移动整个小车
	void run(int PWM=255);
	void back(int PWM=255);
	void left(int PWM=255);
	void right(int PWM=255);
	void spin_left(int PWM=255);
	void spin_right(int PWM=255);
	void stop();
};
