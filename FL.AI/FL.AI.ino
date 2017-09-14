const int trig = 2;
const int echo = 3;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print(getDistance());
  Serial.println(" cm");
  delay(100);
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

