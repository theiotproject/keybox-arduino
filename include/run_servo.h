#pragma once

#include "../config/config.h"
#include <Servo.h>
#include <stdint.h>

static Servo servo;
static uint8_t servo_position;

static void setup_servo()
{
  // initialize servo
  servo.attach(SERVO_ANALOG_PIN);
  servo_position = servo.read();

  // set servo to initial position
  if (servo_position != 0)
    servo.write(0);
}

// dist -> rotation distance in [mm]
// action -> move backwards to open or forward to close
static void run_servo(uint8_t dist, bool action)
{
  uint8_t deg = MIN_DEG, dist_in_deg = 0;

  if (dist > (PI_CONST * 10) || dist < 0)
    dist = PI_CONST * 10;

  // convert gear distance to degrees
  dist_in_deg = dist * (18/PI_CONST);

  if (action)
  {
    // open
    for (deg = MIN_DEG; deg <= dist_in_deg; deg++)
    {
      // set new servo position and wait 15ms
      servo.write(deg);
      // the delay value slows down servo
      delay(15);
    }
  } 
  else
  {
    // close
    for (deg = dist_in_deg; deg >= MIN_DEG; deg--)
    {
      servo.write(deg);
      delay(15);
    }
  }
}
