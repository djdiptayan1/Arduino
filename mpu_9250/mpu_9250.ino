#include<MPU9250.h>
#include<Wire.h>
MPU9250 IMU(Wire, 0x68);
void setup(){
  Serial.begin(9600);
  IMP.begin();
}
void loop(){
  IMU.readSensor();
  Serial.print("Accelerometer X axis: ");
  Serial.print(IMU.getAccelX_mss(), 3);
  Serial.print("Accelerometer y axis: ");
  Serial.print(IMU.getAccelY_mss(), 3);
  Serial.print("Accelerometer z axis: ");
  Serial.print(IMU.getAccelZ_mss(), 3);

  Serial.print("Gyroscope X axis(radian): ");
  Serial.print(IMU.getGyroX_rads(), 3);
  Serial.print("Gyroscope Y axis(radian): ");
  Serial.print(IMU.getGyroY_rads(), 3);
  Serial.print("Gyroscope Z axis(radian): ");
  Serial.print(IMU.getGyroZ_rads(), 3);
}