#include <EEPROM.h>

#define cfgStart 0


struct storeStruct_t {
  char ssid[10] = "Motuthree";
  char pass[10] = "08123456";

  bool StateSystem;

  int CountSYS = 0;

  uint32_t StateFanIN1;
  uint32_t StateFanIN2;
  uint32_t StateFanOut1;
  uint32_t StateFanOut2;
  uint32_t StateFogging1;
  uint32_t StateFogging2;
  uint32_t StateHeater1;
  uint32_t StateHeater2;
  uint32_t StateHeater3;

  struct SetSystem {
    int DayCount;
    bool State;
    float Temp;
    int Hum;
    char ToDay[11];
    char TimeBefore[10];
    char TimeAfter[10];
  } DaySubSec[16];
};

storeStruct_t settings;
storeStruct_t load;

void setup() {
  Serial.begin(115200);
  SetDefaultDataInEEPROM();
  //SaveEEPROM();
  Serial.println(settings.ssid);
  Serial.println(settings.pass);

  /*
     char ssid[10] = "Motuthree";
    char pass[10] = "08123456";
  */
}

void loop() {


}
