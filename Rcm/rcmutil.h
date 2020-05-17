boolean enabled = false;
boolean wasEnabled = false;
float batVolt = 0.0;
const int ONBOARD_LED = 2;
const float DAC_UnitsPerVolt = 10;
const int BAT_PIN = 36;
#define PORT_1 27
#define PORT_2 26
#define PORT_3 25
#define PORT_4 33
#define PORT_5 32
#define PORT_A 13,15,14
#define PORT_B 18,5,21
#define PORT_C 17,16,4
#define PORT_D 23,22,19

void enableMot(int en, int i1, int i2) {

}
void disableMot(int en, int i1, int i2) {

}
void setMot(int en, int i1, int i2, int val) {

}
void setMot(int en, int i1, int i2, float val) {

}
void tankMot(int enl, int i1l, int i2l, int enr, int i1r, int i2r, int turn, int speed) {

}
void tankMot(int enl, int i1l, int i2l, int enr, int i1r, int i2r, float turn, float speed) {

}


struct PVector {
  float x;
  float y;
};
