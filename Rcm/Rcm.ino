#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "networkName";
const char *routerPass = "networkPass";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
float x = 0.0;
float y = 0.0;
float z = 0.0;
float a = 0.0;
float b = 0.0;

void Enabled() { //code to run while enabled
  quadKiwiMot(port1, port2, port3, port4, x, y, z);
  setSer(portA, a, 1500, 1000);
  setSer(portB, b, 1500, 1000);
}

void Enable() { //turn on outputs
  enableMot(port1);
  enableMot(port2);
  enableMot(port3);
  enableMot(port4);
  enableSer(portA);
  enableSer(portB);
}

void Disable() { //shut off all outputs
  disableMot(port1);
  disableMot(port2);
  disableMot(port3);
  disableMot(port4);
  disableSer(portA);
  disableSer(portB);
}

void PowerOn() { //runs once on robot startup
  setMotorCalibration(2.2);

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  x = recvFl();
  y = recvFl();
  z = recvFl();
  a = recvFl();
  b = recvFl();
  //add data to read here:

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
