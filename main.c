#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>
#include <linux/joystick.h>
#include <pthread.h>

#define THRESHOLD 2<<13
#define CLK 8
#define LAT 9
#define DAT 7

int BUTTONS[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//B Y SEL START UP DOWN LEFT RIGHT A X L R

void *joy(void*);
void reset();
void send();

int c = 0;

int main() {
	wiringPiSetup() ;
	piHiPri(99);
	pinMode(CLK, INPUT);
	pinMode(LAT, INPUT);
	pinMode(DAT, OUTPUT);
	digitalWrite(DAT, 1);
	wiringPiISR(LAT, INT_EDGE_RISING, reset);
	wiringPiISR(CLK, INT_EDGE_FALLING, send);
	joy(0);
}

void send() {
	c++;
	digitalWrite(DAT, BUTTONS[c]);
	delayMicroseconds(3);
}

void reset() {
	c = 0;
	delayMicroseconds(5);
}

void *joy(void* args) {
	FILE *joy = fopen("/dev/input/js0", "r");    
	struct js_event e = {0};
	for (;;) {
		fread(&e, sizeof(e), 1, joy);
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
