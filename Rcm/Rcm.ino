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
float ls = 0;
float lt = 0;
float rs = 0;
float rt = 0;
float lturn = 0;
float rturn = 0;
float lspeed = 0;
float rspeed = 0;
float turnLimit = .6;
float accelLimit = 6;
unsigned long lastLoopMillis = 0;
void Enabled() { //code to run while enabled
  float delta = (millis() - lastLoopMillis) / 1000.0;
  lturn += constrain(lt - lturn, -turnLimit * delta, turnLimit * delta);
  rturn += constrain(rt - rturn, -turnLimit * delta, turnLimit * delta);
  lspeed += constrain(ls - lspeed, -accelLimit * delta, accelLimit * delta);
  rspeed += constrain(rs - rspeed, -accelLimit * delta, accelLimit * delta);
  setSer(port1, -lturn, 550, 2450);
  setSer(port2, -rturn, 450, 2480);
  setMot(portA, lspeed);
  setMot(portD, rspeed);
  lastLoopMillis = millis();
}

void Enable() { //turn on outputs
  lastLoopMillis = millis();
  enableSer(port1);
  enableSer(port2);
  enableMot(portA);
  enableMot(portD);
}

void Disable() { //shut off all outputs
  disableSer(port1);
  disableSer(port2);
  disableMot(portA);
  disableMot(portD);
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
  ls = recvFl();
  lt = recvFl();
  rs = recvFl();
  rt = recvFl();
}
int WifiDataToSend() {
  wifiArrayCounter = 0;
  sendFl(batVoltAvg);
  //add data to send here:
  sendFl((lturn < 0 ? map(lturn * 1000, -770, 0, -90, 0) : map(lturn * 1000, 0, 700, 0, 90)));
  sendFl((rturn < 0 ? map(rturn * 1000, -840, 0, -90, 0) : map(rturn * 1000, 0, 660, 0, 90)));
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
