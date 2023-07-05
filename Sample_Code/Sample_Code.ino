/*

  Download the "Bluetooth Controller App" from Google Play store. Please click on link.
https://play.google.com/store/apps/details?id=in.robu.bluetoothcontroller

        
      
Set Key-word in "Bluetooth Controller App" as follows

        1=NW      2=FORWARD     3=NE
        4=CW      5=STOP        6=CCW
        7=SW      8=BACKWARD    9=SE


In our code we use ASCII Code to Detect which key has been pressed.

        Hex     Char
        30       0
        31       1
        32       2
        33       3
        34       4
        35       5
        36       6
        37       7
        38       8
        39       9
  
 */


#include <SoftwareSerial.h>                      // include software serial
#include <AFMotor.h>                             // Install Motor driver sheild library        

AF_DCMotor motor1(1);                            // define motor on channel 1,2& 4 with 1KHz default PWM
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);


const byte rxPin = A0;                           // define Software serial pin 
const byte txPin = A1;

                                                // set up a new serial object
SoftwareSerial mySerial (rxPin, txPin);
/*

Valid values for cmd are:

    FORWARD - run forward (actual direction of rotation will depend on motor wiring)
    BACKWARD - run backwards (rotation will be in the opposite direction from FORWARD)
    RELEASE - Stop the motor.  This removes power from the motor and is equivalent to setSpeed(0).
    The motor shield does not implement dynamic breaking, so the motor may take some time to spin down
*/
int state = 0;
void setup() 
{   
  // 
  
  mySerial.begin(9600);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  //Set initial speed of the motor & stop
  motor1.setSpeed(255);                                 // Set motor 1 to maximum speed
  motor1.run(RELEASE);
  motor2.setSpeed(255);                                 // Set motor 2 to maximum speed
  motor2.run(RELEASE);
  motor3.setSpeed(255);                                 // Set motor 4 to maximum speed
  motor3.run(RELEASE);
Serial.println("EasyMech's POLY");
}


  
void loop()
{
  uint8_t i,s=255;
  
  if(mySerial.available() > 0)                   // Checks whether data is comming from the serial port
  { 
   
    state =mySerial.read();                      // Reads the data from the serial port
    //state =Serial.println(Serial.read());      // Reads the data from the serial port
    delay(10);

    if(state==0x31)                              
    {                                     
      Serial.println("NW");                       // Motor run towards North-West direction
      motor1.run(FORWARD);
      motor3.run(FORWARD);
      motor2.run(RELEASE);    
      motor1.setSpeed(s);
      motor3.setSpeed(s);      
    }

    
    else if(state==0x32)
    {
      Serial.println("FORWARD");                      // Motor run towards forward direction
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(RELEASE);    
      motor1.setSpeed(s);
      motor2.setSpeed(s);              
    }

    
    else if(state==0x33)
    {
      Serial.println("NE");                           // Motor run towards North-East direction 
      motor1.run(RELEASE);     
      motor2.run(FORWARD);
      motor3.run(BACKWARD);
      motor2.setSpeed(s); 
      motor3.setSpeed(s);        
    }

    
    else if(state==0x34)
    {
      Serial.println("CW");                           // Motor run Clock-wise direction
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      motor3.run(BACKWARD); 
      motor1.setSpeed(s); 
      motor2.setSpeed(s);
      motor3.setSpeed(s);     
    }

    
    else if(state==0x35)
    {                           
      Serial.println("STOP");                        // Motor Stop 
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);    
    }

    
    else if(state==0x36)
    {
      Serial.println("CCW");                      // Motor run Anticlock-wise direction
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor1.setSpeed(s); 
      motor2.setSpeed(s);
      motor3.setSpeed(s);      
    }

    
    else if(state==0x37)
    {
      Serial.println("SW");                     // Motor run towards South-West direction 
      motor1.run(RELEASE);    
      motor2.run(BACKWARD);
      motor3.run(FORWARD);
      motor2.setSpeed(s); 
      motor3.setSpeed(s);      
    }

    
    else if(state==0x38)
    {
      Serial.println("BACKWARD");                 // Motor run towards Backward direction 
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      motor3.run(RELEASE);    
      motor1.setSpeed(s);
      motor2.setSpeed(s);        
    }


    else if(state==0x39)
    {
      Serial.println("SE");                      // Motor run towards South-East direction 
      motor1.run(BACKWARD);
      motor2.run(RELEASE);    
      motor3.run(BACKWARD);
      motor1.setSpeed(s);
      motor3.setSpeed(s);   
    }   
  } 
}
