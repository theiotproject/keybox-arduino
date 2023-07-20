#pragma once

// GENERAL PURPOSE
#define PI_CONST 3.1415
#define SERIAL_MONITOR_BAUD_RATE 9600
#define WAIT_TIME_FOR_KEYSLOT_OPEN 5
#define NULL_SLOT 0
#define MAX_SLOTS 16
#define MAX_CARDS 16

// BTN
#define BTN_PIN 16

// LEDs
#define LED_RED_PIN 27
#define LED_GREEN_PIN 26
#define LED_BLUE_PIN 25
#define BUILTIN_LED 2 

// SERVO
#define SERVO_ANALOG_PIN 13
#define DELAY_TIME_SEC 3
#define SERVO_OPEN 1
#define SERVO_CLOSE 0
#define SERVO_OPEN_DISTANCE 20
#define MAX_DEG 180
#define MIN_DEG 0
#define MAX_PULSE 2400
#define MIN_PULSE 500

// RFID RC522
#define SCK_PIN 18
#define MISO_PIN 19
#define SDA_PIN 5
#define MOSI_PIN 23
#define RST_PIN 21

// KEYPAD
#define R1_PIN 14
#define R2_PIN 15
#define C1_PIN 32
#define C2_PIN 33
#define C3_PIN 16
#define C4_PIN 17
#define ROWS 2
#define COLS 4
