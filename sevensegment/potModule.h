#ifndef _POTMODULE_

#define _POTMODULE_

#include "Arduino.h"

/*Character Array Module 
 * Containing the Full Hard Coded Character Table represented in a byte
 * Also contains variables for seven segment methods
 */

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

void doPotInit();
void doPotLoop();

#endif //_POTMODULE_
