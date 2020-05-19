void enableSer(int ch, int pin) {
  ledcSetup(ch, SERVO_FREQ, SERVO_RES);
  ledcAttachPin(pin, ch);
}
void disableSer(int ch, int pin) {
  ledcDetachPin(pin);
}
void setSer(int ch, int pin, float val) {
  val = constrain(val, -1, 1);
  ledcWrite(ch, SERVO_TICKS_PER_MICROSECOND * (1500 + val * 500));
}
void setSer(int ch, int pin, float val, int centerPulse, int rangePulse) {
  val = constrain(val, -1, 1);
  ledcWrite(ch, SERVO_TICKS_PER_MICROSECOND * (centerPulse + val * rangePulse / 2));
}
