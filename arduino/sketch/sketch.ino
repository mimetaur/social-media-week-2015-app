#include <SPI.h>
#include <WiFi.h>

#include "Wire.h"
#include "BlinkM_funcs.h"

#include "light_color.h"

WiFiClient client;

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 100L; // delay between updates, in milliseconds

char ssid[] = "CKGuest";     //  your network SSID (name)
char pass[] = "225CK911";  // your network password
char server[] = "social-media-week-2015.herokuapp.com";
int status = WL_IDLE_STATUS;     // the Wifi radio's status

light_color lightColor;
int lightLifetime = 1000;

void setup() {
	lightColor = { 0, 0, 0 };

  Serial.begin(9600); // set up Serial library at 9600 bps

  connectToWifi();
  printWifiStatus();

  initLights();
  turnLightOff();
}

void loop() {

  while (client.available()) {
    if ( client.find("r") ) {
      	Serial.println("found data in request");
        lightColor.red = client.parseInt();
        lightColor.green = client.parseInt();
        lightColor.blue = client.parseInt();
    }
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
		getLightColor();
  }

  setLightToRgbColor(lightColor.red, lightColor.green, lightColor.blue);
}
