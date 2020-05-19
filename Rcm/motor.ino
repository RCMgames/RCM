void enableMot(int ch, int en, int i1, int i2) {
  ledcSetup(ch, PWM_FREQ, PWM_RES);
  ledcAttachPin(en, ch);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, HIGH);
  ledcWrite(ch, 0);
}
void disableMot(int ch, int en, int i1, int i2) {
  ledcDetachPin(en);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(en, LOW);
}
void setMot(int ch, int en, int i1, int i2, int val) {
  val = constrain(val, -PWM_RANGE, PWM_RANGE);
  if (val > 0) {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, LOW);
    ledcWrite(ch, val);
  }  else if (val < 0) {
    digitalWrite(i1, LOW);
    digitalWrite(i2, HIGH);
    ledcWrite(ch, -val);
  }
  else {
    digitalWrite(i1, HIGH);
    digitalWrite(i2, HIGH);
    digitalWrite(en, LOW);
  }
}
void setMot(int ch, int en, int i1, int i2, float val) {
  setMot(ch, en, i1, i2, int(val * 255));
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, int turn, int speed) {
  setMot(chl, enl, i1l, i2l, turn + speed);
  setMot(chr, enr, i1r, i2r, -turn + speed);
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, float turn, float speed) {
  setMot(chl, enl, i1l, i2l, int(turn * 255) + int(speed * 255));
  setMot(chr, enr, i1r, i2r, -int(turn * 255) + int(speed * 255));
}

void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, PVector vect) {
  setMot(chl, enl, i1l, i2l, int(vect.x * 255) + int(vect.y * 255));
  setMot(chr, enr, i1r, i2r, -int(vect.x * 255) + int(vect.y * 255));
}
