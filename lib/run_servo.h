#pragma once

#include <Servo.h>
#include <stdint.h>
#include "../lib/logs.h"

static Servo servo;
static uint8_t servo_position;

static void setup_servo()
{
  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // turn on RED LED 
  digitalWrite(LED_RED_PIN, HIGH);

  // initialize servo
  servo.attach(SERVO_ANALOG_PIN);
  servo_position = servo.read();

  // set servo to initial position
  if (servo_position != 0)
    servo.write(0);
}

// dist -> rotation distance in [mm]
// action -> move backwards to open or forward to close
static void run_servo(uint8_t dist, uint8_t key_slot_id)
{
  uint8_t deg = MIN_DEG, dist_in_deg = 0;

  if (dist > (PI_CONST * 10) || dist < 0)
    dist = PI_CONST * 10;

  // convert gear distance to degrees
  dist_in_deg = dist * (18/PI_CONST);

  logs("Servo running forwards");
  for (deg = MIN_DEG; deg < MAX_DEG; deg++)
  {
    // set new servo position and wait 15ms
    servo.write(deg);

    // the delay value slows down servo
    delay(10);
  }
    
  // turn off RED LED and turn on GREEN LED
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, HIGH);

  // waiting time in seconds
  delay(DELAY_TIME_SEC * 1000);
  
  // turn off GREEN LED and turn on RED LED
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);

  logs("Servo running backwards");
  for (deg = MAX_DEG; deg > MIN_DEG; deg--)
  {
    servo.write(deg);
    delay(10);
  }
}
