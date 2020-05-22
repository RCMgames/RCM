#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "networkName";
const char *routerPass = "networkPass";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here

void Enabled() { //code to run while enabled

}

void Enable() { //turn on outputs

}

void Disable() { //shut off all outputs

}

void PowerOn() { //runs once on robot startup

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:

}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  sendFl(batVolt);
  //add data to send here:

  return wifiArrayCounter;
}

////////////////////////////////////////////////
void setup() {
  Disable();
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BAT_PIN, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("##########esp32 powered on.");
  setupWifi();
  PowerOn();
}

void loop() {
  batVolt = analogRead(BAT_PIN) / DAC_UnitsPerVolt;
  wasEnabled = enabled;
  wifiComms();
  if (millis() - lastMessageTimeMillis > SIGNAL_LOSS_TIMEOUT) {
    enabled = false;
  }
  if (enabled && !wasEnabled) {
    Enable();
  }
  if (!enabled && wasEnabled) {
    Disable();
  }
  if (enabled) {
    Enabled();
    digitalWrite(ONBOARD_LED, millis() % 500 < 250);
  } else {
    digitalWrite(ONBOARD_LED, HIGH);
  }
}
