void enableSer(int ch, int pin) {
  pinMode(pin, OUTPUT);
  ledcSetup(ch, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(pin, ch);
}
void disableSer(int ch, int pin) {
  ledcDetachPin(pin);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
void setSer(int ch, int pin, float val) {
  val = constrain(val, -1, 1);
  ledcWrite(ch, SERVO_TICKS_PER_MICROSECOND * (1472 + val * 928));
}
void setSer(int ch, int pin, float val, int low, int high) {
  val = constrain(val, -1, 1);
  ledcWrite(ch, SERVO_TICKS_PER_MICROSECOND * ((high + low) / 2 + val * (high - low) / 2));
}
