#include <Servo.h>

// important "magic numbers" (sth like settings for calibration)
#define MAX_DEG 180
#define MIN_DEG 0
#define PI_CONST 3.1415
#define SERVO_ANALOG_PIN 9
#define SERVO_OPEN 1
#define SERVO_CLOSE 0
#define SERVO_OPEN_DISTANCE 31
#define DELAY_TIME_SEC 3
#define BTN_PIN 7
#define LED_RED_PIN 2
#define LED_GREEN_PIN 4

Servo servo;
int servo_position;
bool btn_state;

// dist -> rotation distance in [mm]
// action -> move backwards to open or forward to close
void run_servo(int dist, bool action)
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
      // the delay value makes servo run in some "speed"
      servo.write(deg);
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

void setup() 
{
  servo.attach(SERVO_ANALOG_PIN);
  servo_position = servo.read();

  // set servo to initial position
  if (servo_position != 0)
    servo.write(0);

  // set debug monitor baud rate
  Serial.begin(9600);
  Serial.println(servo_position);

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
