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

File myFile1, myFile2, myFile3;
int data, x;

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
    //To be continued
}

