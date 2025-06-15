#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// نمایشگر OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// پین‌ها
#define LED_A A2
#define LED_B A3
#define LDR_A A0
#define LDR_B A1

// پارامترها
#define BLINK_DURATION 900    // 
#define SENSITIVITY    10     // 
#define DELAY_BETWEEN  900    //
#define DELAY_RESULT   3000   // Amir Mobasheraghdam

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
    Serial.println(F("OLED init failed!"));
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
  // مقدار نور محیط
  int ldr_before = analogRead(ldrPin);
  int threshold = ldr_before + SENSITIVITY;

  // LED را روشن کن و مجدداً مقدار بگیر
  digitalWrite(ledPin, HIGH);
  delay(BLINK_DURATION);
  int ldr_after = analogRead(ldrPin);
  digitalWrite(ledPin, LOW);

  int diff = ldr_after - ldr_before;
  bool ok = (ldr_after > threshold);

  // اطلاعات دیباگ در سریال
  Serial.print("Baseline: "); Serial.print(ldr_before);
  Serial.print(" | After: "); Serial.print(ldr_after);
  Serial.print(" | Diff: "); Serial.print(diff);
  Serial.print(" | "); Serial.println(ok ? "OK" : "FAIL");

  return {diff, ok};
}

void displayResultOLED(const Result& a, const Result& b) {
  display.clearDisplay();

  // عنوان بزرگ
  display.setTextSize(2);
  display.setCursor(15, 0);
  display.println("LWL TEST");

  // نتیجه کانال A
  display.setTextSize(3);
  display.setCursor(0, 25);
  display.print("A:");
  display.print(a.ok ? "OK" : "X ");

  // نتیجه کانال B
  display.setCursor(70, 25);
  display.print("B:");
  display.print(b.ok ? "OK" : "X");

  // اختلاف Diff کوچک پایین صفحه
  display.setTextSize(1);
  display.setCursor(0, 57);
  display.print("dA:"); display.print(a.diff);
  display.print(" dB:"); display.print(b.diff);

  display.display();
}

void showSplash() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(14, 18);
  display.println("LWL TEST");
  display.setTextSize(1);
  display.setCursor(25, 45);
  display.println("Ready!");
  display.display();
  delay(1500);
}
