 
 #define inA 4
 #define inB 5

 int counter = 0; 
 int aState;
 int aLastState;  

 void setup() { 
   pinMode (inA,INPUT);
   pinMode (inB,INPUT);
   
   Serial.begin (9600);
   aLastState = digitalRead(inA);   
 } 

 void loop() { 
   aState = digitalRead(inA);
   if (aState != aLastState){     
     if (digitalRead(inB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState;
 }
