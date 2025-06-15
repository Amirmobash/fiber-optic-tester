#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED-Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
#define LED_A A2
#define LED_B A3
#define LDR_A A0
#define LDR_B A1

// Parameter
#define BLINK_DURATION 900    // LED-Einschaltdauer (ms)
#define SENSITIVITY    10     // Schwelle für Signal-Erkennung
#define DELAY_BETWEEN  900    // Pause zwischen A und B (ms)
#define DELAY_RESULT   3000   // Anzeige-Dauer für Ergebnis

struct Result {
  int diff;
  bool ok;
};

void setup() {
  Serial.begin(9600);

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED-Initialisierung fehlgeschlagen!"));
    while (1);
  }
  showSplash();
}

void loop() {
  Result a = testChannel(LED_A, LDR_A);
  delay(DELAY_BETWEEN);
  Result b = testChannel(LED_B, LDR_B);

  displayResultOLED(a, b);
  delay(DELAY_RESULT);
}

Result testChannel(int ledPin, int ldrPin) {
  int ldr_before = analogRead(ldrPin);
  int threshold = ldr_before + SENSITIVITY;

  digitalWrite(ledPin, HIGH);
  delay(BLINK_DURATION);
  int ldr_after = analogRead(ldrPin);
  digitalWrite(ledPin, LOW);

  int diff = ldr_after - ldr_before;
  bool ok = (ldr_after > threshold);

  Serial.print("Basis: "); Serial.print(ldr_before);
  Serial.print(" | Nachher: "); Serial.print(ldr_after);
  Serial.print(" | Differenz: "); Serial.print(diff);
  Serial.print(" | "); Serial.println(ok ? "OK" : "FEHLER");

  return {diff, ok};
}

void displayResultOLED(const Result& a, const Result& b) {
  display.clearDisplay();

  // Großer Titel
  display.setTextSize(2);
  display.setCursor(15, 0);
  display.println("LWL-TEST");

  // Ergebnis Kanal A
  display.setTextSize(3);
  display.setCursor(0, 25);
  display.print("A:");
  display.print(a.ok ? "OK" : "X ");

  // Ergebnis Kanal B
  display.setCursor(70, 25);
  display.print("B:");
  display.print(b.ok ? "OK" : "X");

  // Differenz unten klein anzeigen + Name
  display.setTextSize(1);
  display.setCursor(0, 57);
  display.print("dA:"); display.print(a.diff);
  display.print(" dB:"); display.print(b.diff);
  display.setCursor(90, 57);
  display.print("Amir");

  display.display();
}

void showSplash() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(14, 18);
  display.println("LWL-TEST");
  display.setTextSize(1);
  display.setCursor(25, 45);
  display.println("von Amir");
  display.display();
  delay(1500);
}
