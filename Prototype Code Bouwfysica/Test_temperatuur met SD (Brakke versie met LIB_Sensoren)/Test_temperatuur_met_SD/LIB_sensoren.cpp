#include "LIB_sensoren.h"

//
//
// CLASS humidity and temperature sensor
//

TemperatureSensor::TemperatureSensor(long minValTemp, long maxValTemp, long minValHum, long maxValHum) {

  this->dht = new DHT(DHT22_PIN, DHT22);
  this->minValTemp = minValTemp;
  this->maxValTemp = maxValTemp;
  this->minValHum = minValHum;
  this->maxValHum = maxValHum;
};

TemperatureSensor::~TemperatureSensor() {
  delete this->dht;
  this->dht = NULL;
};

bool TemperatureSensor::Start() {

  this->dht->begin();
  return true;
};

bool TemperatureSensor::Read() {
  this->valTemp = round(this->dht->readTemperature());
  this->valHum = round(this->dht->readHumidity());
  return true;
};


void TemperatureSensor::PrintSerial() {
  Serial.print(String(this->GetValTemp()) + ", " + String(this->GetValHum()));
};

long TemperatureSensor::GetValTemp() {
  return this->valTemp;
};

long TemperatureSensor::GetValHum() {
  return this->valHum;
};

SensorStatusType TemperatureSensor::GetStatusTemp() {

  if (this->valTemp < this->minValTemp) return TOO_LOW;
  if (this->valTemp > this->maxValTemp) return TOO_HIGH;
  return OK;
};

SensorStatusType TemperatureSensor::GetStatusHum() {

  if (this->valHum < this->minValHum) return TOO_LOW;
  if (this->valHum > this->maxValHum) return TOO_HIGH;
  return OK;
};
