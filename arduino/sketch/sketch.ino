#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PusherClient.h>
#include "Wire.h"
#include "settings.h"

PusherClient client;
byte mac[] = MAC_ADDRESS;

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  
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
}

void loop() {
	if (client.connected()) {
		client.monitor();
	}
}

void lightUpFriends(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	digitalWrite(8, LOW);
	delay(LIGHTUP_DURATION);
	digitalWrite(8, HIGH);
  delay(LIGHTDOWN_DURATION);
}

void lightUpAds(String data) {
	Serial.print("Data received: ");
	Serial.println(data);
	digitalWrite(9, LOW);
	delay(LIGHTUP_DURATION);
	digitalWrite(9, HIGH);
  delay(LIGHTDOWN_DURATION);
}
