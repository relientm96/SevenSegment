#include "RXTXModule.h"

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot() {                          // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<div> <h1>Seven Segment Control </h1> <form method=\"POST\"><input type=\"text\" name=\"number\" placeholder=\"Number\"></br><input type=\"submit\" value=\"Send Number\"></form><p>Enter a number between 0-99</p></div>");
}

 // POST Request Handler
void handleLogin() {
  byte result = 0;
  result = server.arg("number").toInt();
  Serial.print("Number entered is: ");
  Serial.println(result,DEC);
  
  if( (server.arg("number") != NULL) && ((result<=99)&&(result>=0)) ) { 
    server.send(200, "text/html", "<h1>Sucessfully sent number: " + server.arg("number") + "!</h1>");
  } else {                                                                              
    server.send(401, "text/plain", "401: Invalid Number!");
  }
  
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void doESPInit(){
  
  wifiMulti.addAP("china", "bidibadadowop");   // add Wi-Fi networks you want to connect to

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/", HTTP_POST, handleLogin); // Call the 'handleLogin' function when a POST request is made to URI "/login"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");
}

void doESPLoop(){
	 server.handleClient();                     // Listen for HTTP requests from clients
}
