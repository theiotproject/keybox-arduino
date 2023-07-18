#pragma once
#include <Arduino.h>

void setup_logs(int baud)
{
  Serial.begin(baud);
}

template <typename int_or_str> 
void logs(int_or_str arg)
{
  Serial.print("[LOG] ");
  Serial.println(arg);
}
