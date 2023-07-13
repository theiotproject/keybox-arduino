#include "./config/config.h"
#include "./include/run_servo.h"

Servo servo;
int servo_position;
bool btn_state;

void setup() 
{
  servo.attach(SERVO_ANALOG_PIN);

  servo_position = servo.read();

  // set servo to initial position
  if (servo_position != 0)
    servo.write(0);

  // set debug monitor baud rate
  Serial.begin(9600);

  // init button pin
  pinMode(BTN_PIN, INPUT_PULLUP);

  // init diode pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
}

void loop() 
{
  btn_state = digitalRead(BTN_PIN);

  // print button state in serial monitor FALSE if ON, TRUE if OFF
  Serial.println(btn_state);

  // turn on RED LED 
  digitalWrite(LED_RED_PIN, HIGH);
  
  // run servo if btn is pressed
  if (!btn_state)
  {
    run_servo(servo, SERVO_OPEN_DISTANCE, SERVO_OPEN);

    // turn off RED LED and turn on GREEN LED
    //digitalWrite(LED_RED_PIN, LOW);
    //digitalWrite(LED_GREEN_PIN, HIGH);

    // waiting time in seconds
    delay(DELAY_TIME_SEC * 1000);

    // turn off GREEN LED and turn on RED LED
    //digitalWrite(LED_GREEN_PIN, LOW);
    //digitalWrite(LED_RED_PIN, HIGH);

    run_servo(servo, SERVO_OPEN_DISTANCE, SERVO_CLOSE);
  }
}
