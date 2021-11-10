#include <EEPROM.h>

#define cfgStart 0

struct storeStruct_t {
  char ssid[10] = "Xopterser";
  char pass[10] = "12345678";

  bool StateSystem;

  uint32_t StateFanIN1;
  uint32_t StateFanIN2;
  uint32_t StateFanOut1;
  uint32_t StateFanOut2;
  uint32_t StateFogging1;
  uint32_t StateFogging2;
  uint32_t StateHeater1;
  uint32_t StateHeater2;
  uint32_t StateHeater3;

  int CountCall = 0;
  
  struct SetSystem {
    int DayCount;
    bool State;
    float Temp;
    int Hum;
    char ToDay[11];
    char TimeBefore[10];
    char TimeAfter[10];
  } DaySubSec[15];
};

struct Str {
  String Today;
  String TimeBefore;
  String TimeAfter;
} Count[7];

storeStruct_t settings;
storeStruct_t load;

void setup() {
  Serial.begin(115200);
  SetDefaultDataInEEPROM();
}

void loop() {
  // put your main code here, to run repeatedly:

}
