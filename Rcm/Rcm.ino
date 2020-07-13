#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "chicken";
const char *routerPass = "bawkbawk";
const char *APPass = "RCMpassword";
int port = 25212;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
float x = 0.0;
float y = 0.0;
float z = 0.0;
float a = 0.0;
float b = 0.0;

void Enabled() { //code to run while enabled
  quadkiwiMot(portB, portA, portC, portD, x, y, z);
  setSer(port1, a, 1500, 1400);
  setSer(port2, -b, 1500, 1400);
}

void Enable() { //turn on outputs
  enableMot(portB);
  enableMot(portA);
  enableMot(portC);
  enableMot(portD);
  enableSer(port1);
  enableSer(port2);
}

void Disable() { //shut off all outputs
  disableMot(portB);
  disableMot(portA);
  disableMot(portC);
  disableMot(portD);
  disableSer(port1);
  disableSer(port2);
}

void PowerOn() { //runs once on robot startup
  setMotorCalibration(2.2, .05);

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
  y = recvFl();
  x = recvFl();
  z = recvFl();
  b = recvFl();
  a = recvFl();
}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  sendFl(batVoltAvg);
  //add data to send here:
  sendFl(2);
  sendFl(5);
  sendFl(4);
  sendFl(25.21);
  sendFl(1);
  sendFl(4);
  sendFl(8);

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
