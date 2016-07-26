// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

#include <Wire.h> //Lux
#include "TSL2561.h" //Lux
#include <DHT.h> //Temp/Hum

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

TSL2561 tsl(TSL2561_ADDR_FLOAT); //object for lux sensor
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
uint16_t y; //Lux
uint32_t lum; //Lux
uint16_t ir, full; //Lux


void setup() {
    Wire.begin(8);                // join i2c bus with address #8
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

    if (x == 1) {
       getTemp();
    } else if (x == 2) {
       getHumidity();
    } else if (x == 3) {
       getLight();
    } else {
        Serial.println("Signal Ignored");
        Serial.println("");
    }
}

void getTemp() {
    Serial.println("Grabbing temperature.....");
    float temp = dht.readTemperature(true); //Stores temperature value
    float hi = dht.computeHeatIndex(temp, dht.readHumidity());  //Stores heat index value
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("˚ Fahrenheit.");
    Serial.print("Heat index: ");
    Serial.print(hi);
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
    Serial.println("Grabbing light levels.....");
    
    // Lux
    // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
    // That way you can do whatever math and comparisons you want!
    y = tsl.getLuminosity(TSL2561_VISIBLE);
    lum = tsl.getFullLuminosity();
    ir = lum >> 16;
    full = lum & 0xFFFF;

    Serial.print("IR: ");
    Serial.println(ir);
    Serial.print(" Full: ");
    Serial.println(full);
    Serial.print(" Visible: ");
    Serial.println(full - ir);
    Serial.print("Lux: ");
    Serial.println(tsl.calculateLux(full, ir));
    Serial.println("done.");
    Serial.println("");
}
