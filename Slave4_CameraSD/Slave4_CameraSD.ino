//Slave #4, responsible for the Camera and SD card (shield).
//The code for this particular slave remains largely unfinished.

#include <Wire.h>
#include <SD.h>

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

File dataFile;
String data = "";

void loop() {
    //To be continued
}

void receiveEvent(int howMany){
    data = "";
    while(Wire.available()) {
      data += (char)Wire.read();
    }
    dataFile = SD.open("testlog.txt", FILE_WRITE);
    dataFile.print(data);
}

void getPicture() {
    //To be continued
}

