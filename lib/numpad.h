#include <Keypad.h>
#include <stdint.h>
#include "../lib/logs.h"

#define ASCII_DIGITS_START 48
#define ASCII_DIGITS_END 59

static time_t waiting_time, waiting_start_time;

static char keymap[ROWS][COLS]
{
  { '1', '2', '3', '4' },
  { '5', '6', '7', '8' }
};

static uint8_t row_pins[ROWS] = { R1_PIN, R2_PIN };
static uint8_t col_pins[COLS] = { C1_PIN, C2_PIN, C3_PIN, C4_PIN };

Keypad numpad = Keypad(makeKeymap(keymap), row_pins, col_pins, ROWS, COLS);

static uint8_t get_key()
{
  char key;

  logs("", "Waiting for key");
  waiting_start_time = time(NULL);
  waiting_time = 0;

  while(waiting_time <= WAIT_TIME_FOR_KEYSLOT_OPEN)
  {
    // calculate how much seconds passed from waiting start
    waiting_time = time(NULL) - waiting_start_time;
    key = numpad.getKey();

    // check if char is a ASCII digit and return keyslot id
    if (key >= ASCII_DIGITS_START && key <= ASCII_DIGITS_END) 
      return (key - ASCII_DIGITS_START);
  }

  logs("", "Timeout");
  return 0;
}
