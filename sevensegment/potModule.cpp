#include "potModule.h"

void doPotInit(){
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

  //Analog PIN setup for potentiometer reading
  pinMode(A0, INPUT);

}

void doPotLoop(){

    //General Use Variables
    int onTime = 20; //Delay time to hold digit values
    int trickEyes = 10; //Delay between two digits
    byte readMSD; // Most Significant Digit Value
    byte readLSD; // Lease Significant Digit Value

    //Counters
    int i;  //An integer (int) is a 32-bit number (signed)
    byte j; //A byte is an 8-bit number (unsigned)
    
    //We read the analog value of A0
    i = analogRead(A0);
    //Then, we map the analog value to a number between 0 to 1023
    i = map(i, 0, 1023, 0, 99);

    //Printing stuff...
    Serial.print("Mapped value is: ");
    Serial.println(i,DEC); //print the current analog mapped value (between 0 to 1023)

    //Most Significant and Least Significant Stuff
    readMSD = characterArray[i/10];
    readLSD = characterArray[i%10];
    
    //Print output digit to check with ssd
    Serial.print("Output Digit is: ");
    Serial.print(i/10,DEC);
    Serial.println(i%10,DEC);

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
