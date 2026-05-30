const int controlPin = 13;

void setup() {
  pinMode(controlPin, OUTPUT);
}

void loop() {
  digitalWrite(controlPin, HIGH); // LED включается
  delay(1000);

  digitalWrite(controlPin, LOW);  // LED выключается
  delay(1000);
}
