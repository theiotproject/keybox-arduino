#include <Servo.h>

#define MAX_DEG 180
#define MIN_DEG 0
#define PI_CONST 3.1415
#define SERVO_ANALOG_PIN 9
#define SERVO_OPEN 1
#define SERVO_CLOSE 0
#define DELAY_TIME_SEC 3
#define BTN_PIN 7
#define LED_RED_PIN 2
#define LED_GREEN_PIN 4

Servo demo_servo;
int pos;
bool btn_state;

// dist -> rotate distance in [mm]
// action -> move backward to open or forward to close
void run_servo(int dist, bool action)
{
  int deg = MIN_DEG, dist_in_deg = 0;

  if (dist > (PI_CONST * 10) || dist < 0)
    dist = PI_CONST * 10;

  // convert rotation distance to degrees
  dist_in_deg = dist * (18/PI_CONST);

  if (action)
  {
    // open
    for (deg = MIN_DEG; deg <= dist_in_deg; deg++)
    {
      demo_servo.write(deg);
      delay(15);
    }
  } 
  else
  {
    //close
    for (deg = dist_in_deg; deg >= MIN_DEG; deg--)
    {
      demo_servo.write(deg);
      delay(15);
    }
  }
}

void setup() 
{
  demo_servo.attach(SERVO_ANALOG_PIN);
  pos = demo_servo.read();

  if (pos != 0)
    demo_servo.write(0);

  // debug servo pos
  Serial.begin(9600);
  Serial.println(pos);

  // init btn pin
  pinMode(BTN_PIN, INPUT_PULLUP);

  // init diodes pins
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
}

void loop() 
{
  btn_state = digitalRead(BTN_PIN);
  Serial.println(btn_state);

  // turn on red diode
  digitalWrite(LED_RED_PIN, HIGH);

  // run servo if btn is pushed
  if (!btn_state)
  {
    run_servo(31, SERVO_OPEN);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(DELAY_TIME_SEC * 1000);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);
    run_servo(31, SERVO_CLOSE);
  }
}
