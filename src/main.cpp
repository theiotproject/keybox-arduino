#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>
#include "../lib/config.h"
#include "../lib/run_servo.h"
#include "../lib/read_rfid.h"
#include "../lib/logs.h"

bool btn_state;

void setup() 
{
  // init logs
  setup_logs(SERIAL_MONITOR_BAUD_RATE);

  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

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
    digitalWrite(LED_BLUE_PIN, HIGH);
    delay(200);
    digitalWrite(LED_BLUE_PIN, LOW);
    delay(200);

    digitalWrite(LED_BLUE_PIN, HIGH);
    delay(200);
    digitalWrite(LED_BLUE_PIN, LOW);
    delay(200);

    digitalWrite(LED_BLUE_PIN, HIGH);
    delay(200);
    digitalWrite(LED_BLUE_PIN, LOW);
    delay(200);

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
