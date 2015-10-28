#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PusherClient.h>
#include "Wire.h"
#include "BlinkM_funcs.h"
#include "settings.h"

PusherClient client;
byte mac[] = MAC_ADDRESS;

void setup() {
	Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Init Ethernet failed");
  }

	if(client.connect(PUSHER_KEY)) {
		if (IS_LISTENING_FRIENDS) {
			client.bind("friends_tweeted", lightUp);
		}

		if (IS_LISTENING_ADS) {
			client.bind("ads_tweeted", lightUp);
		}

		client.subscribe("smw2015_channel");
	}
	else {
		while(1) {}
	}

  initLights();
}

void loop() {
	if (client.connected()) {
		client.monitor();
	}
}

void lightUp(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	setLightToRgbColor(RED, GREEN, BLUE);
	delay(LIGHTUP_DURATION);
	turnLightOff();
}
