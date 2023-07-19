#pragma once
#include <Arduino.h>
#include <time.h>
#include <stdint.h>

static time_t uptime;

void setup_logs(uint16_t baud)
{
  Serial.begin(baud);
}

template <typename int_or_str> 
void logs(int_or_str arg)
{
  time(&uptime);
  Serial.print("[LOG]");
  Serial.print("[ ");
  Serial.print((intmax_t) uptime);
  Serial.print(" ] ");
  Serial.println(arg);
}
