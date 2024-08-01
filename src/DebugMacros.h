#pragma once

#include <Arduino.h>

#ifdef DEBUG_RS
  #define PRINT_RS(...)  Serial.print(__VA_ARGS__)
  #define PRINTLN_RS(...) Serial.println(__VA_ARGS__)
  #define PRINTF_RS(...)  Serial.printf(__VA_ARGS__)
  #define PRINTLN_ERR_RS Serial.println(String(__FILE__) + " [" + String(__FUNCTION__) + "]:" + String(__LINE__) + "  **********************************************")
  #define START_TIME_SENSOR_MS uint32_t __ms__ = millis();
  #define STOP_TIME_SENSOR_MS   __ms__ = millis() - __ms__; if (__ms__ > 100) Serial.println(String("############## time: ") + __ms__ + String(" ms"));
#else
  #define PRINT_RS(...)
  #define PRINTLN_RS(...)
  #define PRINTF_RS(...)
  #define START_TIME_SENSOR_MS
  #define STOP_TIME_SENSOR_MS
#endif