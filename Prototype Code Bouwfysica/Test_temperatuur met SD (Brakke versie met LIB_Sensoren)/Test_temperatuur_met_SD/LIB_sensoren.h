/*  Library voor het werken met DHT sensor
 *   
 *  Aansluitingen:
 *  
 *  Temperatuur/vochtigheidssensor DHT22
 *  
 *  DHT22     Arduino UNO
 *  
 *  AZ1       GND
 *  AZ2       -
 *  AZ3       D6
 *  AZ4       3.3V
 *  (AZ = achterzijde, van links naar rechts)
 */


// status values
typedef enum {TOO_LOW, TOO_HIGH, OK} SensorStatusType;

//

//
// CLASS humidity and temperature sensor
//

#include <DHT.h>
#include <DHT_U.h>
#define DHT22_PIN 6

class TemperatureSensor {

  private:

    DHT *dht = NULL;

    long valTemp = 0;
    long valHum = 0;

    long minValTemp = 0;
    long maxValTemp = 0;
    long minValHum = 0;
    long maxValHum = 0;

  public:

    TemperatureSensor(long minValTemp, long maxValTemp, long minValHum, long maxValHum);
    ~TemperatureSensor();

    bool Start();
    bool Read();
    void PrintSerial();
    long GetValTemp();
    long GetValHum();
    SensorStatusType GetStatusTemp();
    SensorStatusType GetStatusHum();
};
