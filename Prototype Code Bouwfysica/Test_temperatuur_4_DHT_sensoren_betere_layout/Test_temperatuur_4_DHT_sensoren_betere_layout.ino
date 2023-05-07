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
#define DHT2PIN 7
#define DHT3PIN 8
#define DHT4PIN 9
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
DHT dht2(DHT2PIN, DHTTYPE); 
DHT dht3(DHT3PIN, DHTTYPE); 
DHT dht4(DHT4PIN, DHTTYPE); 

//Variables

int chk;
int i = 1;

float hum;  //Stores humidity value
float temp; //Stores temperature value

float hum2;  //Stores humidity value
float temp2; //Stores temperature value

float hum3;  //Stores humidity value
float temp3; //Stores temperature value

float hum4;  //Stores humidity value
float temp4; //Stores temperature value



void setup() { 
  
 Serial.begin(9600); 

    dht.begin();
    dht2.begin();
    dht3.begin();
    dht4.begin();
    
  if (1==1)
    Serial.println("Dht22 Temperature sensors ok!");
  else
    Serial.println("Failed to start Dht22!");

  Serial.println("Temp (°C) ");
//  Serial.println("Hum(%)");
  
    sensors.begin();
  if(1==1)                                                                                    //Somethings wrong here
    Serial.println("Dallas Temperature sensor ok!"); 
  else
    Serial.println("Failed to start Ds18b20!");

  Serial.println("Temp (°C)");

  Serial.println("            ,Nr.: , DHT 1, DHT 2, DHT 3, DHT 4, ,Ref.:");
  
} 


void loop() { 


   delay(50);
   
    temp= dht.readTemperature();
    temp2= dht2.readTemperature();
    temp3= dht3.readTemperature();
    temp4= dht4.readTemperature();
    
    //Print temp values to serial monitor
    
    Serial.print("Temperature:, ");
    
    Serial.print(i);
    Serial.print(",   ");
    i++;
    
    Serial.print(temp);
    Serial.print(" °C,   ");
    Serial.print(temp2);
    Serial.print(" °C,   ");
    Serial.print(temp3);
    Serial.print(" °C,   ");
    Serial.print(temp4);
    Serial.print(" °C,   ");

 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 

  // Serial.print(" Requesting temperature Ds18b20..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  // Serial.println("Done"); 
  
//  Serial.print("Ref.:, "); 
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" °C"); 
  
   /* Why "byIndex"?  
      You can have more than one DS18B20 on the same bus.  
    0 refers to the first IC on the wire */   

 /*  delay(50);

    hum = dht.readHumidity();
    hum2 = dht2.readHumidity();
    hum3 = dht3.readHumidity();
    hum4 = dht4.readHumidity();
          
    //Print humidity values to serial monitor  
                    
    Serial.print("Humidity:,    ");
    Serial.print(hum);
    Serial.print(" %,    ");
    Serial.print(hum2);
    Serial.print(" %,    ");
    Serial.print(hum3);
    Serial.print(" %,    ");
    Serial.print(hum4);
    Serial.println(" %,    ");
                    
    delay(50); 
  
  Serial.println(" ");
  
 */
    
  delay(800); 
} 
