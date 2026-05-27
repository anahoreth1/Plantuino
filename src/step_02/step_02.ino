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

// inicjalizacja wyświetlacza OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// zmienne dla pomiaru
int soilValue = 0;

// zmienne czasu
unsigned long previousMillis = 0;
const long interval = 1000;

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

  // aktualizacja OLED
  display.display();
}


// aktualizacja pomiaru wilgotności
void update_soil_measurement() {

  unsigned long currentMillis = millis();

  // odczyt co 1 sekunde
  if (currentMillis - previousMillis >= interval) {

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
}


void loop() {

  // aktualizacja pomiaru
  update_soil_measurement();

  // wyswietlanie danych na OLED
  show_soil_data();
}
