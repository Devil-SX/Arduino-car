//和rader.m联动，先打开单片机，再运行rader.m
#include "IUltrasound.h"
#include "IServo.h"

IUltrasound sound;
IServo servo;
int last_send = millis();//上一次发送指令的时间，如果距离上一次10s都没有收到回复，则重新发送
float distance;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	sound.init();
	servo.init();
}

void loop() {
  // put your main code here, to run repeatedly:
	String angle = "";
	char byte = '\0';
	while(1){
		if(millis()-last_send>10000){
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
	
	servo.rotating(angle.toInt());
	distance = sound.distance();
	if(distance)	Serial.println(distance,DEC);
	else	Serial.println("No Track");
	last_send = millis();

	delay(200);
}
