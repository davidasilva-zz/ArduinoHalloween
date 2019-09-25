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
	digitalWrite(13, HIGH);
	delay(10000);
	digitalWrite(13, LOW);
	Serial.println("Done");
}

void setup() {
	Serial.begin(9600);
    pinMode(13, OUTPUT);
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

