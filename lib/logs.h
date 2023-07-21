#pragma once
#include <Arduino.h>
#include <time.h>
#include <stdint.h>

static time_t uptime;

void setup_logs(uint16_t baud)
{
  Serial.begin(baud);
}

// could be improved by overloading (C++ only)
template <typename int_or_str> 
void logs(const char* comment, int_or_str arg)
{
  time(&uptime);
  Serial.print("[ KEYBOX CORE ]");
  Serial.print("[ ");
  Serial.print((intmax_t) uptime);
  Serial.print(" ] ");
  Serial.print(comment);
  Serial.println(arg);
}
