#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <L3G.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

unsigned long myTime;

const int buzzer = 9;

Adafruit_BME280 bme;
L3G gyro;
File Group2;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

 
  Wire.begin();

  if (!gyro.init()) {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();

  bool status;
  
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println("-- Default Test --");

  Serial.println();

  pinMode(buzzer, OUTPUT);
  
}

void loop() { 
  printValues();
  gyro_value();
  buzzer_sound();
  Time();
  delay(1000);
}


void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Group2 = SD.open("test.txt", FILE_WRITE);
   if (Group2) {
    Group2.print(F("Temperature: "));Group2.println(bme.readTemperature());
    Group2.print(F("Altitude: "));Group2.println(bme.readAltitude((SEALEVELPRESSURE_HPA)));
    Group2.print(F("Humidity: "));Group2.println(bme.readHumidity());
    Group2.print(F("Pressure "));Group2.println(bme.readPressure());
    // close the file:
    Group2.close();

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Trial2.txt");
  }
  
  Serial.println();
}
void gyro_value() {
  // nothing happens after setup
  gyro.read();

  float xDPS = (gyro.g.x * 8.75) / 1000;
  float yDPS = (gyro.g.y * 8.75) / 1000;
  float zDPS = (gyro.g.z * 8.75) / 1000;

  //float xRAD = xDPS * (3.14159 / 180);
  //float yRAD = yDPS * (3.14159 / 180);
  //float zRAD = zDPS * (3.14159 / 180);

  Serial.print("Gyroscope X Values: ");
  Serial.print(xDPS);
  Serial.print("Gyroscope Y Values: ");
  Serial.print(yDPS);
  Serial.print("Gyroscope Z Values: ");
  Serial.println(zDPS);

  Group2 = SD.open("test.txt", FILE_WRITE);
   if (Group2) {
    Group2.print(F("Gyro X Values: "));Group2.println(xDPS);
    Group2.print(F("Gyro Y Values: "));Group2.println(yDPS);
    Group2.print(F("Gyro Z Values: "));Group2.println(zDPS);
    // close the file:
    Group2.close();

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void buzzer_sound(){

  tone(buzzer, 1000); // Send 1KHz sound signal...       // ...for 1 sec
  noTone(buzzer);     // Stop sound...       // ...for 1sec
  
}

void Time() {
  Serial.print("Time: ");
  myTime = millis();

  Serial.println(myTime);

  Group2 = SD.open("test.txt", FILE_WRITE);
   if (Group2) {
    Group2.println("Time:");
    Group2.println(myTime);
    Group2.println("s");
    // close the file:
    Group2.close();

  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
