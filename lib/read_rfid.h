#pragma once

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/logs.h"
#include "../lib/manage_card.h"

// Create pin driver. See typical pin layout above.
static MFRC522DriverPinSimple ss_pin(SDA_PIN); 
// Alternative SPI e.g. SPI2 or from library e.g. softwarespi.
static SPIClass &spiClass = SPI; 
// May have to be set if hardware is not fully compatible to Arduino specifications.
static const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0); 
// Create SPI driver.
static MFRC522DriverSPI driver{ss_pin, spiClass, spiSettings}; 
// Create MFRC522 instance.
static MFRC522 mfrc522{driver}; 

bool check_access()
{
  bool is_access = false;
  uint64_t* cards_arr = get_cards();
  uint64_t* slots_arr = get_slots();

  // get the card id
  const MFRC522Constants::Uid* uid = &mfrc522.uid;

  // array of card id in bytes 
  char picc_id_str[uid->size]; 
  uint8_t picc_id_byte;
  uint64_t picc_id_int;

  // add bytes to array
  for (uint8_t i = 0; i < uid->size; i++)
    picc_id_byte += sprintf(&picc_id_str[picc_id_byte], "%d", uid->uidByte[i]);

  picc_id_int = atoll(picc_id_str);

  // log card id
  logs(picc_id_int);

  // check if card has access
  if (picc_id_int == cards_arr[1])
    is_access = true;

  free(cards_arr);
  free(keyslots_arr);

  return is_access;
}

void setup_card() 
{
  // init diode pins
  pinMode(LED_BLUE_PIN, OUTPUT);

  // Init MFRC522 board.
  mfrc522.PCD_Init(); 
}

bool read_card() 
{
	if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
  {
    logs("Card detected");

    if (check_access())
    {
      logs("Access granted");

      // blink 3 times
      for (uint8_t i = 0; i < 3; i++)
      {
        digitalWrite(LED_BLUE_PIN, HIGH);
        delay(200);
        digitalWrite(LED_BLUE_PIN, LOW);
        delay(200);
      }
      
      return true;
    }
    else 
    {
      logs("Access denied");

      // blink once
      digitalWrite(LED_BLUE_PIN, HIGH);
      delay(1000);
      digitalWrite(LED_BLUE_PIN, LOW);

      return false;
    }
  }

  // stand by state
	return false;
}
