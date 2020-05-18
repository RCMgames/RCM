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


struct PVector {
  float x;
  float y;
};
