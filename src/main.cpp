// Desk controller - M01 skeleton: simulated height via serial commands

#include <Arduino.h>

extern int __heap_start;
extern int *__brkval;

const int16_t HEIGHT_MIN_MM = 650;
const int16_t HEIGHT_MAX_MM = 1200;
const int16_t STEP_MM = 10;

int16_t heightMm = 700;                               // signed: M10 computes target - actual, which can be negative
uint16_t commandCount = 0;

int freeRam()                                         // size of the gap between heap top and stack top
{
  int top;
  int heapEnd = (__brkval == 0) ? (int)&__heap_start : (int)__brkval;
  return (int)&top - heapEnd;
}

void setup() {
  Serial.begin(115200);                               // must match monitor_speed in platformio.ini
  Serial.println(F("Desk Controller"));
  Serial.println(F("Firmware v0.1 (M01)"));
  Serial.print(F("Built: "));
  Serial.print(F(__DATE__));
  Serial.print(F(" "));
  Serial.println(F(__TIME__));
  Serial.print(F("Free SRAM: "));
  Serial.print(freeRam());
  Serial.println(F(" bytes"));
  Serial.print(F("Height: "));
  Serial.print(heightMm);
  Serial.println(F(" mm"));
}

void loop() {
  static uint32_t loopCount = 0;                      // static: survives between loop() calls; wraps after ~6 h at ~194k loops/s
  loopCount++;

  if (Serial.available() > 0) {
    char cmd = Serial.read();

    switch (cmd) {
      case 'u':
        heightMm += STEP_MM;
        if (heightMm > HEIGHT_MAX_MM) heightMm = HEIGHT_MAX_MM;
        commandCount++;
        Serial.print(F("Height: ")); Serial.print(heightMm); Serial.println(F(" mm"));
        break;

      case 'd':
        heightMm -= STEP_MM;
        if (heightMm < HEIGHT_MIN_MM) heightMm = HEIGHT_MIN_MM;
        commandCount++;
        Serial.print(F("Height: ")); Serial.print(heightMm); Serial.println(F(" mm"));
        break;

      case 's':
        commandCount++;
        Serial.print(F("Height: "));    Serial.print(heightMm);       Serial.println(F(" mm"));
        Serial.print(F("Commands: "));  Serial.println(commandCount);
        Serial.print(F("Loops: "));     Serial.println(loopCount);
        Serial.print(F("Uptime: "));    Serial.print(millis());       Serial.println(F(" ms"));
        Serial.print(F("Free SRAM: ")); Serial.print(freeRam());      Serial.println(F(" bytes"));
        break;

      case '?':
        commandCount++;
        Serial.print(F("u = up "));         Serial.print(STEP_MM);
        Serial.print(F(" mm, d = down "));  Serial.print(STEP_MM);
        Serial.println(F(" mm, s = status, ? = help"));
        break;

      case '\r':                                      // monitor sends these when Enter is pressed
      case '\n':                                      // monitor sends these when Enter is pressed
        break;

      default:
        Serial.print(F("Unknown command: "));
        Serial.println(cmd);
        break;
    }
  }
}