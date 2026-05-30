#define BTN_PIN 8
#define LED_PIN 13

// czas, do którego będzie pracować
unsigned long enableEndMillis = 0;

// interwał pracy
const long interval = 3000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  
  unsigned long currentMillis = millis();
  
  bool buttonPushed = !digitalRead(BTN_PIN);
  if(buttonPushed) {
    enableEndMillis = currentMillis + interval;
  }
  Serial.print("A: ");
  Serial.print(enableEndMillis);
  Serial.print(" B: ");
  Serial.print(currentMillis);
  Serial.print(" C: ");
  Serial.println(buttonPushed);

  if(enableEndMillis > currentMillis) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  } 
}

 