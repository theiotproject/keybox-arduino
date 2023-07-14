#include "./config/config.h"
#include "./include/run_servo.h"
#include "./include/read_rfid.h"
#include <stdint.h>

bool btn_state;

void setup() 
{
  // set debug monitor baud rate
  Serial.begin(SERIAL_MONITOR_BAUD_RATE);

  // init button pin
  pinMode(BTN_PIN, INPUT_PULLUP);

  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  // init devices
  setup_card();
  setup_servo();
}

void loop() 
{
  //btn_state = digitalRead(BTN_PIN);

  // print button state in serial monitor FALSE if ON, TRUE if OFF
  // Serial.println(btn_state);

  // turn on RED LED 
  digitalWrite(LED_RED_PIN, HIGH);
  
  // read rfid card
  //if(read_card())
  //{
    //digitalWrite(BUILTIN_LED, HIGH);
    //delay(1000);
    //digitalWrite(BUILTIN_LED, LOW);
  //}
  
  // run servo if btn is pressed
  // if (!btn_state)
  if(read_card())
  {
    Serial.print("[LOG] Card detected");
    //run_servo(SERVO_OPEN_DISTANCE, SERVO_OPEN);

    // turn off RED LED and turn on GREEN LED
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);

    // waiting time in seconds
    delay(DELAY_TIME_SEC * 1000);

    // turn off GREEN LED and turn on RED LED
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);

    //run_servo(SERVO_OPEN_DISTANCE, SERVO_CLOSE);
  }
}
