#include <EEPROM.h>

#define cfgStart 0


struct storeStruct_t {
  char ssid[10] = "Motuthree";
  char pass[10] = "08123456";

  int CountSYS = 0;

  struct SetSystem {
    bool State;
    float Temp;
    int Hum;
    char ToDay[11] = "00/00/00";
    char TimeBefore[10] = "00:00:00";
    char TimeAfter[10] = "00:00:00";
  } DaySubSec[16];
};

storeStruct_t settings;

void setup() {
  Serial.begin(115200);
  SaveEEPROM();
  Serial.println(settings.ssid);
  Serial.println(settings.pass);
  Serial.println();
  for (int i = 0 ; i < 16; i++) {
    Serial.println("--------------------------------------");
    Serial.println(settings.DaySubSec[i].Temp);
    Serial.println(settings.DaySubSec[i].Hum);
    Serial.println(settings.DaySubSec[i].ToDay);
    Serial.println(settings.DaySubSec[i].TimeBefore);
    Serial.println(settings.DaySubSec[i].TimeAfter);
    Serial.println("--------------------------------------");
  }
}

void loop() {


}
