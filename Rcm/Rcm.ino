#include "wifi.h"
const char *routerName = "chicken";
const char *routerPass = "bawkbawk";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("##########esp32 powered on.");
  setupWifi();
}

void loop() {
  wifiComms();

}
//you can communicate booleans, bytes, ints, and floats
void WifiDataToParse() {
  wifiArrayCounter = 0;
  //add data to read here:
  Serial.println(readIntFromBuffer());

}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  //add data to send here:
  addIntToBuffer(millis());

  return wifiArrayCounter;
}
