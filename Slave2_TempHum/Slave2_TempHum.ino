//Slave #2, responsible for the Temp/Humidity and Light sensors.

#include <DHT.h> //Temp/Hum
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

//Can be LOW, FLOAT or HIGH for different addresses
//FLOAT default
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino



//Variables
void setup() {
    Wire.begin(10);                // join i2c bus with address #
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);            // start serial for output
    // Get light ready
    //pinMode(12, OUTPUT);  
} 

char out[5];

void loop() {
    delay(200);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    /*while (1 < Wire.available()) { // loop through all but the last
        char c = Wire.read();       // receive byte as a character
        Serial.print(c);            // print the character
    }
    Serial.flush();*/
    int x = Wire.read();           // receive byte as an integer
    Serial.println(x);   // print the integer
    Serial.println("");

    switch (x) {
       case 2:
         getTemp();
         break;
       case 3:
         getHumidity();
         break;
       case 1:
         getLight();
         break;
       default:
         Serial.println("Signal Ignored");
         Serial.println("");
  }
  Wire.flush();
}

void getTemp() {
    Serial.flush();
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

    Serial.flush();
    Serial.println("Grabbing humidity.....");
    Serial.print("Humidity: ");
    Serial.print(dht.readHumidity()); Serial.println("% ");
    Wire.beginTransmission(6);
    Wire.write(dtostrf(dht.readHumidity(),5,2,out));
    Wire.endTransmission();
    Serial.println("done.");
    Serial.println("");
}

void getLight() {
  /* Get a new sensor event */ 
  Serial.println("Grabbing light level.....");
  dht.readTemperature(true);
  if(!tsl.begin()) {
      /* There was a problem detecting the ADXL345 ... check your connections */
      Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
      while(1);
  } else {
    configureSensor();
  }
  sensors_event_t event;
  tsl.getEvent(&event);
 
  /* Display the results (light is measured in lux) */
  if (event.light) {
    Serial.print(event.light); Serial.println(" lux");
  } else {
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  Serial.println("done.");
  Serial.println("");
}

void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
}

