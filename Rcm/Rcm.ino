#include "rcmutil.h"
#include "wifi.h"
const char *routerName = "Garage2.4";
const char *routerPass = "TamiBeach";
const char *APPass = "RCMpassword";
int port = 25213;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
float throttle = 0;
float swerve = 0;
float yaw = 0;
float Sthrottle = 0;
float Sswerve = 0;
float Syaw = 0;
float inouttake = 0;
float arm = 0;
float lights = 0;
//////////////////////////// add variables here

void Enabled() { //code to run while enabled
  Sthrottle = throttle / (1 + abs(swerve) + abs(yaw));
  Sswerve = swerve / (1 + abs(throttle) + abs(yaw));
  Syaw = yaw / (1 + abs(throttle) + abs(yaw));

  setMot(portA, (Sthrottle - Sswerve + Syaw)); //back left motor
  setMot(portB, (Sthrottle + Sswerve + Syaw)); //front left motor
  setMot(portC, (Sthrottle + Sswerve - Syaw)); //back right motor
  setMot(portD, (Sthrottle - Sswerve - Syaw)); //front right motor

  setSer(port3,arm,1,2000);
  setSer(port5,inouttake);
  setSer(port4,-inouttake);
}

void Enable() { //turn on outputs
  enableMot(portA);
  enableMot(portB);
  enableMot(portC);
  enableMot(portD);
  enableSer(port3);
  enableSer(port5);
  enableSer(port4);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portB);
  disableMot(portC);
  disableMot(portD);
  disableSer(port3);
  disableSer(port5);
  disableSer(port4);
}

void PowerOn() { //runs once on robot startup, set pinmodes
  setMotorCalibration(2.2, .05);
}

void Always() { //always runs if void loop is running, don't control outputs here

}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
throttle = recvFl();
swerve = recvFl();
yaw = recvFl();
inouttake = recvFl();
arm = recvFl();
lights = recvFl();
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
