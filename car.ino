//全自动瞎走程序
//超声波+舵机避障
//究极鬼畜

//是否DEBUG模式
//#define DEBUG

#include "IUltrasound.h"
#include "IRremote.h"
#include "IServo.h"
#include "IBeep.h"
#include "IMove.h"

//超声波相关声明
IUltrasound sound;

//红外控制相关声明
#define CH_SUB 0xFFA25D
#define CH 0xFF629D
#define CH_ADD 0xFFE21D
#define R_LEFT 0xFF22DD
#define R_RIGHT 0xFF02FD
#define PAUSE 0xFFC23D
#define SUB 0xFFE01F
#define ADD 0xFFA857
#define EQ 0xFF906F
#define R_0 0xFF6897
#define ADD_100 0xFF9867
#define ADD_200 0xFFB04F
#define R_1 0xFF30CF
#define R_2 0xFF18E7
#define R_3 0xFF7A85
#define R_4 0xFF10EF
#define R_5 0xFF38C7
#define R_6 0xFF5AA5
#define R_7 0xFF42BD
#define R_8 0xFF4AB5
#define R_9 0xFF52AD

#define cmd_tracking_mode R_0
#define cmd_go R_2
#define cmd_left R_4 
#define cmd_stop R_5
#define cmd_right R_6
#define cmd_back R_8

int RECV_PIN = A4;//端口声明
IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明

//舵机相关声明
IServo iservo;

//移动控制相关声明
IMove imove;

//蜂鸣器相关声明
IBeep ibeep;

//其它声明
#define SPEED 200
#define TURN_SPEED 50

int speed = 100;
bool is_tracking_mode = false;
bool is_right_to_left = true;


void setup() {
  // put your setup code here, to run once:
	imove.init();
	sound.init();
	ibeep.init();
  	irrecv.enableIRIn(); // Start the receiver
	iservo.init();
	
	sound.set_max_distance(500);
#ifdef DEBUG
	Serial.begin(9600);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

	//接收红外信号
	if(irrecv.decode(&results)){
		if(results.value==cmd_tracking_mode){
			is_tracking_mode =! is_tracking_mode;
			ibeep.bi(500+is_tracking_mode*500);
		}

		//控制模式
		else if(!is_tracking_mode){
			if(results.value==cmd_go) imove.run(SPEED);
			else if(results.value==cmd_stop) imove.stop();
			else if(results.value==cmd_left) imove.left(TURN_SPEED);
			else if(results.value==cmd_right) imove.right(TURN_SPEED);
			else if(results.value==cmd_back) imove.back();
		}

		irrecv.resume();
	}

	//跟踪模式
	if(is_tracking_mode)
	{
		float distance = 0;
		float max_distance = 0;
		int max_distance_angle = 0;

		//从0到180°扫描，每两度一扫,先从左往右，再从右往左
		if(is_right_to_left){
			for(int angle=0;angle<=180;angle+=2){
				iservo.rotating(angle);
				distance = sound.distance();
				if(distance){
					if(distance>=max_distance){
						max_distance = distance;
						max_distance_angle = angle;
					}
				}
				//超出5米的
				else{
					max_distance = 0;
					max_distance_angle = angle;
					break;
				}
			}
			is_right_to_left = false;
		}
		else{
			for(int angle=180;angle>=180;angle-=2){
				iservo.rotating(angle);
				distance = sound.distance();
				if(distance){
					if(distance>=max_distance){
						max_distance = distance;
						max_distance_angle = angle;
					}
				}
				//超出5米的
				else{
					max_distance = 0;
					max_distance_angle = angle;
					break;
				}
			}
			is_right_to_left = true;
		}

		if(max_distance_angle<75)	imove.right();
		else if(max_distance_angle>105)	imove.left();
		else if(max_distance_angle>=75 && max_distance_angle<=105){
			if(max_distance>100||max_distance==0){
				imove.run();
				delay(1000);
			}
			else if(max_distance>35){
				imove.run();
				delay(500);
			}
			else if(max_distance<35)	imove.back();
		}

		delay(200);
		imove.stop();
	}

}
