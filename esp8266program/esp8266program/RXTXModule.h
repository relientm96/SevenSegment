#ifndef _RXTXMODULE_

#define _RXTXMODULE_

#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

void handleRoot();              // function prototypes for HTTP handlers
void handleNumberInput();       // handles POST request by client
void handleNotFound();          // for invalid URLs
void seriallySendNumber(byte result); //Serially send input number to arduino

void doESPInit();
void doESPLoop();

#endif //_RXTXMODULE_
