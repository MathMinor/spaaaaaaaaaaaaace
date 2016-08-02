// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

#include <Wire.h>

//Variables
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)
float x, y, z, g;
//float avg_x=0; Never used
//float avg_y=0; Never used
//float avg_z=0; Never used


void setup() {
    Wire.begin(4);                // join i2c bus with address #8
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);            // start serial for output
    pinMode(groundpin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    digitalWrite(groundpin, LOW);
    digitalWrite(powerpin, HIGH);
    // Get light ready
    //pinMode(12, OUTPUT);
}

void loop() {
    delay(200);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  getAccel();
  Wire.flush();
}

void getAccel() {
  // print the sensor values:
  Serial.print("X: ");
  x=analogRead(xpin);
  Serial.print(x);
  // print a tab between values:
  Serial.print("\t");
  Serial.print("Y: ");
  y=analogRead(ypin);
  Serial.print(y);
  // print a tab between values:
  Serial.print("\t");
  Serial.print("Z: ");
  z=analogRead(zpin);
  Serial.print(z);
  g = sqrt((x * x) + (y * y) + (z * z));
  Serial.print("\t");
  Serial.print("G-Force: ");
  Serial.print(g);
  Serial.println();
}

/*
void print_rot_ADXL()
{
  float xAxis = VtoG(avg_x);
  float yAxis = VtoG(avg_y);
  float zAxis = VtoG(avg_z);

  float pitch = atan(xAxis/sqrt(pow(yAxis, 2)+pow(zAxis, 2)));
  float roll = atan(yAxis/sqrt(pow(xAxis, 2)+pow(zAxis, 2)));

  // convert radians into degrees
  pitch = pitch * (180.0/PI);
  roll = roll * (180.0/PI);

  Serial.print("\nPitch: "); Serial.print(pitch);
  Serial.print("\tRoll: "); Serial.println(roll);
  }

  void readADXL()
  {
    analogRead(ADXL_X_PIN);
    delay(MUXREADDELAY);
    x_read = analogRead(ADXL_X_PIN);
    analogRead(MUXREADDELAY);
    delay(MUXREADDELAY);
    y_read = analogRead(ADXL_Y_PIN);
    analogRead(ADXL_Z_PIN);
    delay(MUXREADDELAY);
    z_read = analogRead(ADXL_Z_PIN);
  }
  #ifdef ADXL_PRINTMODE_AVG
      avg_x += x_read;
      avg_y += y_read;
      avg_z += z_read;

      ++count;
#endif   
*/
