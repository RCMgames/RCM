#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "networkName";
const char *routerPass = "networkPass";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = false; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
PVector driveVect = {0.0, 0.0};
float servoVal = 0.0;

void Enabled() { //code to run while enabled
  setSer(port1, servoVal);
  tankMot(portA, portB, driveVect);
}

void Enable() { //turn on outputs
  enableMot(portA);
  enableMot(portB);
  enableSer(port1);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portB);
  disableSer(port1);
}

void PowerOn() { //runs once on robot startup
  setMotorCalibration(2.2, .05);

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
  driveVect = recvVect();
  recvFl();//throw away strafing
  recvFl();//throw away first servo value
  servoVal = recvFl();
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
