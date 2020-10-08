#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "google2";
const char *routerPass = "5413422189";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here

//PVector driveVect = {0.0, 0.0};
float drive = 0.0;
float turn = 0.0;
float intake = 0.0;
float arm = 0.0;

void Enabled() { //code to run while enabled
  setSer(port1, arm, 900, 2100);
  setSer(port2, -arm, 900, 2100);
  setSer(port3, intake, 900, 2100);
  tankMot(portA, portC, turn, drive);
}

void Enable() { //turn on outputs
  enableMot(portA);
  enableMot(portC);
  enableSer(port1);
  enableSer(port2);
  enableSer(port3);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portC);
  disableSer(port1);
  disableSer(port2);
  disableSer(port3);
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
  drive = recvFl();
  turn = recvFl();
  recvFl();  //throw away strafing
  intake = recvFl();
  arm = recvFl();
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
