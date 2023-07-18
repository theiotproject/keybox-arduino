#pragma once

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <stdint.h>
#include "../lib/logs.h"

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
  return true;
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
	if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 
		return false;

  logs("Card detected");

  if (check_access())
  {
    // access LED signal, blink 3 times
    for (uint8_t i = 0; i < 3; i++)
    {
      digitalWrite(LED_BLUE_PIN, HIGH);
      delay(200);
      digitalWrite(LED_BLUE_PIN, LOW);
      delay(200);
    }
    // get the card uid
    const MFRC522Constants::Uid &uid = mfrc522.uid;

    // array of card id in bytes 
    uint8_t picc_id[uid.size];

    // add bytes to array
    for (uint8_t i = 0; i < uid.size; i++)
      picc_id[i] = uid.uidByte[i];

    return true;
  }
  else 
  {
    return false;
  }
}
