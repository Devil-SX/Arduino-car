//和rader.m联动，先打开单片机，再运行rader.m
//运行得很鬼畜
#include "IUltrasound.h"
#include "Servo.h"

IUltrasound sound;
Servo servo;
unsigned long last_send = millis();//上一次发送指令的时间，如果距离上一次10s都没有收到回复，则重新发送
float distance;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	sound.init();
	servo.attach(2);
}

void loop() {
  // put your main code here, to run repeatedly:
	String angle = "";
	char byte = '\0';
	while(1){
		//超出5s没有收到来自上位机的信号，重新发送一遍
		if(millis()-last_send>5000){
			if(distance)	Serial.println(distance,DEC);
			else	Serial.println("No Track");
			last_send = millis();
		}
		
		if(Serial.available()>0){
			char byte = Serial.read();
			if(byte=='\n')	break;//使用'\n'作为结束符
			else angle += byte;
		}
	}
	
	//移动舵机
	servo.write(angle.toInt());
	delay(15);

	distance = sound.distance();
	if(distance)	Serial.println(distance,DEC);
	else	Serial.println("No Track");
	last_send = millis();
}
