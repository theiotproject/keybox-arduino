#pragma once

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <stdint.h>
#include "../lib/logs.h"

static MFRC522DriverPinSimple ss_pin(SDA_PIN); // Create pin driver. See typical pin layout above.
static SPIClass &spiClass = SPI; // Alternative SPI e.g. SPI2 or from library e.g. softwarespi.
static const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0); // May have to be set if hardware is not fully compatible to Arduino specifications.
static MFRC522DriverSPI driver{ss_pin, spiClass, spiSettings}; // Create SPI driver.
static MFRC522 mfrc522{driver}; // Create MFRC522 instance.

void setup_card() 
{
  mfrc522.PCD_Init(); // Init MFRC522 board.
}

bool read_card() 
{
	if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 
		return false;

  logs("Card detected");

  // get the card uid
  const MFRC522Constants::Uid &uid = mfrc522.uid;
  // array of card id number in bytes 
  uint8_t i, picc_id[uid.size];

  for (i = 0; i < uid.size; i++)
  {
    picc_id[i] = uid.uidByte[i];
    logs(picc_id[i]);
  }

  return true;
}
