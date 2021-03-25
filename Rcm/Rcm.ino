#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "networkName";
const char *routerPass = "networkPass";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
float speed = 0.0;
void Enabled() { //code to run while enabled
  setSer(port1, speed);
}

void Enable() { //turn on outputs
  enableSer(port1);
}

void Disable() { //shut off all outputs
  disableSer(port1);
}

void PowerOn() { //runs once on robot startup, set pinmodes

}

void Always() { //always runs if void loop is running, don't control outputs here

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
  speed = recvFl();

}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  sendFl(batVoltAvg);
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
  batVoltAvg = analogRead(BAT_PIN) / DAC_UnitsPerVolt;
  PowerOn();
}

void loop() {
  batVolt = analogRead(BAT_PIN) / DAC_UnitsPerVolt;
  batVoltAvg = batVolt * .001 + batVoltAvg * (.999);
  wasEnabled = enabled;
  wifiComms();
  if (millis() - lastMessageTimeMillis > SIGNAL_LOSS_TIMEOUT) {
    enabled = false;
  }
  Always();
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
