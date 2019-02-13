# Seven Segment 

This is a double seven segment display module controlled using Arduino.  
Has three different modes

- Potentiometer Mode: Control number to display by potentiometer.  
- Auto Counter: Automatically increments from 0-99 and displays it. 
- Web Server control: Input a number from 0-99 on the web and see it display on the seven segment!
	* Uses ESP8266 as a web server
	* ESP8266 communicates the display number to Arduino Uno using serial communication
