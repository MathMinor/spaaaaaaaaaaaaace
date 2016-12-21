//Slave #4, responsible for the Camera and SD card (shield).

#include <Wire.h>
#include <SD.h>
#include <Adafruit_VC0706.h>

File myFile;
bool picture = false;
int i = 0;

SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
  
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

#define chipSelect 10

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
  
  Wire.begin(6); //Receives event on channel 6
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);


  if (!SD.begin(10)) {
    Serial.println("Card failed, or not present");
    return;
  }
}



void loop() {
  if (picture) {
    getPicture();
  }
  delay(200);
}

void receiveEvent(int howMany){
  int data, data2, data3, data4, x;
    while(Wire.available()) {
      x = Wire.read();
      data = Wire.read();
      data2 = Wire.read();
      data3 = Wire.read();
      data4 = Wire.read();
      Serial.print(x); Serial.print(" "); Serial.println(data);
    }
    
    switch (x) {
       case 1:
         //This is light
         myFile = SD.open("lightlog.txt", FILE_WRITE);
         Serial.print(F("FreeRam: "));Serial.println(FreeRam());
         if (myFile) {
          Serial.println("Writing data to SD...");
          myFile.print(data); myFile.println(" lux");
          Serial.print("Done.");
         } else {
          Serial.println("Failed to open.");
         }
         myFile.close();
         break;
       case 2:
         //This is temperature
         myFile = SD.open("templog.txt", FILE_WRITE);
         myFile.print(data); myFile.println(" F");
         myFile.close();
         Serial.print("Done.");
         break;
       case 3:
         //This is humidity
         myFile = SD.open("humidlog.txt", FILE_WRITE);
         myFile.print(data); myFile.println(" %");
         myFile.close();
         break;
       case 4:
         picture = true;
         break;
       case 5:
         myFile = SD.open("accellog.txt", FILE_WRITE);
         Serial.print(F("FreeRam: "));Serial.println(FreeRam());
         if (myFile) {
          Serial.println("Writing data to SD...");
          myFile.print("x"); myFile.print(data); myFile.print(" ");
          myFile.print("y"); myFile.print(data2); myFile.print(" ");
          myFile.print("z"); myFile.print(data3); myFile.print(" ");
          myFile.print("g"); myFile.println(data4);
          Serial.print("Done.");
         } else {
          Serial.println("Failed to open.");
         }
         myFile.close();
         break;
       default:
         Serial.println("Signal Ignored");
         Serial.println("");
  }
}

void getPicture() {
  if (cam.begin()) { // Try to locate the camera
    Serial.println("Test1");
    Serial.println("Camera Found:");
    cam.begin();
    cam.setImageSize(VC0706_640x480);
    char filename[13];
    strcpy(filename, "IMAGExx.JPG");
      
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    i++;
    Serial.println("Test2");
    
    Serial.println("Snap in 3 secs...");
    delay(3000);

    if (! cam.takePicture()) {
        Serial.println("Failed to snap!");
        Serial.println("Test3");
        return;
        Serial.println("Test4");
    } else {
        Serial.println("Picture taken!");
        Serial.println("Test5");
    }
  
    myFile = SD.open(filename, FILE_WRITE);

    // Get the size of the image (frame) taken  
    uint16_t jpglen = cam.frameLength();
    Serial.print("Storing ");
    Serial.print(jpglen, DEC);
    Serial.print(" byte image.");
    Serial.println("Test6");

    int32_t time = millis();
    pinMode(8, OUTPUT);
    Serial.println("Test7");
    // Read all the data up to # bytes!
    byte wCount = 0; // For counting # of writes
    while (jpglen > 0) {
      Serial.println("Test8");
       // read 32 bytes at a time;
       uint8_t *buffer;
       uint8_t bytesToRead = min(64, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
       buffer = cam.readPicture(bytesToRead);
       myFile.write(buffer, bytesToRead);
       if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
           Serial.print('.');
           wCount = 0;
       }
       jpglen -= bytesToRead;
       Serial.println("Test9");
    }
    myFile.close();
    picture = false;
    Serial.println("Done.");
  } else {
    Serial.println("No camera found?");
    Serial.println("Test10");
    return;
  }
}
