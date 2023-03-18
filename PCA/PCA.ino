//motor 1
#define ena 1
#define inp1a 2
#define inp1b 0

//motor 2
#define ena2 4
#define inp2a 5
#define inp2b 6

//motor 3
#define ena3 8
#define inp3a 9
#define inp3b 10

/* Include the HCPCA9685 library */
#include "HCPCA9685.h"
/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2CAdd 0x40
/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);
 
void setup()
{
  /* Initialize the library*/
  HCPCA9685.Init();
  /* Wake the device up */
  HCPCA9685.Sleep(false);
 
  pinMode(ena,OUTPUT);
  pinMode(inp1a,OUTPUT);
  pinMode(inp1b,OUTPUT);
  pinMode(ena2,OUTPUT);
  pinMode(inp2a,OUTPUT);
  pinMode(inp2b,OUTPUT);
  pinMode(ena3,OUTPUT);
  pinMode(inp3a,OUTPUT);
  pinMode(inp3b,OUTPUT);
}
 
 
void loop()
{
  HCPCA9685.SetPeriodFreq(100);
 
  //setting input pins of motors 1,2,3,4 as high and low
  HCPCA9685.Output(inp1a,0, 4095);//high
  HCPCA9685.Output(inp1b,0, 0);//low
  HCPCA9685.Output(inp2a,0, 4095);//high
  HCPCA9685.Output(inp2b,0, 0);//low
  HCPCA9685.Output(inp3a,0, 4095);//high
  HCPCA9685.Output(inp3b,0, 0);//low
 
//setting motor speed (PWM range:0-4095)
  HCPCA9685.Output(ena,0, 1000);//25% speed
  HCPCA9685.Output(ena2,0, 1000);//25% speed
  HCPCA9685.Output(ena3,0, 1000);//25% speed
  delay(10000);
 
  //pause
  HCPCA9685.Output(inp1a,0, 0);//low
  HCPCA9685.Output(inp1b,0, 0);//low
  HCPCA9685.Output(ena,0, 0);//0% speed
  HCPCA9685.Output(inp2a,0, 0);//low
  HCPCA9685.Output(inp2b,0, 0);//low
  HCPCA9685.Output(ena2,0, 0);//0% speed
  HCPCA9685.Output(inp3a,0, 0);//low
  HCPCA9685.Output(inp3b,0, 0);//low
  HCPCA9685.Output(ena3,0, 0);//0% speed
  delay(3000);
 
  //changing direction of motor movement
  HCPCA9685.Output(inp1a,0, 0);//low
  HCPCA9685.Output(inp1b,0, 4095);//high
  HCPCA9685.Output(inp2a,0, 0);//low
  HCPCA9685.Output(inp2b,0, 4095);//high
  HCPCA9685.Output(inp3a,0, 0);//low
  HCPCA9685.Output(inp3b,0, 4095);//high
 
//setting motor speed (PWM range:0-4095)
  HCPCA9685.Output(ena,0, 1000);//25% speed
  HCPCA9685.Output(ena2,0, 1000);//25% speed
  HCPCA9685.Output(ena3,0, 1000);//25% speed
  delay(10000);
 
//pause
  HCPCA9685.Output(inp1a,0, 0);//low
  HCPCA9685.Output(inp1b,0, 0);//low
  HCPCA9685.Output(ena,0, 0);//0 speed
  HCPCA9685.Output(inp2a,0, 0);//low
  HCPCA9685.Output(inp2b,0, 0);//low
  HCPCA9685.Output(ena2,0, 0);//0 speed
  HCPCA9685.Output(inp3a,0, 0);//low
  HCPCA9685.Output(inp3b,0, 0);//low
  HCPCA9685.Output(ena3,0, 0);//0 speed
  delay(3000);
}
