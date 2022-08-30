#include "IUltrasound.h"

IUltrasound sound;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	sound.init();
}

void loop() {
  // put your main code here, to run repeatedly:
	float distance = sound.distance();
	if(distance)
		Serial.println(distance,DEC);
	else
		Serial.println("No Track");
	delay(200);

}
