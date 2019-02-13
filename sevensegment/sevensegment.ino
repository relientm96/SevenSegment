/* Seven Segment Display Control using Potentiometer
 * 
 * This module allows a control of a seven segement display using a potentiometer / counter up
 * Character configurations of each segment is "hard coded" in the characterArray
 * If mode == 1, potentiometer mode, if mode == 0, counter mode
 */

//Pre-processor macros
//#define <VARIABLE NAME> <VALUE> lets the program know that if they see this variable name, just replace it with value

//Mode Controls (Uncomment to use, only one mode at a time)
//#define POTMODE 
//#define COUNTERMODE
#define RXTXMODE 

/*Adding our externally defined modules*/

#ifdef RXTXMODE
  #include "RXTXModule.h"
#endif

/*--------------Variable and Constants Definitions----------------*/
//Here we define the global variables we need that can be "seen" and used by all subroutines

const byte characterArray[] = {
//  ABCDEFG        Segments        7-segment map:
  0b1111110, // index: 0   "0"          AAA
  0b0110000, // index: 1   "1"         F   B
  0b1101101, // index: 2   "2"         F   B
  0b1111001, // index: 3   "3"          GGG
  0b0110011, // index: 4   "4"         E   C
  0b1011011, // index: 5   "5"         E   C
  0b1011111, // index: 6   "6"          DDD
  0b1110000, // index: 7   "7"
  0b1111111, // index: 8   "8"
  0b1111011, // index: 9   "9"
  
 /*Uncomment below to enable hex characters*/
 // 0b1110111, // 10  "A" 
 // 0b0011111, // 11  "b"
 // 0b1001110, // 12  "C"
 // 0b0111101, // 13  "d"
 // 0b1001111, // 14  "E"
 // 0b1000111, // 15  "F"
};

//General Use Variables
int onTime = 20; //Delay time to hold digit values
int trickEyes = 10; //Delay between two digits
byte readMSD; // Most Significant Digit Value
byte readLSD; // Lease Significant Digit Value

//Counters
int i;  //An integer (int) is a 32-bit number (signed)
byte j; //A byte is an 8-bit number (unsigned)

//Pin Names (for convinience)
const int potPin = A0;

/*-------------Main Program Starts Here----------------*/
/* Order: start program -> setup() -> loop() -> loop() -> loop() -> loop().... (until user turns off arduino)*/

//Entry point of our program, program starts here and runs setup() once initially
void setup() {
  
  //Setup Serial Monitor for debugging
  Serial.begin(9600); //Set initial baud rate of 9600
  Serial.println("---Serial Monitor ---"); //Print monitor header (only printed once)
  
  /*Setup Pin assignments*/
  // void pinMode( <pin number> , <type of pin> )
  // returns: void (nothing)
  // parameters: a) <pin number> : this is where you put your pin # on arduino that you want to control
  //             b) <type of pin> : Only accepts two values, INPUT or OUTPUT (which is a pre-defined macro to define if pin is input/output)

  #if defined POTMODE || defined COUNTERMODE
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
  
  #endif

  //Analog input pin for potentiometer analog read value (potPin = A0) 
  //For potentiometer mode only
  #ifdef POTMODE
     pinMode(potPin, INPUT);
  #endif

  //RX TX Mode for ESP8266 board programming
  #ifdef RXTXMODE
    Serial.println("---Initializing ESP8266 ---"); //Print monitor header (only printed once)
    doESPInit();
  #endif RXTXMODE
}


//Main Subroutine of our program, we will repeat this until arduino dies
void loop() {

  /*----This section of code is for potentiometer mode-----*/
  #ifdef POTMODE 

      //We read the analog value of A0
      i = analogRead(potPin);
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
  #endif

 /*-------------------------------------------------*/
      
 /*----This section of code is for counter mode-----*/
 #ifdef COUNTERMODE 

  //Outer loop controls which number to increment to
  for(i = 0; i <= 99; i++){

      //Printing stuff...
      Serial.print("Now Printing Number: ");
      Serial.println(i,DEC); //print the current index, i in DECimal format

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
      
 #endif
 /*-------------------------------------------------*/

 #ifdef RXTXMODE
  doESPLoop();
 #endif 
}
      
      
          
