#pragma once

#include <Servo.h>

// important "magic numbers" (sth like settings for calibration)
#define PI_CONST 3.1415
#define MAX_DEG 180
#define MIN_DEG 0
#define SERVO_ANALOG_PIN 9
#define SERVO_OPEN 1
#define SERVO_CLOSE 0
#define SERVO_OPEN_DISTANCE 31

// dist -> rotation distance in [mm]
// action -> move backwards to open or forward to close
static void run_servo(Servo servo_instance, int dist, bool action)
{
  int deg = MIN_DEG, dist_in_deg = 0;

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
      servo_instance.write(deg);
      // the delay value slows down servo
      delay(15);
    }
  } 
  else
  {
    // close
    for (deg = dist_in_deg; deg >= MIN_DEG; deg--)
    {
      servo_instance.write(deg);
      delay(15);
    }
  }
}
