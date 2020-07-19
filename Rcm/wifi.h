#include <WiFi.h>
#include <WiFiUdp.h>
char APName[9];
WiFiUDP udp;
const int maxWifiSendBufSize = 100;
const int maxWifiRecvBufSize = 100;
boolean wifiConnected = false;
boolean receivedNewData = false;
unsigned long lastMessageTimeMillis = 0;
byte recvdData[maxWifiRecvBufSize] = {0};
byte dataToSend[maxWifiSendBufSize] = {0};
char packetBuffer[maxWifiRecvBufSize] = {0};
int numBytesToSend = 0;
int wifiArrayCounter = 0;
IPAddress wifiIPLock=IPAddress(0, 0, 0, 0);
