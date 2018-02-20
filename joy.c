#include <stdio.h>
#include <sys/time.h>
#include <linux/joystick.h>
#include <pthread.h>

#define THRESHOLD 2<<13

int BUTTONS[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//B Y SEL START UP DOWN LEFT RIGHT A X L R

void *joy(void*);

int main() {
	pthread_t joy_thread;
	if (pthread_create(&joy_thread, 0, joy, 0)) {
		return 1;
	}
	for(;;) {}
	return 0;
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
	int i;
	for (i = 1; i <= 12; i++) {
		printf("%d", BUTTONS[i]);
	}
	printf("\n");
    }
}
