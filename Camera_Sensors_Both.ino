#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h> //Lux
#include "TSL2561.h" //Lux
#include <DHT.h> //Temp/Hum
#include <SoftwareSerial.h> 


// comment out this line if using Arduino V23 or earlier
//#include <SoftwareSerial.h>         

// uncomment this line if using Arduino V23 or earlier
// #include <NewSoftSerial.h>       

// SD card chip select line varies among boards/shields:
// Adafruit SD shields and modules: pin 10
// Arduino Ethernet shield: pin 4
// Sparkfun SD shield: pin 8
// Arduino Mega w/hardware SPI: pin 53
// Teensy 2.0: pin 0
// Teensy++ 2.0: pin 20

#define chipSelect 10
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

TSL2561 tsl(TSL2561_ADDR_FLOAT); //object for lux sensor


DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//Constants
const int xPin = 0; //Analog A0 Lux
const int yPin = 1; //Analog A1 Lux
const int zPin = 2; //Analog A2 Lux

//Variables
int chk;
float hum=0;  //Stores humidity value
float temp=0; //Stores temperature value
//The minimum and maximum values that came from
//the accelerometer while standing still
int minVal = 260;
int maxVal = 360;
//Double values to keep the accelerometer values
double x=0;
double y=0;
double z=0;

// Pins for camera connection are configurable.
// With the Arduino Uno, etc., most pins can be used, except for
// those already in use for the SD card (10 through 13 plus
// chipSelect, if other than pin 10).
// With the Arduino Mega, the choices are a bit more involved:
// 1) You can still use SoftwareSerial and connect the camera to
//    a variety of pins...BUT the selection is limited.  The TX
//    pin from the camera (RX on the Arduino, and the first
//    argument to SoftwareSerial()) MUST be one of: 62, 63, 64,
//    65, 66, 67, 68, or 69.  If MEGA_SOFT_SPI is set (and using
//    a conventional Arduino SD shield), pins 50, 51, 52 and 53
//    are also available.  The RX pin from the camera (TX on
//    Arduino, second argument to SoftwareSerial()) can be any
//    pin, again excepting those used by the SD card.
// 2) You can use any of the additional three hardware UARTs on
//    the Mega board (labeled as RX1/TX1, RX2/TX2, RX3,TX3),
//    but must specifically use the two pins defined by that
//    UART; they are not configurable.  In this case, pass the
//    desired Serial object (rather than a SoftwareSerial
//    object) to the VC0706 constructor.

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(4, 5);
// On Mega: camera TX connected to pin 69 (A15), camera RX to pin 3:
//SoftwareSerial cameraconnection = SoftwareSerial(69, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(4, 5);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

// Using hardware serial on Mega: camera TX conn. to RX1,
// camera RX to TX1, no SoftwareSerial object is required:
//Adafruit_VC0706 cam = Adafruit_VC0706(&Serial1);

void setup() {

  // When using hardware SPI, the SS pin MUST be set to an
  // output (even if not connected or used).  If left as a
  // floating input w/SPI on, this can cause lockuppage.
#if !defined(SOFTWARE_SPI)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if(chipSelect != 53) pinMode(53, OUTPUT); // SS on Mega
#else
  if(chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
#endif
#endif

  Serial.begin(9600);
  // Coppied into loop
  //..
  //Serial.println("VC0706 Camera snapshot test");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }  
  
  //if (
  //cam.begin();//) {
  // Try to locate the camera
   // Serial.println("Camera Found:");
  //} else {
   // Serial.println("No camera found?");
   // return;
  //}
  // Print out the camera version information (optional)
  //char *reply = cam.getVersion();
  /*if (reply == 0) {
    Serial.print("Failed to get version");
  } else {
    Serial.println("-----------------");
    Serial.print(reply);
    Serial.println("-----------------");
  }
*/
  // Set the picture size - you can choose one of 640x480, 320x240 or 160x120 
  // Remember that bigger pictures take longer to transmit!
  
  //cam.setImageSize(VC0706_640x480);        // biggest
  //cam.setImageSize(VC0706_320x240);        // medium
  //cam.setImageSize(VC0706_160x120);          // small

  // You can read the size back from the camera (optional, but maybe useful?)
  /*uint8_t imgsize = cam.getImageSize();
  Serial.print("Image size: ");
  if (imgsize == VC0706_640x480) Serial.println("640x480");
  if (imgsize == VC0706_320x240) Serial.println("320x240");
  if (imgsize == VC0706_160x120) Serial.println("160x120");
  */
  //Serial.println("Snap in 3 secs...");
  //...
  
  //for (int i = 0; i < 5; i++) {
              
//}
 Serial.println("Please select as follows:");
 Serial.println(" -a- for camera");
 Serial.println(" -b- for sensors");
}
int i=0;
File imgFile;
File dataFile;


void loop() {
     
    if (Serial.available() > 0) {
     
       int inByte = Serial.read();
    switch (inByte) {
       case 'a':
         //digitalWrite(2, HIGH);
         //Serial.println("It was A!");
         camera();
         break;
       case 'b':
         //digitalWrite(3, HIGH);
         //Serial.println("It was B!");
         sensors();
         break;
       case 'c':
         //digitalWrite(4, HIGH);
         Serial.println("It was C!");
         break;
       case 'd':
         //digitalWrite(5, HIGH);
         Serial.println("It was D!");
         break;
       case 'e':
         //digitalWrite(6, HIGH);
         Serial.println("It was E!");
         break;
       default:
          Serial.println("It was incorrect!");
  }
}           

  
     delay(1000);
}

//Change celsius to Fahrenheit
double CtF (double celsius) {
  return ((celsius * 1.8) + 32);
}

void camera(){
              cam.begin();
              cam.setImageSize(VC0706_640x480);
              char filename[13];
              strcpy(filename, "IMAGExx.JPG");
              //for(int i = 0; i<5 ; i++)
              //{
                filename[5] = '0' + i/10;
                filename[6] = '0' + i%10;
                //if(!SD.exist(filename)){
                //  break;
                //}
              
              //}
              Serial.println("Snap...");
              cam.takePicture();//) 
              imgFile = SD.open(filename, FILE_WRITE);
              Serial.println(F("Taking photo..."));
              uint16_t jpglen = cam.frameLength();
              int32_t time = millis();
              pinMode(8, OUTPUT);
              byte wCount = 0; // For counting # of writes
              while (jpglen > 0) {
                     uint8_t *buffer;
                     uint8_t bytesToRead = min(64, jpglen); 
                     buffer = cam.readPicture(bytesToRead);
                     imgFile.write(buffer, bytesToRead);
                     if(++wCount >= 64) { 
                          Serial.print('--------->');
                          wCount = 0;
                     }
                     jpglen -= bytesToRead;
            }
            imgFile.close();
            
            time = millis() - time;
            Serial.println("done!");
            Serial.print(time); 
            Serial.println(" ms elapsed");  
    
  
}

void sensors(){
   // Sensor data:
    
    dataFile = SD.open("loggerData.txt", FILE_WRITE);
// Lux
    // Simple data read example. Just read the infrared, fullspecrtrum diode 
    // or 'visible' (difference between the two) channels.
    // This can take 13-402 milliseconds! Uncomment whichever of the following you want to read
    uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);     
    //uint16_t x = tsl.getLuminosity(TSL2561_FULLSPECTRUM);
    //uint16_t x = tsl.getLuminosity(TSL2561_INFRARED);
  
    //(Temp/Hum) Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    
    //(Accelerometer) Grab the values from the accelerometer and store
    int xRead = analogRead(xPin);
    int yRead = analogRead(yPin);
    int zRead = analogRead(zPin);
    //(Accelerometer) Convert the read values into degrees
    int xAng = map(xRead, minVal, maxVal, -90, 90);
    int yAng = map(yRead, minVal, maxVal, -90, 90);
    int zAng = map(zRead, minVal, maxVal, -90, 90);
    //(Accelerometer) Convert from radians to degrees
    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

    // Lux
    // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
    // That way you can do whatever math and comparisons you want!
    uint32_t lum = tsl.getFullLuminosity();
    uint16_t ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;
   
    dataFile.print("IR: ");
    dataFile.print(ir);
    dataFile.print(" Full: ");
    dataFile.print(full);
    dataFile.print(" Visible: ");
    dataFile.println(full - ir);
    dataFile.print("Lux: ");
    dataFile.print(tsl.calculateLux(full, ir));
    dataFile.print(" Humidity: ");
    dataFile.print(hum);
    dataFile.print("% ");
    dataFile.print("Temp: ");
    dataFile.print(CtF(temp));
    dataFile.println(" Fahrenheit ");
    dataFile.print("Angular Movement    ");
    dataFile.print(" x: ");
    dataFile.print(x);
    dataFile.print(" y: ");
    dataFile.print(y);
    dataFile.print(" z: ");
    dataFile.print(z);
    dataFile.println();
    dataFile.println();
    dataFile.println();

    
    dataFile.close(); 

}

