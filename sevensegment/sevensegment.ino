/* Seven Segment Display Control using Potentiometer
 * 
 * This module allows a control of a seven segement display using a potentiometer / counter up
 * Character configurations of each segment is "hard coded" in the characterArray
 * Three External Modules
 *  a) Potentiometer Module: potModule.cpp and potModule.h: Seven Segment Displays a number that is mapped from analog read of potentiometer pin
 *  b) Counter Module: counterModule.cpp and counterModule.h: Seven Segment Displays a number that is auto incremented from 0-99
 *  c) ESP8266 configuration module: RXTXModule.cpp and RXTXModule.h: Performs ESP8266 configurations and transmits serial data to arduino
 */

/**Main Function**/

/*----Mode Controls (Uncomment to use, only one mode at a time)---*/
//#define POTMODE 
//#define COUNTERMODE
#define SERIALDISP

/*----Adding External Modules---*/

#include "Arduino.h"

#ifdef POTMODE
  #include "potModule.h"
#endif 

#ifdef COUNTERMODE
  #include "counterModule.h"
#endif

#ifdef SERIALDISP
  #include "serialDisp.h"
#endif

/*-------------Main Program----------------*/

//Entry point of our program, program starts here and runs setup() once initially
void setup() {
  
  //Setup Serial Monitor for debugging
  Serial.begin(9600); //Set initial baud rate of 9600
  Serial.println("---Serial Monitor ---"); //Print monitor header (only printed once)
  
  //Analog input pin for potentiometer analog read value (potPin = A0) 
  //For potentiometer mode only
  #ifdef POTMODE
    Serial.println("---Initializing Counter Module ---"); 
    doPotInit(); 
  #endif

  #ifdef COUNTERMODE
    Serial.println("---Initializing Counter Module ---"); 
    doCounterInit();
  #endif

  #ifdef SERIALDISP
    doRxInit();
  #endif 
  
}


//Main Subroutine of our program, we will repeat this until arduino dies
void loop() {

  /*----This section of code is for potentiometer mode-----*/
  #ifdef POTMODE 
    doPotLoop();
  #endif
  
  /*----This section of code is for counter module-----*/
  #ifdef COUNTERMODE 
   doCounterLoop();
  #endif

  /*----This section of code is for Arduino Receiver module from ESP8266-----*/
  #ifdef SERIALDISP
    doRxLoop();
  #endif 

}
      
      
          

      
          
