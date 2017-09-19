const int trig = 2;
const int echo = 3;

const int f1 = 9;
const int b1 = 10;
const int f2 = 5;
const int b2 = 6;

int counter = 0;
int i = 0;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(b2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();
  //Serial.print(distance);
  //Serial.println(" cm");

  if (distance < 20){
    /*
    if (counter == 10){
      forward(i);
      i += 50;
    }
    if (i > 255) i = 0;
    */
    forward(0);
  }
  else{
    forward(255);
  }
  
  if (counter == 10) counter = 0;
  counter++;
  delay(10);
}

int getDistance(){
  // Gets the distance from the sensor in cm.
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(3, HIGH, 90000);
  long distance = (duration/2) / 29.1;
  return distance;
}

void backward(int motor, int pwm){
  if (motor == 1){
    digitalWrite(f1, LOW);
    delay(200);
    analogWrite(b1, pwm);
  }
  else{
    digitalWrite(f2, LOW);
    delay(200);
    analogWrite(b2, pwm);
  }
}

void forward(int motor, int pwm){
  if (motor  == 1){
    digitalWrite(b1, LOW);
    delay(200);
    analogWrite(f1, pwm);
  }
  else{
    digitalWrite(b2, LOW);
    delay(200);
    analogWrite(f2, pwm);
  }
}
