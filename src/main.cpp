#include <Arduino.h>
#include <UltrasoundDistanceSensor/UltrasoundDistanceSensor.h>

#define IDLE                            0
#define ACTIVE                          1
#define DISTANCE_ACTIVATION_THRESHOLD   100
#define ECHO_PIN                        8
#define TRIGGER_PIN                     9
#define RED_PIN                         3
#define GREEN_PIN                       5
#define BLUE_PIN                        6
#define MUSIC_PIN                       12
#define MUSIC_ON_PULSE_WIDTH            10
#define ANIMATION_DURATION              8000
#define MIN_COLOR_TIME                  40
#define MAX_COLOR_TIME                  500

UltrasoundDistanceSensor sensor(ECHO_PIN, TRIGGER_PIN);
bool state = IDLE;

float distance = 0;

void run() {
    Serial.println("Running");

    digitalWrite(MUSIC_PIN, HIGH);
    delay(MUSIC_ON_PULSE_WIDTH);
    digitalWrite(MUSIC_PIN, LOW);

    for (unsigned long ti = millis(); millis() < (ti + ANIMATION_DURATION);) {
        analogWrite(RED_PIN, random(255));
        analogWrite(GREEN_PIN, random(255));
        analogWrite(BLUE_PIN, random(255));
        delay(random(MIN_COLOR_TIME, MAX_COLOR_TIME));
    }
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
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

        if (distance > 0 && distance < DISTANCE_ACTIVATION_THRESHOLD) {
            state = ACTIVE;
        }
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(MUSIC_PIN, OUTPUT);

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(MUSIC_PIN, LOW);
}
