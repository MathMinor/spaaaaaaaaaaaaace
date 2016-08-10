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

//File dataFile;
float data;
byte data2 [4];
int i;

void loop() {
    //To be continued
}

void receiveEvent(int howMany){
    while(Wire.available()) {
      //data += (byte)Wire.read();
      //i = 0;
      //data2[i] = Wire.read();
      //i++;
      Serial.println(Wire.read(),HEX);
    }
    //dataFile = SD.open("testlog.txt", FILE_WRITE);
    //Serial.println(data);
}

void getPicture() {
    //To be continued
}

