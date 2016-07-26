// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <Wire.h> //Lux
#include "TSL2561.h" //Lux
#include <DHT.h> //Temp/Hum

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

TSL2561 tsl(TSL2561_ADDR_FLOAT); //object for lux sensor
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
float hum=0;  //Stores humidity value
float temp=0; //Stores temperature value


void setup() {
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);            // start serial for output
    // Get light ready
    pinMode(12, OUTPUT);
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

    if (x == 1) {
       getTemp();
    } else if (x == 2) {
       getHumidity();
    } else if (x == 3) {
       getLight();
    } else {
        Serial.println("Signal Ignored");
    }
}

void getTemp() {
    Serial.println("Grabbing temperature.....");
    temp = dht.readTemperature();
    Serial.println("Temp: ");
    Serial.println(CtF(temp));
    Serial.println(" Fahrenheit ");
    Serial.println("done.");
}

void getHumidity () {
    Serial.println("Grabbing humidity.....");
    hum = dht.readHumidity();
    Serial.println(" Humidity: ");
    Serial.println(hum);
    Serial.println("% ");
    Serial.println("done.");
}

void getLight() {
    Serial.println("Grabbing light levels.....");
    
    uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);

    // Lux
    // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
    // That way you can do whatever math and comparisons you want!
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;

    Serial.println("IR: ");
    Serial.println(ir);
    Serial.println(" Full: ");
    Serial.println(full);
    Serial.println(" Visible: ");
    Serial.println(full - ir);
    Serial.println("Lux: ");
    Serial.println(tsl.calculateLux(full, ir));
    Serial.println("done.");
}

//Turn celsius to fahrenheit
double CtF (double celsius) {
    return ((celsius * 1.8) + 32);
}
