// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

//#include <Wire.h> //Lux
//#include "TSL2561.h" //Lux
#include <DHT.h> //Temp/Hum
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

//Can be LOW, FLOAT or HIGH for different addresses
//FLOAT default
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
//TSL2561 tsl(TSL2561_ADDR_FLOAT); //object for lux sensor
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
void setup() {
    Wire.begin(10);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);            // start serial for output
    // Get light ready
    //pinMode(12, OUTPUT);
}

void loop() {
    delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    while (1 < Wire.available()) { // loop through all but the last
        char c = Wire.read();       // receive byte as a character
        Serial.print(c);            // print the character
    }
    int x = Wire.read();           // receive byte as an integer
    Serial.println(x);             // print the integer
    Serial.println("");

    switch (x) {
       case 3:
         getTemp();
         break;
       case 2:
         getHumidity();
         break;
       case 1:
         getLight();
         break;
       default:
          Serial.println("Signal Ignored");
          Serial.println("");
  }
}

void getTemp() {
    Serial.println("Grabbing temperature.....");
    Serial.print("Temperature: ");
    Serial.print(dht.readTemperature(true));
    Serial.println("˚ Fahrenheit.");
    Serial.print("Heat index: ");
    Serial.print(dht.computeHeatIndex(dht.readTemperature(true), dht.readHumidity()));
    Serial.println(" *C.");
    Serial.println("done.");
    Serial.println("");
}

void getHumidity () {
    Serial.println("Grabbing humidity.....");
    float hum = dht.readHumidity();
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("% ");
    Serial.println("done.");
    Serial.println("");
}

void getLight() {
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
  
  if(!tsl.begin()) {
    Serial.println("Sensor not found!");  
  } else {
    tsl.enableAutoRange(true);
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
    sensors_event_t event;
    tsl.getEvent(&event);
 
    /* Display the results (light is measured in lux) */
    if (event.light) {
      Serial.print(event.light); Serial.println(" lux");
    } else {
      /* If event.light = 0 lux the sensor is probably saturated
      and no reliable data could be generated! */
      Serial.println("Sensor overloaded or saturated!");
    }
  }
  Serial.println("");
}
