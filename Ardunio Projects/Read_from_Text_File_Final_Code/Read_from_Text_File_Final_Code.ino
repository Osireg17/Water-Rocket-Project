/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

File Group2;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  Group2 = SD.open("Final_Test8.txt", FILE_WRITE);

  // re-open the file for reading:
  Group2 = SD.open("Final_Test8.txt");
  if (Group2) {
    Serial.println("Final_Test8.txt:");

    // read from the file until there's nothing else in it:
    while (Group2.available()) {
      Serial.write(Group2.read());
    }
    // close the file:
    Group2.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Final_Test8.txt");
  }
}

void loop() {
  // nothing happens after setup
}
