#include "wifi.h"
const char *routerName = "chicken";
const char *routerPass = "bawkbawk";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
////////////////////////////////////////
boolean ledVal = false;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("##########esp32 powered on.");
  setupWifi();
  ///////////////////
  pinMode(2, OUTPUT);
}

void loop() {
  wifiComms();
  digitalWrite(2, ledVal);
}
//you can communicate booleans, bytes, ints, and floats
void WifiDataToParse() {
  wifiArrayCounter = 0;
  //add data to read here:
  ledVal = readBoolFromBuffer();

}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  //add data to send here:
  addIntToBuffer(millis());

  return wifiArrayCounter;
}
