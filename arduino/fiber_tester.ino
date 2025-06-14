#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED-Amirips
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
#define LED_A A2
#define LED_B A3
#define LDR_A A0
#define LDR_B A1

// Parameter
#define BLINK_DURATION 900    // LED-Einschaltdauer (ms)
#define SENSITIVITY    15     // Empfindlichkeitsschwelle
#define DELAY_BETWEEN  900    // Verzögerung zwischen Test A und B
#define DELAY_RESULT   3000   // Ergebnisanzeigedauer

struct Result {
  int ldr_before;
  int ldr_after;
  int diff;
  bool ok;
};

void showWelcomeAnimation() {
  display.clearDisplay();
  
  // Animationseffekt - einlaufender Text
  for(int i=0; i<4; i++) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    
    // LWL-TESTER Animation
    display.setTextSize(2);
    display.setCursor(10, 5);
    display.println("LWL-TESTER");
    
    // Entwickler-Info mit Animation
    display.setTextSize(1);
    display.setCursor(10 + (i*10), 30);
    display.print("Amir Mobasher");
    
    // Unterer animierter Balken
    display.fillRect(0, 50, 20 + (i*30), 5, SSD1306_WHITE);
    
    display.display();
    delay(200);
  }
  
  // Finale Ansicht für 2 Sekunden
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(5, 5);
  display.println("LWL-TESTER");
  
  display.setTextSize(1);
  display.setCursor(35, 30);
  display.println("    AMIR");
  
  display.setTextSize(1);
  display.setCursor(10, 50);
  display.println("Initialisierung...");
  display.display();
  delay(2000);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);

  // OLED-Initialisierung
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("OLED-Initialisierung fehlgeschlagen"));
    while (1);
  }
  
  // Begrüßungsanimation anzeigen
  showWelcomeAnimation();
}

void loop() {
  Result a = testChannel("A", LED_A, LDR_A);
  delay(DELAY_BETWEEN);
  Result b = testChannel("B", LED_B, LDR_B);

  displayResultOLED(a, b);
  delay(DELAY_RESULT);
}

Result testChannel(const char* name, int ledPin, int ldrPin) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("Teste Kanal ");
  display.print(name);
  display.display();

  int ldr_before = analogRead(ldrPin);
  int threshold = ldr_before + SENSITIVITY;

  Serial.print("["), Serial.print(name), Serial.println("]");
  Serial.print("Umgebungslicht: "), Serial.print(ldr_before);
  Serial.print(" | Schwellenwert: "), Serial.println(threshold);

  digitalWrite(ledPin, HIGH);
  delay(BLINK_DURATION);
  int ldr_after = analogRead(ldrPin);
  digitalWrite(ledPin, LOW);

  int diff = ldr_after - ldr_before;

  Serial.print("LED-Licht: "), Serial.print(ldr_after);
  Serial.print(" | Differenz: "), Serial.print(diff);

  bool ok = (ldr_after > threshold);
  if (ok) {
    Serial.println(" => SIGNAL ✔");
  } else {
    Serial.println(" => KEIN SIGNAL ✗");
  }

  return {ldr_before, ldr_after, diff, ok};
}

void displayResultOLED(const Result& a, const Result& b) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  //display.setTextSize(1);
  //display.setCursor(0, 0);
  //display.println("LWL-KABELTESTER");
  //display.println("von AMIR");  // Dein Name bleibt sichtbar

  display.setCursor(0, 5);
  display.print("A Diff: "); display.print(a.diff);
  display.print(" | B Diff: "); display.print(b.diff);

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print("A: ");
  display.print(a.ok ? "OK" : "X ");
  display.setCursor(68, 25);
  display.print("B: ");
  display.print(b.ok ? "OK" : "X ");

  display.setTextSize(1);
  display.setCursor(0, 55);
  display.print("Empfindlichkeit: ");
  display.print(SENSITIVITY);
  display.display();
}
