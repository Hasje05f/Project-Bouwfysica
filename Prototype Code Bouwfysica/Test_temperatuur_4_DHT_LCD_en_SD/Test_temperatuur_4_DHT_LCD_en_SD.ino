/*

	DHT Sensor1: pin 6: Binnen
	DHT Sensor2: pin 7: Binnenmuur/Isolatie
	DHT Sensor3: pin 8: Spouwmuur
	DHT Sensor4: pin 9: Buiten
	
	Ds18b20: pin 2
	

	Written by: Hannes Flament
		    6IW
*/


// ----------------  Include Libraries  -------------------- //


#include <OneWire.h> 
#include <DallasTemperature.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>



// ------------  Ds18b20  temperature Sensor  ------------- //


#define ONE_WIRE_BUS 2                // Data wire is plugged into pin 2 on the Arduino 
OneWire oneWire(ONE_WIRE_BUS);        // Setup a oneWire instance to communicate with any OneWire devices  
DallasTemperature sensors(&oneWire);  // Pass our oneWire reference to Dallas Temperature. 



// ------------  Dht22 temperature Sensor  --------------- //


#define DHTPIN 6        // what pin we connected the first DHT to
#define DHT2PIN 7       // what pin we connected the second DHT to
#define DHT3PIN 8       // what pin we connected the third DHT to
#define DHT4PIN 9       // what pin we connected the fourth DHT to
#define DHTTYPE DHT22   // Define type DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);     // Initialize DHT sensor for normal 16mhz Arduino
DHT dht2(DHT2PIN, DHTTYPE);   // ""
DHT dht3(DHT3PIN, DHTTYPE);   // ""
DHT dht4(DHT4PIN, DHTTYPE);   // ""



// -----------------  SD - Card  ------------------------ //


const int CHIPSELECT = 10;      // Specific for Ethernet Shield 2
const String FN = "data.log";   // Define file name



// ------------------  LCD screen   --------------------- //


 LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display



// ------------------  Constants   ---------------------- //

#define EDELAY 10      // Define avoid-error-delay  10ms
#define SDELAY 100     // Define small delay        100ms
#define WDELAY 2570    // Define waiting delay      2570ms    (3000-430)ms


// ------------------  Variables   ---------------------- //


int i = 1;
int x = 1;

float hum;    // Stores humidity value for DHT nr. 1
float temp;   // Stores temperature value for DHT nr. 1

float hum2;   // Stores humidity value for DHT nr. 2
float temp2;  // Stores temperature value for DHT nr. 2

float hum3;   // Stores humidity value for DHT nr. 3
float temp3;  // Stores temperature value for DHT nr. 3

float hum4;   // Stores humidity value for DHT nr. 4
float temp4;  // Stores temperature value for DHT nr. 4



// -----------------  Void setup (410ms)  --------------------- //

void setup() { 


 Serial.begin(9600);                  // Initialize the serial connection at 9600 bits per second.


  bool SDcard = false;                // Check presence SD-card
  
  if (!SD.begin(CHIPSELECT)) {
    Serial.println(" No SD-card found!");
   }
  else {
    Serial.println(" SD-card OK!");
    SDcard = true;
  }

  delay(SDELAY);
  
    if (SDcard) {                    // Mark new beginning on SD-card                  


      File dataFile = SD.open(FN, FILE_WRITE);
      dataFile.println(" --- New Start --- ");
      dataFile.println("            Nr.  DHT 1 (°C), DHT 2 (°C),  DHT 3 (°C),  DHT 4 (°C)");
  //    dataFile.println("                       (%),        (%),         (%),         (%)");

//    Serial.println(dataFile);
      dataFile.close();
      delay(SDELAY);     
    }



    dht.begin();                    // Initialize the DHT sensors
    dht2.begin();
    dht3.begin();
    dht4.begin();


 // if (1==1)                                                                                            // Check function DHT's                   //Idrk how to check
 //  Serial.println("Dht22 Temperature sensors ok!");
    
 /* else
    Serial.println("Failed to start Dht22!");
  */
                                                                   
    Serial.println("");                                                                         // Define logging values

    delay(SDELAY);



    sensors.begin();
    
 // if(1==1)                                                                                             // Check function Ds18b20                //Idrk how to check
 //   Serial.println("Dallas Temperature sensor ok!"); 
    
 /* else
    Serial.println("Failed to start Ds18b20!");
  */

 // Serial.println("Temp (°C)");                                                                         // Define logging value

  Serial.println("            Nr.  DHT 1 (°C),   DHT 2 (°C),    DHT 3 (°C),    DHT 4 (°C)");       // Define corresponding sensors
  //Serial.println("                          (%),          (%) ,          (%),           (%),");

    delay(SDELAY);


    lcd.init();                    // Initialize the lcd
    lcd.clear();
    lcd.backlight();

    delay(EDELAY); 
}


// -----------------  Void Loop (3000ms)  --------------------- //

void loop() { 


   delay(EDELAY);

    temp= dht.readTemperature();      // Get temperature value from DTH nr. 1
    temp2= dht2.readTemperature();    // Get temperature value from DTH nr. 2
    temp3= dht3.readTemperature();    // Get temperature value from DTH nr. 3
    temp4= dht4.readTemperature();    // Get temperature value from DTH nr. 4


    Serial.print("Temperature: ");   // Print temperature values to serial monitor

    Serial.print(i);                  // Print corresponding measurement nr.
    Serial.print("   ");

    Serial.print(temp);               // Print temperature value from DTH nr. 1
    Serial.print(",        ");
    Serial.print(temp2);              // Print temperature value from DTH nr. 2
    Serial.print(",         ");
    Serial.print(temp3);              // Print temperature value from DTH nr. 3
    Serial.print(",         ");
    Serial.print(temp4);              // Print temperature value from DTH nr. 4
 //   Serial.print(" ,   ");


    delay(EDELAY);

/*
    sensors.requestTemperatures();            // Send the command to get the Ds18b20's temperature readings
//  Serial.println("Done"); 

//  Serial.print("Ref.:, "); 
    Serial.print(sensors.getTempCByIndex(0));   // Print temperature value from Ds18b20
    Serial.print(" ,   ");
 // Why "byIndex"?  Well, you can have more than one DS18B20 on the same bus. 0 refers to the first IC on the wire.

*/
  delay(SDELAY);


    hum = dht.readHumidity();         // Get humidity value from DTH nr. 1
    hum2 = dht2.readHumidity();       // Get humidity value from DTH nr. 2
    hum3 = dht3.readHumidity();       // Get humidity value from DTH nr. 3
    hum4 = dht4.readHumidity();       // Get humidity value from DTH nr. 4
      
/* 
                
    Serial.print("Humidity:,    ");   // Print humidity values to serial monitor

    Serial.print(i);                  // Print corresponding measurement nr.
    Serial.print(",   ");

    Serial.print(hum);                // Print humidity value from DTH nr. 1
    Serial.print(" ,    ");
    Serial.print(hum2);               // Print humidity value from DTH nr. 2
    Serial.print(" ,    ");
    Serial.print(hum3);               // Print humidity value from DTH nr. 3
    Serial.print(" ,    ");
    Serial.print(hum4);               // Print humidity value from DTH nr. 4
    Serial.println(" ");               

// */

  delay(SDELAY); 
  lcd.clear();                        // Delete all information on the LCD

  switch (x) {                        // Create a switch case for the 4 sensor places

  case 1:                             // Binnen
	      lcd.setCursor(0,0);           // Print previous pieces of info on the LCD
        lcd.print("Binnen:");

	      delay(EDELAY);
        
	      lcd.setCursor(0,1);
        lcd.print(temp);
    	  lcd.print(" C, ");
    	  lcd.print(hum);
    	  lcd.print(" %,  ");

        delay(EDELAY);

    break;


  case 2:                             // Binnenmuur/Isolatie
 	      lcd.setCursor(0,0);           // Print previous pieces of info on the LCD
        lcd.print("Binnenm./Iso.:");  

	      delay(EDELAY);

	      lcd.setCursor(0,1);
        lcd.print(temp2);
    	  lcd.print(" C, ");
    	  lcd.print(hum2);
    	  lcd.print(" %,  ");

        delay(EDELAY);

    break;


  case 3:                             // Spouwmuur
	      lcd.setCursor(0,0);           // Print previous pieces of info on the LCD
        lcd.print("Spouw:");

      	delay(EDELAY);

	      lcd.setCursor(0,1);
        lcd.print(temp3);
   	    lcd.print(" C, ");
    	  lcd.print(hum3);
    	  lcd.print(" %,  ");

        delay(EDELAY);

    break;


  case 4:                             // Buiten
	      lcd.setCursor(0,0);           // Print previous pieces of info on the LCD
        lcd.print("Buiten:");

	      delay(EDELAY);

	      lcd.setCursor(0,1);
        lcd.print(temp4);
    	  lcd.print(" C, ");
    	  lcd.print(hum4);
    	  lcd.print(" %,  ");

        delay(EDELAY);

    break;

	}
 
  delay(WDELAY);                     // Waiting delay to have time to read values
	x++;                               // 1Up variable for switch case
	if(x==5)                           // Reset variable after case 4
		x=1;


    File dataFile = SD.open(FN, FILE_WRITE);    // Open dataFile on SD-card

    if (dataFile) {


        dataFile.print("Temperature: ");       // Print temperature values to SD 

        dataFile.print(i);
        dataFile.print("   ");
  
        dataFile.print(temp);
//      dataFile.print(" °C");
        dataFile.print(",  ");
        dataFile.print(temp2);
//      dataFile.print(" °C,");
        dataFile.print(",  ");  
        dataFile.print(temp3);
//      dataFile.print(" °C,");
        dataFile.print(",  ");
        dataFile.print(temp4);
//      dataFile.print(" °C,");
        dataFile.print(",  ");
//      dataFile.print(sensors.getTempCByIndex(0));
//      dataFile.print(" °C");
        dataFile.println(" ");

        delay(EDELAY);

                      
        dataFile.print("Humidity:    ");       // Print humidity values to SD 

        dataFile.print(i);
        dataFile.print("   ");

        dataFile.print(hum);
//      dataFile.print(" %");
        dataFile.print(",  ");
        dataFile.print(hum2);
//      dataFile.print(" %");
        dataFile.print(",  ");
        dataFile.print(hum3);
//      dataFile.print(" %");
        dataFile.print(",  ");
        dataFile.print(hum4);
//      dataFile.print(" %");
        dataFile.println(" ");
        dataFile.println(" ");

        delay(EDELAY);

        dataFile.close();
        
        delay(EDELAY); 


// */
        }

  i++;                          // 1up the correspond measurement nr.
  Serial.println(" ");
  delay(SDELAY);

} 
