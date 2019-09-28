#include <Arduino.h>
#include <UltrasoundDistanceSensor.h>

#define IDLE 0
#define ACTIVE 1
#define ACTIVATION_THRESHOLD 20

UltrasoundDistanceSensor sensor(8, 9);
bool state = IDLE;

float distance = 0;

void run() {
	Serial.println("Running");
    Serial.println("Working...");
}

void loop() {

	if (state == ACTIVE) {
		run();
		state = IDLE;
	}

	if (state == IDLE) {
		distance = sensor.getDistance();
		Serial.println(distance);

		if (distance < ACTIVATION_THRESHOLD) {
			state = ACTIVE;
		}
	}
}

void setup() {

    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);

    for(;;) {
    	analogWrite(3, random(255));
        analogWrite(5, random(255));
        analogWrite(6, random(255));
		delay(random(40, 500));
    }
}

int main() {

	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

	setup();

	for (;;) {
		loop();

		if (serialEventRun) {
			serialEventRun();
		}
	}
	return 0;
}
