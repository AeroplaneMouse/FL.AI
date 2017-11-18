#include <Servo.h>
// Servo
const int servoPin = 3;

// Afstands sensor pins
const int trig = 2;
const int echo = 4;

// Motor pins
const int f1 = 5;  // Højre
const int f2 = 6;  // Højre
const int b1 = 9;  // Venstre
const int b2 = 10; // Venstre

// Infrarød pin
//const string red = A0;

// Andre variabler
int counter = 0;
int servo_direction = 1;
char frem_bytes[] = "frem";
char bak_bytes[] = "bak";
char hoejre_bytes[] = "hoejre";
char venstre_bytes[] = "venstre";
bool autoStop = true;
int object = 90;
int counter_no_object = 0;
bool go = false;

Servo servo;
int pos[] = {0, 0};

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  servo.attach(servoPin);
  Serial.begin(9600);



  // Finding enemy.
  /*
  servo.write(0);
  delay(100);
  int distance = getDistance();
  if (!search) {
    turn(180);
    delay(100);
    if (!search) {
      Serial.println("Error");
      return;
    }
  }

  if (pos[0] > 70 && pos[0] < 110) {
    drive(255, 1);
  }
  else if (pos[0] <= 70) {

  }
  else {
    turn(30);
    delay(100);
    drive(255, 1);
  }
  */
}

void loop() {
  if (go) {
    if (analogRead(A0) < 10) {
      drive(255, 2);
      delay(400);
      turn(90);
      delay(100);
      drive(255, 1);
    }
    /*
    int distance = getDistance();
    Serial.println(distance);) {
      if (pos[1] == 0) {
        pos[0] += 10;
      }

    if (distance > 20 || distance == 0
      else {
        pos[0] -= 10;
      }
      servo.write(pos[0]);

      if (pos[0] == 180) {
        pos[1] = 1;
      }
      else if (pos[0] == 0) {
        pos[1] = 0;
      }
    }
    */

    /*
    servo.write(pos[0]);

    if (pos[1] == 0) pos[0] += 10;
    else pos[0] -= 10;

    if (pos[0] == 180) pos[1] = 1;
    else if (pos[0] == 0) pos[1] = 0;

    */


    // Delay and counter. Slow things down and keep track of time.
    delay(10);
    counter += 10;
    if (counter == 1010) {
      counter = 10;
    }

    if (digitalRead(12) == LOW) {
      go = false;
      Serial.println("LOW2");
    }
    else {
      Serial.println("HIGH2");
    }
  }
  else {
    if (digitalRead(12) == HIGH) {
      Serial.println("HIGH1");
      go = true;
      delay(3000);
      drive(255,1);
    }
    else {
      Serial.println("LOW1");
    }
  }

  /*
  if (analogRead(A0) < 6) {
    Serial.println("Black nigger! :(");
  }
  else {
    Serial.println("White person. :D");
  }


  if (pos[0] > 180) pos[1] = 1;
  if (pos[0] < 0) pos[1] = 0;

  servo.write(pos[0]);


  int distance = getDistance();

  if (object_found) Serial.println("True");
  else Serial.println("False");


  if (distance < 10 && distance > 0) {
    object_found = true;
  }

  if (object_found && (distance > 9 || distance < 1)) {
    if (pos[1] == 0) pos[1] = 1;
    else pos[0] = 0;
  }

  if (pos[1] == 0) pos[0] += 10;
  else pos[0] -= 10;

  delay(100);
  */
}

bool search() {
  int distance = 0;
  for (pos[0] = 0; pos[0] < 180; pos[0] += 10) {
    servo.write(pos);
    delay(100);
    distance = getDistance();
    if (distance < 20) {
      break;
    }
  }

  if (distance < 20) {
    return true;
  }
  for (pos[0] = 180; pos[0] > 0; pos[0] -= 10) {
    servo.write(pos);
    delay(100);
    distance = getDistance();
    if (distance < 20) {
      break;
    }
  }

  if (distance < 20) {
    return true;
  }
  return false;
}


int getDistance(){
  // Gets the distance from the sensor in cm.
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 10000);
  long distance = (duration/2) / 29.1;      // Return cm.
  //long distance = ((duration/2)*0.34029)/100; // Return cm.
  return distance;
}

void drive(int _speed, int _direction){
  //_speed = (_speed*255)/100;
  switch (_direction){
    case 0:
      digitalWrite(f1, LOW);
      digitalWrite(f2, LOW);
      digitalWrite(b1, LOW);
      digitalWrite(b2, LOW);
      break;
    case 1: // Frem
      digitalWrite(f2, LOW);
      digitalWrite(b2, LOW);
      analogWrite(f1, _speed);
      analogWrite(b1, _speed);
      break;
    case 2: // Tilbage
      digitalWrite(f1, LOW);
      digitalWrite(b1, LOW);
      analogWrite(f2, _speed);
      analogWrite(b2, _speed);
      break;
  }
}

void turn(int degree){
  digitalWrite(f1, LOW);
  digitalWrite(b2, LOW);
  analogWrite(f2, 255);
  analogWrite(b1, 255);
  delay(300);
  digitalWrite(f2, LOW);
  digitalWrite(b1, LOW);

  /*
  int q = 0;
  if (degree < 0) {
    degree += -(2*degree);
    q = 1;
  }
  int x = 230*(((degree*100)/180)/100);
  if (q == 0) {
    digitalWrite(f1, LOW);
    digitalWrite(b2, LOW);
    analogWrite(f2, 255);
    analogWrite(b1, 255);
    delay(x);
    digitalWrite(f2, LOW);
    digitalWrite(b1, LOW);
  }
  else {
    digitalWrite(f2, LOW);
    digitalWrite(b1, LOW);
    analogWrite(f1, 255);
    analogWrite(b2, 255);
    delay(x);
    digitalWrite(f1, LOW);
    digitalWrite(b2, LOW);
  }
  */
}

int getDirection(int waitingBytes){
  bool correctMessage = true;
  switch (waitingBytes){
    case 3:
      for (int q = 0; q < 3; q++){
          if (Serial.read() != bak_bytes[q]){
            correctMessage = false;
            break;
          }
      }
      return 2;
    case 4:
      for (int q = 0; q < 4; q++){
        if (Serial.read() != frem_bytes[q]){
          correctMessage = false;
          break;
        }
      }
      return 1;
    case 6:
      for (int q = 0; q < 5; q++){
        if (Serial.read() != hoejre_bytes[q]){
          correctMessage = false;
          break;
        }
      }
      return 3;
    case 7:
      for (int q = 0; q < 7; q++){
        if (Serial.read() != venstre_bytes[q]){
          correctMessage = false;
          break;
        }
      }
      return 4;
  }
  return 0;
}
