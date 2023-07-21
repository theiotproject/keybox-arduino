#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include "../lib/config.h"
#include "../lib/logs.h"
#include "../lib/run_servo.h"
#include "../lib/read_rfid.h"
#include "../lib/numpad.h"
#include "../lib/manage_card.h"

void setup() 
{
  // init logs
  setup_logs(SERIAL_MONITOR_BAUD_RATE);

  // init devices
  setup_card();
  setup_servo();
}

void loop() 
{
  if(read_card())
  {
    // key -> slot id
    uint8_t key = get_key();
    if (key != NULL_SLOT)
      run_servo(SERVO_OPEN_DISTANCE, key);
  }
}
