//Slave #4, responsible for the Camera and SD card (shield).
//The code for this particular slave remains largely unfinished.

#include <Wire.h>
#include <SD.h>
#include <Adafruit_VC0706.h>

File myFile1, myFile2, myFile3, myFile4;
int data, x;
int i = 0;

#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(4, 5);
// On Mega: camera TX connected to pin 69 (A15), camera RX to pin 3:
//SoftwareSerial cameraconnection = SoftwareSerial(69, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(4, 5);
#endif
  
Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

#define chipSelect 10

void setup() {
  Wire.begin(6); //Receives event on channel 6
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);


  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
}



void loop() {
    //To be continued
}

void receiveEvent(int howMany){
    while(Wire.available()) {
      x = Wire.read();
      data = Wire.read();
      Serial.print(x); Serial.print(" "); Serial.println(data);
    }
    
    switch (x) {
       case 1:
         //This is light
         myFile1 = SD.open("lightlog.txt", FILE_WRITE);
         myFile1.print(data); myFile1.println(" lux");
         myFile1.close();
         break;
       case 2:
         //This is temperature
         myFile2 = SD.open("templog.txt", FILE_WRITE);
         myFile2.print(data); myFile2.println(" F");
         myFile2.close();
         break;
       case 3:
         //This is humidity
         myFile3 = SD.open("humidlog.txt", FILE_WRITE);
         myFile3.print(data); myFile3.println(" lux");
         myFile3.close();
         break;
       case 4:
         getPicture();
       default:
         Serial.println("Signal Ignored");
         Serial.println("");
  }
}

void getPicture() {
  if (cam.begin()) {
  // Try to locate the camera
    Serial.println("Camera Found:");
    cam.begin();
    cam.setImageSize(VC0706_640x480);
    char filename[13];
    strcpy(filename, "IMAGExx.JPG");
      
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    i++;
    
    Serial.println("Snap in 3 secs...");
    delay(3000);

    if (! cam.takePicture()) {
        Serial.println("Failed to snap!");
        return;
    } else {
        Serial.println("Picture taken!");
    }
  
    myFile4 = SD.open(filename, FILE_WRITE);

    // Get the size of the image (frame) taken  
    uint16_t jpglen = cam.frameLength();
    Serial.print("Storing ");
    Serial.print(jpglen, DEC);
    Serial.print(" byte image.");

    int32_t time = millis();
    pinMode(8, OUTPUT);
    // Read all the data up to # bytes!
    byte wCount = 0; // For counting # of writes
    while (jpglen > 0) {
       // read 32 bytes at a time;
       uint8_t *buffer;
       uint8_t bytesToRead = min(64, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
       buffer = cam.readPicture(bytesToRead);
       myFile4.write(buffer, bytesToRead);
       if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
           Serial.print('.');
           wCount = 0;
       }
       //Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");
         jpglen -= bytesToRead;
    }
       myFile4.close();
  } else {
    Serial.println("No camera found?");
    return;
  }
}

