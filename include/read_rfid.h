#pragma once

#include "../config/config.h"
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <stdint.h>

MFRC522DriverPinSimple ss_pin(SDA_PIN); // Create pin driver. See typical pin layout above.

SPIClass &spiClass = SPI; // Alternative SPI e.g. SPI2 or from library e.g. softwarespi.

const SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0); // May have to be set if hardware is not fully compatible to Arduino specifications.

MFRC522DriverSPI driver{ss_pin, spiClass, spiSettings}; // Create SPI driver.

MFRC522 mfrc522{driver}; // Create MFRC522 instance.

void setup_card() 
{
  //Serial.begin(115200); // Initialize serial communications with the PC for debugging.
  //while (!Serial);      // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4).
  mfrc522.PCD_Init();   // Init MFRC522 board.
  MFRC522Debug::PCD_DumpVersionToSerial(mfrc522, Serial);	// Show details of PCD - MFRC522 Card Reader details.
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

bool read_card() 
{
	if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 
		return false;

  // MFRC522Debug::PICC_DumpToSerial(mfrc522, Serial, &(mfrc522.uid));
  return true;
}
