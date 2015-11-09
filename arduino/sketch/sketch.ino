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
		client.bind("friends_tweeted", lightUpFriends);
		client.bind("ads_tweeted", lightUpAds);
		client.subscribe("smw2015_channel");
	}
	else {
		while(1) {}
	}

	pinMode(12, OUTPUT);
	digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
	digitalWrite(12, HIGH);
}

void loop() {
	if (client.connected()) {
		client.monitor();
	}
}

void lightUpFriends(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	digitalWrite(12, HIGH);
	delay(LIGHTUP_DURATION);
	digitalWrite(12, LOW);
}

void lightUpAds(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	digitalWrite(13, HIGH);
	delay(LIGHTUP_DURATION);
	digitalWrite(13, LOW);
}
