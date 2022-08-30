#include "IMove.h"
#include "IRremote.h"

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

#define cmd_go R_2
#define cmd_left R_4 
#define cmd_stop R_5
#define cmd_right R_6
#define cmd_back R_8

int RECV_PIN = A4;//端口声明
IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明

//移动控制相关声明
IMove imove;

//其它声明
#define SPEED 100
#define TURN_SPEED 50

void setup() {
  // put your setup code here, to run once:
	imove.init();
  	irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
	if(irrecv.decode(&results))
	{
		if(results.value==cmd_go) imove.run(SPEED);
		else if(results.value==cmd_stop) imove.stop();
		else if(results.value==cmd_left) imove.left(TURN_SPEED);
		else if(results.value==cmd_right) imove.right(TURN_SPEED);
		else if(results.value==cmd_back) imove.back();
		
		irrecv.resume();
	}
}
