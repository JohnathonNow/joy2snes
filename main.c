#include <stdio.h>
#include <sys/time.h>
#include <linux/joystick.h>

int main() {
    FILE *joy = fopen("/dev/input/js0", "r");    
    struct js_event e = {0};
    for (;;) {
        fread(&e, sizeof(e), 1, joy);
        switch (e.type)
        {
            case JS_EVENT_BUTTON:
                printf("Button %u %s\n", e.number, e.value ? "pressed" : "released");
            break;
            case JS_EVENT_AXIS:
                printf("Axis %u %x\n", e.number, e.value);
            break;
            default: break;
        }
    }
}
