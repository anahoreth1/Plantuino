#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ustawienia OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// pin czujnika wilgotności gleby
#define SOIL_SENSOR A0

#define BTN_PIN 8
#define LED_PIN 13

// czas, do którego będzie pracować
unsigned long enableEndMillis = 0;

// interwał pracy
const long interval = 300;


// inicjalizacja wyświetlacza OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// zmienne dla pomiaru
int soilValue = 0;

int soilThreshold = 400;

// zmienne czasu
unsigned long previousMillis = 0;
const long measurementInterval = 1000;

// wyświetlanie danych o wilgotności
void show_soil_data() {

  // wyczyszczenie ekranu
  display.clearDisplay();

  // ustawienia tekstu
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 5);

  display.print("W:");
  display.println(soilValue);

  display.setCursor(0, 25);

  display.print("P:");
  display.println(soilThreshold);

  // aktualizacja OLED
  display.display();
}


// aktualizacja pomiaru wilgotności
void update_soil_measurement() {

  unsigned long currentMillis = millis();

  // odczyt co 1 sekunde
  if (currentMillis - previousMillis >= measurementInterval) {

    previousMillis = currentMillis;

    // odczyt wartosci analogowej
    soilValue = analogRead(SOIL_SENSOR);

    // wyswietlanie w Serial Monitor
    Serial.print("Wilgotność: ");
    Serial.println(soilValue);
  }
}


void setup() {

  // uruchomienie komunikacji szeregowej
  Serial.begin(9600);

  // inicjalizacja OLED
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
}

void update_pump() {
  unsigned long currentMillis = millis();
  
  bool buttonPushed = !digitalRead(BTN_PIN);
  if(buttonPushed || (soilValue < soilThreshold)) {
    enableEndMillis = currentMillis + interval;
  }

  Serial.print("A: ");
  Serial.print(enableEndMillis);
  Serial.print(" B: ");
  Serial.print(currentMillis);
  Serial.print(" C: ");
  Serial.println(buttonPushed);

  if(enableEndMillis > currentMillis) {
    digitalWrite(LED_PIN, HIGH );
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void loop() {

  // aktualizacja pomiaru
  update_soil_measurement();

  // wyswietlanie danych na OLED
  show_soil_data();

  update_pump();
}
