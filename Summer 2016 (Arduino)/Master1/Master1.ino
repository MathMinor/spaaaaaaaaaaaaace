//Master, responsible for sending commands and the Tranceiver.

#include <Wire.h> //Lux

void setup() {
 pinMode(10, OUTPUT); 
 Serial.begin(9600);
  
 Serial.println("Please select as follows:");
 Serial.println("1 for Light");
 Serial.println("2 for Temperature");
 Serial.println("3 for Humidity");
 Serial.println("4 for Camera");
 Serial.println("5 for Accelerometer");
 Wire.begin(); // join i2c bus (address optional for master)
}

void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    
    switch (inByte) {
       case '1':  
         Serial.println("Processing light sensor..."); 
         Wire.beginTransmission(10); // transmit to device #8
         //Wire.write("Sensor pick up");        // sends five bytes
         Wire.write(1);              // sends one byte
         Wire.endTransmission(); // stop transmitting
         //Wire.flush();
         break;
         
       case '2':
         Serial.println("Processing temperature sensor...");
         Wire.beginTransmission(10); //ransmit to device #8
         //Wire.write("Sensor pick up");        // sends five bytes
         Wire.write(2);              // sends one byte
         Wire.endTransmission();    // stop transmitting
         Wire.flush();
         break;
         
       case '3':
         Serial.println("Processing humidity sensor...");
         //digitalWrite(3, HIGH);
         //Serial.println("It was B!");
         //sensors();
         Wire.beginTransmission(10); // transmit to device #8
         //Wire.write("Sensor pick up");        // sends five bytes
         Wire.write(3);              // sends one byte
         Wire.endTransmission();    // stop transmitting
         Wire.flush();
         break;
         
      case '4':
         Serial.println("Processing camera...");
         //digitalWrite(3, HIGH);
         //Serial.println("It was B!");
         //sensors();
         Wire.beginTransmission(3); // transmit to device #8
         //Wire.write("Sensor pick up");        // sends five bytes
         Wire.write(1);              // sends one byte
         Wire.endTransmission();    // stop transmitting
         Wire.flush();
         break;
         
      case '5':
         Serial.println("Processing accelerometer...");
         //digitalWrite(3, HIGH);
         //Serial.println("It was B!");
         //sensors();
         Wire.beginTransmission(4); // transmit to device #8
         //Wire.write("Sensor pick up");        // sends five bytes
         Wire.write(1);              // sends one byte
         Wire.endTransmission();    // stop transmitting
         Wire.flush();
         
         break;
         
       default:
         Serial.println("Incorrect input - try again!");
  }
}
 
  delay(2000);
}
