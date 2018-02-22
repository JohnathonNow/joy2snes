#include <stdio.h>
#include <wiringPi.h>


#define CLK 7
#define LAT 9
#define DAT 8

#define RAW 0

const char* NAMES[12] = {
	"B",
	"Y",
	"SELECT",
	"START",
	"UP",
	"DOWN",
	"LEFT",
	"RIGHT",
	"A",
	"X",
	"L",
	"R"
};

void read(int* d) {
	digitalWrite(LAT, 1);
	delayMicroseconds(12);
	digitalWrite(LAT, 0);
	int i = 0;
	for (i = 0; i < 16; i++) {
		delayMicroseconds(6);
		digitalWrite(CLK, 0);
		d[i] = digitalRead(DAT);
		delayMicroseconds(6);
		digitalWrite(CLK, 1);

	}
}

int main()
{
	wiringPiSetup() ;
	pinMode(CLK, OUTPUT);
	pinMode(LAT, OUTPUT);
	pinMode(DAT, INPUT);
	digitalWrite(LAT, 0);
	digitalWrite(CLK, 1);
	int buttons[16] = {0};
	for (;;)
	{
		read(buttons);
		#if RAW
			int i;
			for (i = 0; i < 16; i++) {
				printf("%d", buttons[i]);
			}
			printf("\n");
		#else
			printf("\033[G");
			int i;
			for (i = 0; i < 12; i++) {
				if (!buttons[i]) {
					printf("%s ", NAMES[i]);
				}
			}
			printf("                                                                                                        ");
			fflush(stdout);
		#endif
		//delayMicroseconds(166700);
	}
	return 0 ;
}
