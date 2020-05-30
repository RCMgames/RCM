void enableMot(int ch, int en, int i1, int i2) {
  ledcSetup(ch, PWM_FREQ, PWM_RES);
  ledcAttachPin(en, ch);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, HIGH);
  ledcWrite(ch, 0);
}
void disableMot(int ch, int en, int i1, int i2) {
  ledcDetachPin(en);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(en, OUTPUT);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(en, LOW);
}
void setMot(int ch, int en, int i1, int i2, int val) {
  val = constrain(val, -PWM_RANGE, PWM_RANGE);
  if (val > 0) {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, LOW);
    val = calibrateMotorValue(val);
    ledcWrite(ch, val);
  }  else if (val < 0) {
    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
    val = calibrateMotorValue(-val);
    ledcWrite(ch, val);
  }
  else {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, HIGH);
    digitalWrite(en, LOW);
  }
}

void setMot(int ch, int en, int i1, int i2, float val) {
  setMot(ch, en, i1, i2, int(val * PWM_RANGE));
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, int turn, int speed) {
  setMot(chl, enl, i1l, i2l, turn + speed);
  setMot(chr, enr, i1r, i2r, -turn + speed);
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, float turn, float speed) {
  setMot(chl, enl, i1l, i2l, int(turn * PWM_RANGE + speed * PWM_RANGE));
  setMot(chr, enr, i1r, i2r, int(-turn * PWM_RANGE + speed * PWM_RANGE));
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, PVector vect) {
  setMot(chl, enl, i1l, i2l, int(vect.x * PWM_RANGE + vect.y * PWM_RANGE));
  setMot(chr, enr, i1r, i2r, int(-vect.x * PWM_RANGE + vect.y * PWM_RANGE));
}
void quadkiwiMot(int ch1, int en1, int a1, int b1, int ch2, int en2, int a2, int b2, int ch3, int en3, int a3, int b3, int ch4, int en4, int a4, int b4, float _x, float _y, float _z) {
  if (_x + _y + _z == 0) {
    float x = 0;
    float y = 0;
    float z = 0;
  } else {
    float x = x / (_x + _y + _z);
    float y = y / (_x + _y + _z);
    float z = z / (_x + _y + _z);
  }
  setMot(ch1, en1, a1, b1, z - y + x);
  setMot(ch2, en2, a2, b2, z + y + x);
  setMot(ch3, en3, a3, b3, z + y - x);
  setMot(ch4, en4, a4, b4, z - y - x);
}

void setMotorCalibration(float val) {
  motorMinMovePower = PWM_RANGE * val;
}
int calibrateMotorValue(int val) {
  return map(val, 0, PWM_RANGE, motorMinMovePower / batVoltAvg, PWM_RANGE);
}
