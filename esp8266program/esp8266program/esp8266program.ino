/*ESP8266 configuration module 
 * Performs ESP8266 configurations and transmits serial data to arduino
 * Serially Transmits integer data to arduino
 */

#include "RXTXModule.h"

void setup() {
  doESPInit();
}

void loop() {
   doESPLoop();
}
