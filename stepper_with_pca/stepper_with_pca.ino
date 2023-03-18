#include "HCPCA9685.h"
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);
#define inp1a 1
#define inp1b 0

// #define dir 2
// #define step 3
void setup(){
  HCPCA9685.Init();
  HCPCA9685.Sleep(false);
  // pinMode(dir,OUTPUT);
  // pinMode(step, OUTPUT);

  pinMode(inp1a, OUTPUT);
  pinMode(inp1b, OUTPUT);
}
void loop(){
  digitalWrite(inp1b, 255);
  for(int i=0;i<400;i++){
    HCPCA9685.Output(inp1a,0, 4095);//high
    delayMicroseconds(500);
    HCPCA9685.Output(inp1a,0, 0);//low
    delayMicroseconds(500);
  }
  delay(1000);

  digitalWrite(inp1b, 0);
  for(int i=0;i<400;i++){
    HCPCA9685.Output(inp1a,0, 4095);//high
    delayMicroseconds(500);
    HCPCA9685.Output(inp1a,0, 0);//low
    delayMicroseconds(500);
  }
  delay(1000);
}
