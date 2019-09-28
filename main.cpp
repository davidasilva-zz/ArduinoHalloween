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

    pinMode(8, OUTPUT);

    float c1 = 0.1;
    float c2 = 0.5;
    float c3 = 1.0;

    float tc = 1000;

    float tl1 = c1 * tc;
    float td1 = tc - tl1;

    float tl2 = c2 * tc;
    float td2 = tc - tl2;

    float tl3 = c3 * tc;
    float td3 = tc - tl3;

    for (;;) {
    	digitalWrite(5, HIGH);
    	delay((unsigned long)tl1);
    	digitalWrite(5, LOW);
    	delay((unsigned long)td1);

    	digitalWrite(6, HIGH);
    	delay((unsigned long)tl2);
    	digitalWrite(6, LOW);
    	delay((unsigned long)td2);

    	digitalWrite(7, HIGH);
    	delay((unsigned long)tl3);
    	digitalWrite(7, LOW);
    	delay((unsigned long)td3);
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
