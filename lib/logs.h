#pragma once
#include <Arduino.h>
#include <time.h>

static time_t time_res;

void setup_logs(int baud)
{
  Serial.begin(baud);
}

template <typename int_or_str> 
void logs(int_or_str arg)
{
  time_res = time(NULL);
  Serial.print("[LOG]");
  Serial.print("[ ");
  Serial.print((intmax_t) time_res);
  Serial.print(" ] ");
  Serial.println(arg);
}
