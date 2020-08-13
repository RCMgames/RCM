#include "rcmutil.h"
#include "wifi.h"
// Change once router has been set up
const char *routerName = "networkName";
const char *routerPass = "networkPass";
const char *APPass = "RCMpassword";
int port = 25210;
const boolean connectToNetwork = true; //true=try to connect to router  false=go straight to hotspot mode
const boolean wifiRestartNotHotspot = true; //when connection issue, true=retry connection to router  false=fall back to hotspot
const int SIGNAL_LOSS_TIMEOUT = 1000; //disable if no signal after this many milliseconds
//////////////////////////// add variables here
float turn = 0.0;
float forward = 0.0;
// How much power to give to the conveyor motors
float intake = 0.0;
// Value read by the distance sensor
float sensorValue = 0.0;


void Enabled() { //code to run while enabled
  // Run drivetrain motors 
  tankMot(portA, portD, turn, forward);
  // Run conveyor motors
  setMot(portB, intake);
  setMot(portC, intake);
}

void Enable() { //turn on outputs
  // Drive motors. Need to figure out exact ports
  enableMot(portA);
  enableMot(portD);
  // Conveyor motors. Need to figure out exact ports
  enableMot(portB);
  enableMot(portC);
}

void Disable() { //shut off all outputs
  disableMot(portA);
  disableMot(portB);
  disableMot(portC);
  disableMot(portD);
}

void PowerOn() { //runs once on robot startup
  // Can play with to make robot drive better
  setMotorCalibration(2.2, .05);
}

void Always(){ //always runs if void loop is running, don't control outputs here
  // Get values from the distance sensor
  sensorValue = digitalRead(port1Pin);
}

//you can communicate booleans, bytes, ints, floats, and vectors
void WifiDataToParse() {
  wifiArrayCounter = 0;
  enabled = recvBl();
  //add data to read here:
  forward = recvFl();
  // skip strafe
  recvFl();
  turn = recvFl();
  intake = recvFl();
}

int WifiDataToSend() {
  wifiArrayCounter = 0;
  sendFl(batVoltAvg);
  //add data to send here:
  sendFl(sensorValue);
  
  return wifiArrayCounter;
}

////////////////////////////////////////////////
void setup() {
  Disable();
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BAT_PIN, INPUT);
  pinMode(port1Pin, INPUT);
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
