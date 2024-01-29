#pragma once
#include <Arduino.h>
#ifdef UART_DEBUG
    #define DEBUG(str) Serial.printf("%s:%d %s; millis: %ld; msg: %s\n", \
     __FILE__, __LINE__, __PRETTY_FUNCTION__, millis(), String(str).c_str());
#else
  #define DEBUG(str)
#endif