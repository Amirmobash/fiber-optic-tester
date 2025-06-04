
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

#define LDR_A A0
#define LDR_B A1
#define LED_A 2
#define LED_B 3

int readLDR(int pin) {
  int count = 0;
  for (int i = 0; i < 200; i++) {
    int val = analogRead(pin);
    if (val < 500) count++;
    delay(5);
  }
  return count;
}

void blinkLED(int pin, int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }
}

void setup() {
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  Serial.begin(9600);
}

void loop() {
  blinkLED(LED_A, 2);
  blinkLED(LED_B, 4);

  int signalA = readLDR(LDR_A);
  int signalB = readLDR(LDR_B);

  bool A_detects_2 = (signalA >= 15 && signalA <= 35);
  bool A_detects_4 = (signalA >= 60 && signalA <= 90);
  bool B_detects_2 = (signalB >= 15 && signalB <= 35);
  bool B_detects_4 = (signalB >= 60 && signalB <= 90);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  if (A_detects_2 && B_detects_4) {
    display.println("Cable OK!");
    Serial.println("A:2;B:4");
  } else if (B_detects_2 && A_detects_4) {
    display.println("Cable Reversed!");
    Serial.println("A:4;B:2");
  } else {
    display.println("Cable NOT connected!");
    Serial.println("A:0;B:0");
  }

  display.display();
  delay(2000);
}
