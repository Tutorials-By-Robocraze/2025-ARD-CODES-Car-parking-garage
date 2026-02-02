#include <Servo.h>

#define TRIG_PIN 6  // Ultrasonic sensor trigger pin
#define ECHO_PIN 7  // Ultrasonic sensor echo pin
#define SERVO_PIN 9 // Servo motor pin

Servo garageServo;
const int openPosition = 90;  // Door open position
const int closePosition = 0;  // Door closed position
const int carDistanceThreshold = 15; // Distance threshold in cm

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    garageServo.attach(SERVO_PIN);
    garageServo.write(closePosition);
    Serial.begin(9600);
}

long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2; // Convert to cm
}

void loop() {
    long distance = getDistance();
    Serial.println(distance);

    if (distance < carDistanceThreshold) {
        garageServo.write(openPosition); // Open garage door
    } else {
        garageServo.write(closePosition); // Close garage door
    }

    delay(500);
}

