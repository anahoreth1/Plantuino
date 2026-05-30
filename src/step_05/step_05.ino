#define RELAY_PIN 13

// aktualny stan przekaźnika
bool relayState = false;


void setup() {

  // ustawienie pinu przekaźnika jako wyjście
  pinMode(RELAY_PIN, OUTPUT);

  // wyłączenie przekaźnika na starcie
  digitalWrite(RELAY_PIN, HIGH);
}


void loop() {

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
  
  // 3 sekundy czekamy
  delay(3000);
}
