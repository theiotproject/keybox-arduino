#include <Servo.h>
#include <stdint.h>

#include "../manage_card/manage_card.h"
#include "../../include/config.h"
#include "run_servo.h"

Servo servo;
uint8_t servo_position;

void setup_servo()
{
  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // turn on RED LED 
  digitalWrite(LED_RED_PIN, HIGH);

  // init servo position
  servo_position = servo.read();

  // set servo to initial position
  if (servo_position != 0)
    servo.write(0);
}

// dist -> rotation distance in [mm]
void run_servo(uint8_t dist, uint8_t key)
{
  uint8_t *slots_arr = get_slots();
  size_t i;


  Serial.print("[ Keybox Core ] Slot ID: ");
  Serial.println(key);

  switch(key)
  {
    case 1:
      servo.attach(SERVO_PULSE_GPIO_1);
      break;
    case 2:
      servo.attach(SERVO_PULSE_GPIO_2);
      break;
    case 3:
      servo.attach(SERVO_PULSE_GPIO_3);
      break;
    default:
      servo.attach(NULL_SLOT);
  }

  // check access to slots
  if ((slots_arr[0] != key) && (slots_arr[1] != key) && (slots_arr[2] != key))
  {
    Serial.println("[ Keybox Core ] No access to slot");
    return;
  }
  
  uint8_t deg = MIN_DEG, dist_in_deg = 0;

  if (dist > (PI_CONST * 10) || dist < 0)
    dist = PI_CONST * 10;

  // convert gear distance to degrees
  dist_in_deg = dist * (18/PI_CONST);

  Serial.println("[ Keybox Core ] Servo running forwards");
  for (deg = MIN_DEG; deg < dist_in_deg; deg++)
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

  free(slots_arr);

  Serial.println("[ Keybox Core ] Servo running backwards");
  for (deg = dist_in_deg; deg > MIN_DEG; deg--)
  {
    servo.write(deg);
    delay(10);
  }
}
