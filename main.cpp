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

	unsigned long d = 5000;

	for (unsigned long ti = millis(); millis() < (ti + d);) {
		analogWrite(3, random(255));
		analogWrite(5, random(255));
		analogWrite(6, random(255));
		delay(random(40, 500));
	}
	digitalWrite(3, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	Serial.println("Done...");
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

	Serial.begin(9600);
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
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
