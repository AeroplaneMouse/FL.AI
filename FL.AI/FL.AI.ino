#include <Servo.h>

#define servoPin 3
#define trig 2
#define echo 4
#define hf 11
#define hb 10
#define vf 5
#define vb 6
#define startSwitch 12
#define STOPPED 0
#define DRIVING 1
#define WAITING 2
#define SEARCHING 3

#define STOP 0
#define DRIVE 1
#define FORWARD 2
#define BACKWARD 3

#define DRIVE_SPEED 200
#define REVERSE_SPEED 255
#define SEARCH_DISTANCE_MAX 60
#define BLACKNESS 4
#define H_OFFSET 0
#define V_OFFSET 30

struct servo {
  int pin;
  int pos;
  int direction;
  Servo servo;
} servo;

struct memory {
  int state;
} memory;

void setup() {
  servo.pin = 3;
  memory.state = STOPPED;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(hf, OUTPUT);
  pinMode(hb, OUTPUT);
  pinMode(vf, OUTPUT);
  pinMode(vb, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(startSwitch, INPUT_PULLUP);

  servo.servo.attach(servo.pin);
  servo.servo.write(81);
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();
  int color = analogRead(A0);
  Serial.println(color);
  switch (memory.state) {
    case STOPPED:
      // Serial.println("STOPPED");
      drive(0, STOP);
      if (digitalRead(startSwitch) == LOW) {
        memory.state = WAITING;
        delay(3000);
      }
      break;

    case WAITING:
      // Serial.println("WAITING");
      memory.state = SEARCHING;
      break;

    case DRIVING:
      // Serial.println("DRIVING");
      if (digitalRead(startSwitch) == HIGH) {
        memory.state = STOPPED;
        return;
      }
      else if (color < BLACKNESS) {
        // Serial.println("EDGE");
        drive(REVERSE_SPEED, BACKWARD);
        delay(520);
        turn90();
        memory.state = SEARCHING;
      }
      else if (distance > SEARCH_DISTANCE_MAX || distance == 0) {
        memory.state = SEARCHING;
      }
      break;

    case SEARCHING:
      // Serial.println("SEARCHING");
      if (digitalRead(startSwitch) == HIGH) {
        memory.state = STOPPED;
        return;
      }
      if (color < BLACKNESS) {
        // Serial.println("EDGE");
        drive(REVERSE_SPEED, BACKWARD);
        delay(520);
        turn90();
      }
      else if (distance > SEARCH_DISTANCE_MAX || distance == 0) {
        turn10();
      }
      else {
        drive(DRIVE_SPEED, FORWARD);
        memory.state = DRIVING;
      }
      break;
  }
  delay(100);
}

void drive(int _speed, int _direction) {
  switch (_direction) {
    case STOP:
      analogWrite(hf, 0);
      analogWrite(hb, 0);
      analogWrite(vf, 0);
      analogWrite(vb, 0);
      // Serial.println("DRIVE STOP");
      break;
    case FORWARD:
      analogWrite(hb, 0);
      analogWrite(vb, 0);
      analogWrite(hf, _speed + H_OFFSET);
      analogWrite(vf, _speed + V_OFFSET);
      // Serial.println("DRIVE FORWARD");
      break;
    case BACKWARD:
      analogWrite(hf, 0);
      analogWrite(hb, _speed);
      analogWrite(vf, 0);
      analogWrite(vb, _speed);
      // Serial.println("DRIVE BACKWARD");
      break;
  }
}

int getDistance() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 10000);
  long distance = (duration/2) / 29.1;      // Return cm.
  //long distance = ((duration/2)*0.34029)/100; // Return cm.
  return distance;
}

void turn90() {
  analogWrite(hf, 0);
  analogWrite(hb, 255);
  analogWrite(vf, 255);
  analogWrite(vb, 0);
  delay(120);
  analogWrite(hf, 100);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 100);
  delay(10);
  analogWrite(hf, 0);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 0);
}

void turn90inv() {
  analogWrite(hf, 255);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 255);
  delay(120);
  analogWrite(hf, 0);
  analogWrite(hb, 100);
  analogWrite(vf, 100);
  analogWrite(vb, 0);
  delay(10);
  analogWrite(hf, 0);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 0);
}

void turn10() {
  analogWrite(hf, 200);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 200);
  delay(40);
  analogWrite(hf, 0);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 0);
}

void turn180() {
  analogWrite(hf, 0);
  analogWrite(hb, 255);
  analogWrite(vf, 255);
  analogWrite(vb, 0);
  delay(400);
  analogWrite(hf, 0);
  analogWrite(hb, 0);
  analogWrite(vf, 0);
  analogWrite(vb, 0);
}
