#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "Garage2.4";
const char *routerPass = "TamiBeach";
const char *APPass = "RCMpassword";
int port = 25216;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
float throttle = 0;
float yaw = 0;
float lift = 0;
float finger = 0;
float lifter = 0;

void Enabled() { //code to run while enabled
  tankMot(portA, portC, yaw, throttle);
  setMot(portB, lift);
////////////////////////
  setSer(port5,lifter,500,2000);
  setSer(port4,finger,500,2000);
}

void Enable() { //turn on outputs
  enableMot(portA);
  enableMot(portB);
  enableMot(portC);
  enableSer(port5);
  enableSer(port4);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portB);
  disableMot(portC);
  disableSer(port5);
  disableSer(port4);
}

void PowerOn() { //runs once on robot startup, set pinmodes
  setMotorCalibration(2.2, .05);
}

void Always(){ //always runs if void loop is running, don't control outputs here

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
throttle = recvFl();
yaw = recvFl();
lift = recvFl();
finger = recvFl();
lifter = recvFl();
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
