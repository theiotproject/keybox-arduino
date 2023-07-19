#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include "../lib/config.h"
#include "../lib/logs.h"
#include "../lib/run_servo.h"
#include "../lib/read_rfid.h"
#include "../lib/numpad.h"

bool btn_state;

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
    uint8_t keyslot_id = get_key();
    if (keyslot_id != NULL_KEYSLOT)
      run_servo(SERVO_OPEN_DISTANCE, keyslot_id);
  }
}
