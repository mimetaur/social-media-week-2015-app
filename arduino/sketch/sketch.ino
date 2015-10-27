#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PusherClient.h>

#include "Wire.h"
#include "BlinkM_funcs.h"

#include "light_color.h"

PusherClient client;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

light_color lightColor;

void setup() {
	lightColor = { 0, 0, 0 };

	Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Init Ethernet failed");
  }

	if(client.connect("62b391c0f827198df078")) {
		client.bind("hashtag_tweeted", hashtagTweeted);
		client.subscribe("smw2015_channel");
	}
	else {
		while(1) {}
	}

  initLights();
  turnLightOff();
}

void loop() {
	if (client.connected()) {
		client.monitor();
	}
}

void hashtagTweeted(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	setLightToRgbColor(0, 255, 0);
	delay(1000);
	turnLightOff();
}
