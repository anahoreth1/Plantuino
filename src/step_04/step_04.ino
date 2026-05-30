#define RELAY_PIN 7

// zmienna czasu
unsigned long previousMillis = 0;

// interwał migania
const long interval = 1000;

// aktualny stan przekaźnika
bool relayState = false;


void setup() {

  // ustawienie pinu przekaźnika jako wyjście
  pinMode(RELAY_PIN, OUTPUT);

  // wyłączenie przekaźnika na starcie
  digitalWrite(RELAY_PIN, HIGH);
}


void loop() {

  unsigned long currentMillis = millis();

  // zmiana stanu co 1 sekundę
  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    // zmiana stanu przekaźnika
    relayState = !relayState;

    // sterowanie przekaźnikiem
    if (relayState) {

      // włączenie przekaźnika
      // dla większości modułów: LOW = ON
      digitalWrite(RELAY_PIN, LOW);
    }
    else {

      // wyłączenie przekaźnika
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
}
