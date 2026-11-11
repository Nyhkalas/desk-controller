#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println(F("Desk Controller"));
  Serial.println(F("Firmware v0.1 (M01)"));
  Serial.print(F("Built: "));
  Serial.print(F(__DATE__));
  Serial.print(F(" "));
  Serial.println(F(__TIME__));
}

void loop() {
  
}