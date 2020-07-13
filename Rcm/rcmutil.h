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
#define port1Pin 32
#define port2Pin 33
#define port3Pin 25
#define port4Pin 26
#define port5Pin 27
//          PWM_CH, PIN
#define port1 8,port1Pin
#define port2 7,port2Pin
#define port3 6,port3Pin
#define port4 5,port4Pin
#define port5 4,port5Pin
//           PWM_CH, EN_PIN, PIN1, PIN2
#define portA 3,23,22,19
#define portB 1,5,18,21
#define portC 2,17,16,12
#define portD 0,13,4,14

#define inport1 39
#define inport2 34
#define inport3 35

struct PVector {
  float x;
  float y;
};
