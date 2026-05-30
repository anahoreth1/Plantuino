#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ustawienia OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// czujniki
#define SOIL_SENSOR A0
#define POTENTIOMETER A1

// LED
#define LED_PIN 7

// OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pomiary
int soilValue = 0;
int thresholdValue = 0;

// czas
unsigned long previousMillis = 0;
const long interval = 1000;


// wyświetlanie danych
void show_data() {

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("W:");
  display.println(soilValue);

  display.setCursor(0, 30);
  display.print("P:");
  display.println(thresholdValue);

  display.display();
}


// odczyt czujników
void update_measurements() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    soilValue = analogRead(SOIL_SENSOR);
    thresholdValue = analogRead(POTENTIOMETER);

    Serial.print("Wilgotnosc: ");
    Serial.print(soilValue);

    Serial.print(" | Prog: ");
    Serial.println(thresholdValue);
  }
}


// sterowanie LED
void update_led() {

  if (soilValue > thresholdValue) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}


void setup() {

  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}


void loop() {

  update_measurements();

  update_led();

  show_data();
}
