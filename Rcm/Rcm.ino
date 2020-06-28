#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "chicken";
const char *routerPass = "bawkbawk";
const char *APPass = "RCMpassword";
int port = 25213;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
PVector movement = {0.0, 0.0};
float intake = 0.0;
float flywheel = 0.0;
float hood = 0.0;
boolean laser = false;

void Enabled() { //code to run while enabled
  setSer(port4, intake);
  setSer(port3, hood);
  setMot(portC, laser ? 100 : 0);
  setMot(portD, flywheel);
  tankMot(portA, portB, movement);
}

void Enable() { //turn on outputs
  enableMot(portA);
  enableMot(portB);
  enableMot(portC);
  enableMot(portD);
  enableSer(port3);
  enableSer(port4);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portB);
  disableMot(portC);
  disableMot(portD);
  disableSer(port3);
  disableSer(port4);

}

void PowerOn() { //runs once on robot startup
  setMotorCalibration(2.2, .05);
}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
  movement = recvVect();
  intake = recvFl();
  flywheel = recvFl();
  hood = recvFl();
  laser = recvBl();

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
