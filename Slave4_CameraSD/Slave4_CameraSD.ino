#include <Wire.h>
#include <SD.h>

#define chipSelect 10

void setup() {
  // put your setup code here, to run once:
  Wire.begin(6);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
}

File dataFile;
String data = "";

void loop() {
  // put your main code here, to run repeatedly:

}

void receiveEvent(int howMany){
    data = "";
    while(Wire.available()) {
      data += (char)Wire.read();
    }
    dataFile = SD.open("testlog.txt", FILE_WRITE);
    dataFile.print(data);

    /*switch (x) {
       case '1':
         dataFile = SD.open("lightlog.txt", FILE_WRITE);
         dataFile.print(whateverreceived); Serial.println(" lux");
         break;
         
       case '2':
         dataFile = SD.open("templog.txt", FILE_WRITE);
         dataFile.print(whateverreceived); Serial.println("˚ Fahrenheit.");
         break;
         
       case '3':
         data = "";
         dataFile = SD.open("humidlog.txt", FILE_WRITE);
         dataFile.print(whateverreceived); Serial.println(" %");
         break;

       case '4':
         dataFile = SD.open("accellog.txt", FILE_WRITE);
         dataFile.print(whateverreceived); Serial.println(" lux");
         break;
         
       default:
         Serial.println("Signal Ignored");
         Serial.println("");
  }
  Wire.flush();*/
}

void getPicture() {
  
}

