#include <Arduino.h>

extern int __heap_start;
extern int *__brkval;

int freeRam() {
  int top;
  int heapEnd = (__brkval == 0) ? (int)&__heap_start : (int)__brkval;
  return (int)&top - heapEnd;
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("Desk Controller"));
  Serial.println(F("Firmware v0.1 (M01)"));
  Serial.print(F("Built: "));
  Serial.print(F(__DATE__));
  Serial.print(F(" "));
  Serial.println(F(__TIME__));
  Serial.print(F("Free SRAM: "));
  Serial.print(freeRam());
  Serial.print(F(" bytes"));
}

void loop() {
  
}