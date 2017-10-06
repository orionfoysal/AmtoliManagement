
/*
SPI Pin in Arduino Nano

    MOSI D11
    MISO D12
    SS   D10
    SCA  D13
*/
#define SD_CS_PIN 10

#include "SdFat.h"
#include <SPI.h>
#include <String.h>

SdFat SD;
File myFile;

void setup(){
  Serial.begin(9600);
  if(!SD.begin(SD_CS_PIN)){
      Serial.println("SD card failed");
  }
  Serial.println(getName("MOCK_DATA.csv", "10-2960033"));
}

void loop(){
    
}

