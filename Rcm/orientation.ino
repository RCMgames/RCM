#include <MPU9250_asukiaaa.h> //get it from the library manager
#define SDA_PIN port2Pin
#define SCL_PIN port1Pin
MPU9250_asukiaaa mySensor;
float gZ, mX, mY;
float headingVal = 0;
unsigned long lastOrientationCalc = 0;
void orientationSetup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
}
void orientationReadRawData() {
  mySensor.accelUpdate();
  mySensor.gyroUpdate();
  mySensor.magUpdate();
  //  aX = mySensor.accelX();
  //  aY = mySensor.accelY();
  //  aZ = mySensor.accelZ();
  //  gX = mySensor.gyroX();
  //  gY = mySensor.gyroY();
  gZ = mySensor.gyroZ();
  mX = mySensor.magX();
  mY = mySensor.magY();
  //  mZ = mySensor.magZ();
  //  mDirection = mySensor.magHorizDirection();
  
  //  magHeading = atan2(mY - (maxmY + minmY) / 2, mX - (maxmX + minmX) / 2);

  headingVal += (micros() - lastOrientationCalc) * (gZ * 2000.0f / 32767.5f * TWO_PI / 180) / 100000 / 3.8 * PI;
  lastOrientationCalc = micros();
}
float orientationReadHeading() {
  return headingVal;
}
