#include "serialDisp.h"

void doRxInit(){
  pinMode(13, OUTPUT);   //c segment       
  pinMode(2, OUTPUT);    //decimal point segment
  pinMode(3, OUTPUT);    //e segement     
  pinMode(4, OUTPUT);    //d segement    
  pinMode(5, OUTPUT);    //g segement     
  pinMode(6, OUTPUT);    //f segement    
  pinMode(9, OUTPUT);    //b segement     
  pinMode(10, OUTPUT);   //a segement   
    
  //Cathode Controls (Digit Select "Cathod" Pins)
  pinMode(7, OUTPUT);   //right digit select
  pinMode(8, OUTPUT);   //left digit select
}

void doRxLoop(){

    //General Use Variables
    int onTime = 20; //Delay time to hold digit values
    int trickEyes = 10; //Delay between two digits
    byte readMSD; // Most Significant Digit Value
    byte readLSD; // Lease Significant Digit Value

    //Counters
    byte i;  //A byte storing the received data from ESP8266
    byte j; //A byte is an 8-bit number (unsigned)

    i = 87;

    //Obtain our right digit and left digit display numbers
    readMSD = characterArray[i/10];
    readLSD = characterArray[i%10];

    //Printing out output to check if equal to seven segment
    Serial.print("Output Digit is: ");
    Serial.print((i/10),DEC);
    Serial.println((i%10),DEC);

    //This inner loop loops through to display the two digits at fast speeds
    //(Increase speedOfHoldingNumber to make it slower)
    int speedOfHoldingNumber = 5;
    for(j = 0; j <= speedOfHoldingNumber; j++){

    //1. Choose Side
    digitalWrite(7, LOW);       
    digitalWrite(8, HIGH);   

    //2. Display Right Digit Character from array (turning LED's ON)
    digitalWrite(10,(1<<6)&(readLSD));
    digitalWrite(9, (1<<5)&(readLSD));       
    digitalWrite(13, (1<<4)&(readLSD));        
    digitalWrite(4, (1<<3)&(readLSD));        
    digitalWrite(3, (1<<2)&(readLSD));      
    digitalWrite(6, (1<<1)&(readLSD));        
    digitalWrite(5, (1<<0)&(readLSD));        
    digitalWrite(2, (1<<7)&(readLSD));  //DP 

    //3. Leave display on for some time 
    delay(trickEyes);               
        
    //4. Change to other side
    digitalWrite(7,HIGH);  
    digitalWrite(8, LOW);       

    //5. Display the left digit
    digitalWrite(10,(1<<6)&(readMSD));
    digitalWrite(9, (1<<5)&(readMSD));       
    digitalWrite(13, (1<<4)&(readMSD));        
    digitalWrite(4, (1<<3)&(readMSD));        
    digitalWrite(3, (1<<2)&(readMSD));      
    digitalWrite(6, (1<<1)&(readMSD));        
    digitalWrite(5, (1<<0)&(readMSD));        
    digitalWrite(2, (1<<7)&(readMSD));      

    //6. Display the character for some time
    delay(onTime);   
    }

}
