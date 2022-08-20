#include "IServo.h"
#include "IBeep.h"

IServo iservo;
IBeep ibeep;

void setup() {
  // put your setup code here, to run once:
	iservo.init();
	ibeep.init();

	ibeep.bi();
	iservo.rotating(0);
	delay(500);

	ibeep.bi();
	iservo.rotating(180);
	delay(1000);

	ibeep.bi();
	iservo.rotating(0);

}

void loop() {
  // put your main code here, to run repeatedly:


}
