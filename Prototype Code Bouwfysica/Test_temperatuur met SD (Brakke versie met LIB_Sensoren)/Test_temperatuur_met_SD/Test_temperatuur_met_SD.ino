// ----------  Include Libraries  ------------- //

#include <OneWire.h> 
#include <DallasTemperature.h>
#include "LIB_sensoren.h"
#include <SPI.h>
#include <SD.h>


// -----------------  SD - Card  ------------------------ //

const int CHIPSELECT = 10; // is specifiek voor Ethernet Shield 2
const String DATA = "hallo"; 
const String FN = "data.log";
#define DELAY 500


// ----------  Ds18b20  temperature Sensor  ------------- //


// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);




// ----------  Dht22 temperature Sensor  ------------- //

// minT(C), maxT(C), minHum(%), maxHum(%)
TemperatureSensor temperatureSensor(16, 28, 35, 85);




void setup() { 
  
 Serial.begin(9600); 

  if (temperatureSensor.Start())
    Serial.println("Dht22 Temperature sensor ok!");
  else
    Serial.println("Failed to start Dht22!");

  Serial.println("Temp (C), Hum(%)");



    sensors.begin();
  if(1==1)                                                                                    //Somethings wrong here
    Serial.println("Dallas Temperature sensor ok!"); 
  else
    Serial.println("Failed to start Ds18b20!");

  Serial.println("Temp (C)");
  

 bool SDKaart = false;
  if (!SD.begin(CHIPSELECT)) {
    Serial.println(" geen SD kaart gevonden!");
    delay(100);
  }
  else {
    Serial.println(" SD kaart OK!");
    SDKaart = true;
    delay(100);
  }

  if (SDKaart) {

  
      File dataFile = SD.open(FN, FILE_WRITE);
      dataFile.println(" --- New Start --- ");
      Serial.println(dataFile);
      dataFile.close();
      delay(100);     
  }
}

void loop() { 

  temperatureSensor.Read();
  Serial.print("Temperature Dht22 is:   ");
  temperatureSensor.PrintSerial();
  Serial.println();

  
  delay(50);



 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 

  // Serial.print(" Requesting temperature Ds18b20..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  // Serial.println("Done"); 

  Serial.print("Temperature Ds18b20 is: "); 
  Serial.println(sensors.getTempCByIndex(0));
   
   /* Why "byIndex"?  
      You can have more than one DS18B20 on the same bus.  
    0 refers to the first IC on the wire */

   delay(50);

   File dataFile = SD.open(FN, FILE_WRITE);
    
    if (dataFile) {


         // Temperature and humidity

        bool DataTemp1 = temperatureSensor.Read();
        dataFile.print(DataTemp1);
        dataFile.print(" (°C,%)");
        dataFile.print(",   ");
        bool DataTemp2 = sensors.getTempCByIndex(0);
        dataFile.print(DataTemp2);
        dataFile.print(" (°C)");
    }
    
  delay(900); 
} 
