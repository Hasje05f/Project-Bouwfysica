// ----------  Include Libraries  ------------- //

#include <OneWire.h> 
#include <DallasTemperature.h>
#include <DHT.h>



// ----------  Ds18b20  temperature Sensor  ------------- //


// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);




// ----------  Dht22 temperature Sensor  ------------- //


#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables

int chk;

float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() { 
  
 Serial.begin(9600); 

    dht.begin();
    
  if (1==1)
    Serial.println("Dht22 Temperature sensor ok!");
  else
    Serial.println("Failed to start Dht22!");

  Serial.println("Temp (°C), Hum(%)");

    sensors.begin();
  if(1==1)                                                                                    //Somethings wrong here
    Serial.println("Dallas Temperature sensor ok!"); 
  else
    Serial.println("Failed to start Ds18b20!");

 //  Serial.println("Temp (°C)");
  
} 


void loop() { 

   delay(50);
   
    hum = dht.readHumidity();
    temp= dht.readTemperature();
                
    //Print temp and humidity values to serial monitor
    

    Serial.print("Temperature DHT22 is:, ");
    Serial.print(temp);
    Serial.print(" °C,    ");
    Serial.print(hum);
    Serial.println(" %");
    

    delay(50); 

  
 // Serial.println(" ");

 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 

  // Serial.print(" Requesting temperature Ds18b20..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  // Serial.println("Done"); 

  Serial.print("Temperature Ds18b20 is: "); 
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" °C"); 
   /* Why "byIndex"?  
      You can have more than one DS18B20 on the same bus.  
    0 refers to the first IC on the wire */

 // Serial.println(" ");


    
  delay(900); 
} 