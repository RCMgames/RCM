boolean enabled = false;
boolean wasEnabled = false;
float batVolt = 0.0;
const int ONBOARD_LED = 2;
const float DAC_UnitsPerVolt = 413;
const int BAT_PIN = 36;
const int PWM_FREQ = 12000;
const int PWM_RES = 8;
const int PWM_RANGE = 255;
//          PWM_CH, PIN
#define PORT_1 4,27
#define PORT_2 5,26
#define PORT_3 6,25
#define PORT_4 7,33
#define PORT_5 8,32
//           PWM_CH, EN_PIN, PIN1, PIN2
#define PORT_A 0,13,15,14
#define PORT_B 1,18,5,21
#define PORT_C 2,17,16,4
#define PORT_D 3,23,22,19

void enableMot(int ch, int en, int i1, int i2) {
  ledcSetup(ch, PWM_FREQ, PWM_RES);
  ledcAttachPin(en, ch);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, HIGH);
  ledcWrite(ch, 0);
}
void disableMot(int ch, int en, int i1, int i2) {
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
  setMot(en, i1, i2, int(val * 255);
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, int turn, int speed) {
  setMot(enl, i1l, i2l, turn + speed);
  setMot(enr, i1r, i2r, -turn + speed);
}
void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, float turn, float speed) {
  setMot(enl, i1l, i2l, int(turn * 255) + int(speed * 255));
  setMot(enr, i1r, i2r, -int(turn * 255) + int(speed * 255));
}

void tankMot(int chl, int enl, int i1l, int i2l, int chr, int enr, int i1r, int i2r, PVector vect) {
  setMot(enl, i1l, i2l, int(vect.x * 255) + int(vect.y * 255));
  setMot(enr, i1r, i2r, -int(vect.x * 255) + int(vect.y * 255));
}

struct PVector {
  float x;
  float y;
};
