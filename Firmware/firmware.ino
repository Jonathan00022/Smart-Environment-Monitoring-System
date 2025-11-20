
/*
THIS FIRMWARE FOR SMART ENVIRONMENT MONITORING SYSTEM (SEMS_NODE)

VERSION:0.1 CONCEPTS_NODE PROTOTYPE
AURTHOR:MUHIRE JONATHAN

THIS CODE IS DESIGNED TO DEMONSRATE HOW THE FIRMWARE OF REAL SEMS_NODE

_WE USE THE DFRobot_AirQualitySensor IN THIS DEMO 
_WE USE  DHT11 IN THIS DEMO 
_WE USE MQ-9 IN THIS DEMO
_WE USE ARDUINO_UNO IN THIS DEMO

IF YOU DON'T HAVE THEIR LIBRARIES INSTALL THEM

source:https://github.com/Jonathan00022/Smart-Environment-Monitoring-System

*/
#include <DFRobot_AirQualitySensor.h>
#include <Bonezegei_DHT11.h>

#define DHT_DATA_PIN 12
#define I2C_ADDRESS 0X19
#define CO2_DATA_PIN  A0


Bonezegei_DHT11 dht11(DHT_DATA_PIN);
DFRobot_AirQualitySensor PmSensor(&Wire, I2C_ADDRESS);

void setup()
{
  Serial.begin(9600);

  //initialize the sensors
  
  dht11.begin();

  while(!PmSensor.begin())
  {
    Serial.println(F("Sensor not detected. Check wiring / I2C address."));
    delay(1000);
   

  }
  /*Serial.println("PM Sensor begin successfully");

   uint8_t version = PmSensor.gainVersion();
   Serial.println(F("Firmware Version: "));
   Serial.println(version);
  */
  delay(500);

 
}
void loop()
{
 
  //Serial.println(F("--------------MEASUREMENT CYCLES------------"));
  

 //you can measure both standard and atmosphere particleConcentration but in this demo we are using particle number per every 0.1L
  uint16_t PM2_5_std = PmSensor.gainParticleConcentration_ugm3(PARTICLE_PM2_5_STANDARD);
  uint16_t PM2_5_atm = PmSensor.gainParticleConcentration_ugm3(PARTICLE_PM2_5_ATMOSPHERE);
  uint16_t Cnt2_5    = PmSensor.gainParticleNum_Every0_1L(PARTICLENUM_2_5_UM_EVERY0_1L_AIR);

// Map the Cnt2_5 values to the scale of 1000 max 
// use the min & max value that is in your simulation results when you adjusting the DFRobot_Air_Quality sensor 

uint16_t Cnt2_5_mapped_value = map(Cnt2_5,4982,9870,0,1000);


  float CO2_level = analogRead(CO2_DATA_PIN);

// Map the CO2_level so it will match with scale of 5000 ppm
uint16_t CO2_level_mapped_value = map(CO2_level,0,1023,0,5000);

  uint8_t Humidity_values = 0;
  float Temperature_values = 0.0;

  if(dht11.getData());
  {
     Humidity_values = dht11.getHumidity();
     Temperature_values = dht11.getTemperature();

  }

  /* This is for debugging purpose  in proteus serial monitor 
  Serial.println(F("Mass Concentration  ug\m3 :"));

  Serial.print("--------Standard-------");
  Serial.print("PM2_5: "); Serial.println(PM2_5_std);

  Serial.println("------Atmospheric--------");
  Serial.print("PM2_5: "); Serial.println(PM2_5_atm);

  Serial.println(F("---------Particle Count Per 0.1L-----------------"));
  Serial.print(F("Particle concentration: ")); Serial.println(Cnt2_5);

  Serial.println("-----------TEMPERATURE & HUMIDITY VALUES------------");

  Serial.print("Temp: "); Serial.println(Temperature_values);
  Serial.print("Hum: "); Serial.println(Humidity_values);
  Serial.println("------------CO2 LEVEL--------------");
  Serial.print("CO2_Level: "); Serial.println(CO2_level);

  Serial.println("---------------------------------------------------------------------------------------");
  */

  //Parse data in serial as json as we are going to use in bridge script 
  //We are going to use easy and not standard way to parse json objects

  
  
  Serial.print("{\"hum\": ");
  Serial.print(Humidity_values);
  Serial.print(",\"temp\": ");
  Serial.print(Temperature_values);
  Serial.print(",\"CO2_level\": ");
  Serial.print(CO2_level_mapped_value);
  Serial.print(",\"PM2_5_Concentration\": ");
  Serial.print(Cnt2_5_mapped_value);
  Serial.println("}");


 // wait 2 seconds before you take other measurements

  delay(2000);

 
}
