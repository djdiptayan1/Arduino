 
 #define inA 2 //encoder input
 #define inB 3 //encoder input

 #define motorin1 9 //motor in1
 #define motorin2 10//motor in2
 #define en 11 //motor enable

 int counter = 0; 
 int State;
 int LastState;
 String dir="";  
int flag=0;
 void forward(){
   digitalWrite(motorin1, HIGH);
   digitalWrite(motorin2, LOW);
 }

 void backward(){
   digitalWrite(motorin1, LOW);
   digitalWrite(motorin2, HIGH);
 }

 void stopm(){
   digitalWrite(motorin1, LOW);
   digitalWrite(motorin2, LOW);
 }

 void setup() { 
   pinMode (inA,INPUT);
   pinMode (inB,INPUT);
   pinMode (motorin1,OUTPUT);
   pinMode (motorin2, OUTPUT);
   pinMode(en, OUTPUT);
   
   Serial.begin (9600);
   LastState = digitalRead(inA);
 } 

 void loop() {
   digitalWrite(en,255);
   State = digitalRead(inA);
   if (State != LastState){
     if (digitalRead(inB) != State) {
       counter ++;
       dir="cw";
     } else {
       counter --;
       dir="acw";
     }
     Serial.print("Position: ");
     Serial.println(counter);

      if(counter<70 && flag==0)
      forward();
      if(counter>=70 && flag==0)
      {
      flag=1;
      stopm();
      delay(3000);
      }
      if(flag==1)
      backward();
      if(counter<0 && flag==1)
      stopm();
  }
  LastState = State;
 }