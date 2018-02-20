#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <linux/joystick.h>
#include <pthread.h>
#include <fcntl.h>

#define THRESHOLD 2<<13
#define CLK 8
#define LAT 9
#define DAT 7

int BUTTONS[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//B Y SEL START UP DOWN LEFT RIGHT A X L R

void *joy(void*);

int main() {
	wiringPiSetup() ;
	piHiPri(99);
	pinMode(CLK, INPUT);
	pinMode(LAT, INPUT);
	pinMode(DAT, OUTPUT);
	digitalWrite(DAT, 1);
	int joy = open("/dev/input/js0", O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);    
	struct js_event e = {0};
	for (;;) {
		if (!digitalRead(LAT)) {
			delayMicroseconds(6);
			digitalWrite(DAT, BUTTONS[1]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[2]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[3]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[4]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[5]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[6]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[7]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[8]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[9]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[10]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[11]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[12]);
			delayMicroseconds(12);
			digitalWrite(DAT, BUTTONS[13]);
			delayMicroseconds(12);
		}
		read(joy, &e, sizeof(e));
		switch (e.type)
		{
			case JS_EVENT_BUTTON:
				switch (e.number) {
					case 0:
						BUTTONS[9] = !e.value;
						break;
					case 1:
						BUTTONS[1] = !e.value;
						break;
					case 2:
						BUTTONS[2] = !e.value;
						break;
					case 3:
						BUTTONS[10] = !e.value;
						break;
					case 4:
						BUTTONS[11] = !e.value;
						break;
					case 5:
						BUTTONS[12] = !e.value;
						break;
					case 6:
						BUTTONS[3] = !e.value;
						break;
					case 7:
						BUTTONS[4] = !e.value;
						break;
					default: break;
				}
				break;
			case JS_EVENT_AXIS:
				switch (e.number) {
					case 0:
						BUTTONS[7] = !((int)e.value < -THRESHOLD);
						BUTTONS[8] = !((int)e.value > THRESHOLD);
						break;
					case 1:
						BUTTONS[5] = !( e.value < -THRESHOLD);
						BUTTONS[6] = !(e.value > THRESHOLD);
						break;
					default: break;
				}
				break;
			default: break;
		}
	}
}

void latch() {
	delayMicroseconds(18);
	int i;
	for (i = 1; i <= 13; i++) {
		digitalWrite(DAT, BUTTONS[i]);
		delayMicroseconds(10);
	}
}

void *joy(void* args) {
	for (;;) {
	}
}
