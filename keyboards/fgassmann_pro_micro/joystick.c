
#include "pointing_device.h"

//joystick

int xPin = F4; // VRx
int yPin = F5; // VRy
//int swPin = C4; // SW

// Set Parameters
int minAxisValue = 0;
int maxAxisValue = 1023;

int maxCursorSpeed = 1;

int xPolarity = 1;
int yPolarity = 1;

int cursorTimeout = 10;

int xOrigin, yOrigin;

uint16_t lastCursor = 0;

int axisCoordinate(int pin, int origin) {
    int direction;
    int distanceFromOrigin;
    int range;

    int position = analogReadPin(pin);
    //dprintf("analog read: %d (origin is %d))\n", position,origin);

    if (origin == position) {
        return 0;
    } else  if (origin > position) {
        distanceFromOrigin = origin - position;
        range = origin - minAxisValue;
        direction = -1;
    } else {
        distanceFromOrigin = position - origin;
        range = maxAxisValue - origin;
        direction = 1;
    }

    float percent = (float)distanceFromOrigin / range;
    int coordinate = (int)(percent * 100);
    if (coordinate < 0) {
        return 0;
    }
    else if (coordinate > 100) {
      return 100 * direction;
    }
    else {
      return coordinate * direction;
    }
}

int axisToMouseComponent(int pin, int origin, int maxSpeed, int polarity) {
    int coordinate = axisCoordinate(pin, origin);
    print_decs(coordinate); println();
    if (coordinate == 0) {
        return 0;
    }
    else {
        float percent = (float)coordinate / 100;
        return percent * maxCursorSpeed * polarity * (abs(coordinate)/6);
    }
}

void pointing_device_task(void) {
    report_mouse_t report;
    report.x = 0;
    report.y = 0;
    report.h = 0;
    report.v = 0;
    report.buttons = 0;

    // todo read as one vector
    if (timer_elapsed(lastCursor) > cursorTimeout) {
        lastCursor = timer_read();
        report.x = axisToMouseComponent(xPin, xOrigin, maxCursorSpeed, xPolarity);
        report.y = axisToMouseComponent(yPin, yOrigin, maxCursorSpeed, yPolarity);
    }

    // if (digitalRead(swPin) == 1) {
    //     report.buttons |= MOUSE_BTN1;
    // }
    pointing_device_set_report(report);
    pointing_device_send();
}


void matrix_init_kb(void) {
    i2c_init();

    // timer_init();
    // xOrigin = analogReadPin(xPin);
    // dprintf("analog read: Xorigin is %d))\n", xOrigin);
    // yOrigin = analogReadPin(yPin);
    // dprintf("analog read: Yorigin is %d))\n", yOrigin);
}