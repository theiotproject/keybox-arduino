#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include "../lib/config.h"
#include "../lib/run_servo.h"
#include "../lib/read_rfid.h"

bool btn_state;

void setup() 
{
  // set debug monitor baud rate
  Serial.begin(SERIAL_MONITOR_BAUD_RATE);

  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  // turn on RED LED 
  digitalWrite(LED_RED_PIN, HIGH);

  // init devices
  setup_card();
  setup_servo();
}

void loop() 
{
  if(read_card())
  {
    Serial.println("[LOG] Card detected!");
    run_servo(SERVO_OPEN_DISTANCE, SERVO_OPEN);

    // turn off RED LED and turn on GREEN LED
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);

    // waiting time in seconds
    delay(DELAY_TIME_SEC * 1000);

    // turn off GREEN LED and turn on RED LED
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);

    run_servo(SERVO_OPEN_DISTANCE, SERVO_CLOSE);
  }
}
