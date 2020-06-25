boolean enabled = false;
boolean wasEnabled = false;
float batVolt = 0.0;
float batVoltAvg = 0.0;
const int ONBOARD_LED = 2;
const float DAC_UnitsPerVolt = 413;
const int BAT_PIN = 36;
const int PWM_FREQ = 2000;
const int PWM_RES = 10;
const int PWM_RANGE = 1023;
const float SERVO_TICKS_PER_MICROSECOND = 52.4288;
const int SERVO_FREQ = 50;
const int SERVO_RES = 20;
float motorMinMovePWMVal = 0;
float motorDeadzone = 0;
//          PWM_CH, PIN
#define port1 8,32
#define port2 7,33
#define port3 6,25
#define port4 5,26
#define port5 4,27
//           PWM_CH, EN_PIN, PIN1, PIN2
#define portA 3,23,22,19
#define portB 1,5,18,21
#define portC 2,17,16,12
#define portD 0,13,4,14

struct PVector {
  float x;
  float y;
};
