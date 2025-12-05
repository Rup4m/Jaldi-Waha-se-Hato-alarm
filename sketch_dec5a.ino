#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;

unsigned long detectTime = 0;
bool objectNear = false;
bool secondMsgShown = false;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration;
  float distance;

  // Ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // OBJECT NEAR (<10 cm)
  if (distance < 10 && distance > 0) {

    if (!objectNear) {
      objectNear = true;
      secondMsgShown = false;
      detectTime = millis();

      // Send PLAY signal once
      Serial.println("PLAY");

      // First 2-line message
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Jaldi oha se hato");
      lcd.setCursor(0, 1);
      lcd.print("TRMCD,Utar..,");
    }

    
  }
  else {
    // NO OBJECT
    if (objectNear) {
      // Send STOP signal once
      Serial.println("STOP");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Object");

      objectNear = false;
    }
  }

  delay(50);
}
