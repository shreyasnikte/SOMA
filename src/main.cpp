/*
AUTHOR: Shreyas Nikte
PROJECT: Project SOMA
*/


#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


// ESP32WROOM32 pin assignment
#define DHTPIN 4      // Digital pin connected to the DHT sensor
#define MOIST_PIN 36  // Digital pin connected to the Moisture sensor
#define LED_BuiltIn 2 // Digital pin connected to the on-board LED pin. To be used for troubleshooting.
#define Code_DEBUG 0  // Normal operation: Code_DEBUG=0, DEBUG operation: Code_DEBUG=1


// MOISTURE SENSOR: Define setpoints for moisture sensor. Please calibrate your new sensor before use. They are notoriously different from each other.
#define DRY_SOIL_THRESHOLD 3500 // Threshold for RAW analog input value (WET_SOIL_THRESHOLD < DRY_SOIL_THRESHOLD < Air[value:4095])
#define WET_SOIL_THRESHOLD 2100 // Threshold for RAW analog input value (saltwater[value:1200]< DRY_SOIL_THRESHOLD < WET_SOIL_THRESHOLD)
#define WATER_LOW_TRIGG 20   //  Trigger value for watering action
#define WATER_LOWLOW_TRIGG 10   //  Trigger value for watering action


// DHT SENSOR:  Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)



/******************************* */

// put function declarations here:
int Get_Rel_Moisture();   // read raw value and return percentage moisture of the soil

DHT_Unified dht(DHTPIN, DHTTYPE);
/******************************* */


void setup() {
  // put your setup code here, to run once:
  // pinMode(LED_BuiltIn, OUTPUT);
  Serial.begin(115200);
  dht.begin();

}

/******************************* */


void loop() {
  delay(2000);
  int Rel_SoilMoisture = Get_Rel_Moisture();    //Rel_Moisture is a 0-100 (%) scaled value of the soil moisture.

  if (Rel_SoilMoisture < WATER_LOW_TRIGG && Rel_SoilMoisture > WATER_LOWLOW_TRIGG ){
    bool WATER_LOW = true;
    bool WATER_LOWLOW = false;

    Serial.println("Warning: Low soil moisture detected");
  }

  else if (Rel_SoilMoisture < WATER_LOWLOW_TRIGG)
  {
    bool WATER_LOW = false;
    bool WATER_LOWLOW = true;
    Serial.println("ALERT: Very low soil moisture detected");
  }
  

  else{
    bool WATER_LOW = false;
    bool WATER_LOWLOW = false;
    Serial.println("Information: Moisture level is ok");
  }

}


/******************************* */


// put function definitions here:

int Get_Rel_Moisture(){

  // Read the analog input value from moisture sensor 
  float sensorValue = analogRead(MOIST_PIN);

  if (Code_DEBUG == 1) {
    Serial.print("DEBUG: Moisture sensor raw value: ");
    Serial.println(sensorValue);
  } // Serial monitor

  // Map the raw input into a 0-100 scale
  int scaled_SoilMoisture = static_cast<int>(((sensorValue - DRY_SOIL_THRESHOLD)/(WET_SOIL_THRESHOLD - DRY_SOIL_THRESHOLD))*100);
  
  // Limit the scaled value between 0 & 100
  int Rel_SoilMoisture = (scaled_SoilMoisture > 100) ? 100 : (scaled_SoilMoisture < 0) ? 0 : scaled_SoilMoisture;
  // Rel_SoilMoisture = (scaled_SoilMoisture < 0) ? 0 : scaled_SoilMoisture;

  Serial.print("Relative Soil Moisture: ");   // Serial monitor
  Serial.print(Rel_SoilMoisture);             // Serial monitor
  Serial.print("%. ");                          // Serial monitor

  // return th relative soil moisture value to the loop() function

  return Rel_SoilMoisture;
}


