/*
SPI Pin in Arduino Nano

    MOSI D11
    MISO D12
    SS   D10
    SCA  D13
*/

/* ********************************
 *      Define SD card Pin
 **********************************/ 
#define SD_CS_PIN 10 

/**********************************
 *      Define RFID Card PINS
 * ********************************/
#define RST_PIN  9   
#define SS_PIN  10

/**********************************
 *     Include Necessary Libraries
 * ********************************/
#include "SdFat.h"
#include <SPI.h>
#include <String.h>
#include <MFRC522.h>

/****************************************
 *      Initialize SD and RFID Card
 * **************************************/
SdFat SD;
File myFile;

MFRC522 rfid(SS_PIN, RST_PIN);



void setup(){
  Serial.begin(9600);
  if(!SD.begin(SD_CS_PIN)){
      Serial.println("SD card failed");
  }

  readWrite();

  Serial.println(getName("MOCK_DATA.csv", "10-2960033"));

/*******************************
 *     RFID Card
 * ****************************/

  String tempID = taskRFID(); 
  // put your main code here, to run repeatedly:
  if(tempID != UID && tempID != "NULL"){
    Serial.println("Got It");
    UID = tempID;
    Serial.println(UID);
  }
  else if(tempID == UID)
    Serial.println("Card Once Read In this Session");
}

void loop(){
    
}

String taskRFID()
{
    String cardNumber;
    byte uidArray[4];

    // Look for new cards
    if ( ! rfid.PICC_IsNewCardPresent())
        return "NULL";

    // Verify if the NUID has been readed
    if ( ! rfid.PICC_ReadCardSerial())
        return "NULL";

    // Serial.print(F("PICC type: "));
    // MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    // Serial.println(rfid.PICC_GetTypeName(piccType));
    
    /* 
        Store NUID into uidArray. Then copy it to a String. If we read directly from the buffer then buffer will be cleared and we cant check if
        it is pressed again. It would be more efficient if we directly return the byte pointer but it might create problem in assign in future (?)
    */
    for (byte i = 0; i < 4; i++) {
        uidArray[i] = rfid.uid.uidByte[i];
        cardNumber += uidArray[i];
    }
    
//    Serial.println(F("The NUID tag is:"));    
//    Serial.println(cardNumber);

    return cardNumber;

}

//This is for only testing two SPI simultaeneously 
//Will be deleted after this

void readWrite(){

myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
