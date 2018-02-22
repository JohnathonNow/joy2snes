#include <stdio.h>
#include <sys/time.h>
#include <linux/joystick.h>
#include <pthread.h>

#define THRESHOLD 2<<13

int BUTTONS[32] = {0};
int AXES[32] = {0};

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
		BUTTONS[e.number] = e.value;
		break;
            case JS_EVENT_AXIS:
		AXES[e.number] = (int)e.value;
	    	break;
            default: break;
        }
	int i;
	for (i = 0; i < 11; i++) {
		printf("%d", BUTTONS[i]);
	}
	for (i = 0; i < 8; i++) {
		printf("  %8d  ", AXES[i]);
	}
	printf("\n");
    }
}
