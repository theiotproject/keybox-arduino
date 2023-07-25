#include <Keypad.h>

#include "../../include/config.h"
#include "numpad.h"

#define ASCII_DIGITS_START 48
#define ASCII_DIGITS_END 59

time_t waiting_time, waiting_start_time;

char keymap[ROWS][COLS]
{
  { '1', '2', '3', '4' },
  { '5', '6', '7', '8' }
};

uint8_t row_pins[ROWS] = { R1_PIN, R2_PIN };
uint8_t col_pins[COLS] = { C1_PIN, C2_PIN, C3_PIN, C4_PIN };

Keypad numpad = Keypad(makeKeymap(keymap), row_pins, col_pins, ROWS, COLS);

uint8_t get_key()
{
  char key;

  Serial.println("[ Keybox Core ] Waiting for key");
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

  Serial.println("[ Keybox Core ] Timeout");
  return 0;
}
