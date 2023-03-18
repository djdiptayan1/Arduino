#include<SPI.h>
#include<SD.h>

File myfile; //create a file named attendance

constexpr uint8_t cs = D8;//NODE MCU

void setup(){
  Serial.begin(9600);
  while(!Serial){
    ;
  }

  Serial.println("Initializing SD card");

 // if(!SD.begin(4)){ //arduino
    if(!SD.begin(cs)){ //nodeMCU
    Serial.println("initialization failed");
    while(1);
  }
  Serial.println("initialization DONE");

  if(SD.exists("attendance1.csv")) //checks whether the file is available or not
  Serial.println("FILE EXISTS");
  else
  Serial.println("FILE DOESN'T EXISTS");

//writing into file "attendance.txt"
  myfile=SD.open("attendance1.csv", FILE_WRITE);
  myfile.write("WRITING :) :)");
  Serial.println("WROTE IN FILE SUCCESSFUL");
  myfile.close();

//reading a file
  myfile=SD.open("attendance1.csv", FILE_READ);
  myfile.write("READING :) :)");
  while(myfile.available()){
    Serial.write(myfile.read());
  }
  myfile.close();
}
void loop(){
  
}