#include <stdio.h>
#include <wiringPi.h>


#define CLK 8
#define LAT 9
#define DAT 7

int main()
{
  wiringPiSetup() ;
  piHiPri(99);
  pinMode(CLK, INPUT);
  pinMode(LAT, INPUT);
  pinMode(DAT, OUTPUT);
  digitalWrite(DAT, 1);
  int c = 0;
  int edge = 0;
  int oldLat = 0;
  for (;;)
  {
	int newLat = digitalRead(LAT);
	if (newLat && !oldLat) {
		c = 0;
		delayMicroseconds(5);
	}
	oldLat = newLat;
	int cur = digitalRead(CLK);
	if (cur == 0 && edge == 1) {
		c++;
		//if (c == 5 || c == 1) {
		if (c == 12) {
			digitalWrite(DAT, 0);
		} else {
			digitalWrite(DAT, 1);
		}
		delayMicroseconds(3);
	}
        edge = cur;
  }
  return 0 ;
}
