void SetDefaultDataInEEPROM()
{
  storeStruct_t SetDefaultEEPROM;
  Serial.println("Set Default EEPROM");
  EEPROM.begin(4095);
  EEPROM.get( cfgStart, SetDefaultEEPROM);
  EEPROM.end();
  settings = SetDefaultEEPROM;
}

void SaveEEPROM()
{
  Serial.println("saveEEPEM");
  EEPROM.begin(4095);
  EEPROM.put( cfgStart, settings );
  delay(200);
  EEPROM.commit();
  EEPROM.end();
}

void GetEEPROM()
{
  Serial.println("Loading config");
  EEPROM.begin(4095);
  EEPROM.get( cfgStart, load);
  EEPROM.end();
  // PrintEEPROM();
}

void PrintEEPROM()
{
  Serial.println(load.ssid);
  Serial.println(load.pass);
  Serial.println(load.StateFanIN1);
  Serial.println(load.StateFanIN2);
  Serial.println(load.StateFanOut1);
  Serial.println(load.StateFanOut2);
  Serial.println(load.StateFogging1);
  Serial.println(load.StateFogging2);
  Serial.println(load.StateHeater1);
  Serial.println(load.StateHeater2);
  Serial.println(load.StateHeater3);

  Serial.print("StateSystem : ");
  Serial.println(settings.StateSystem);

  Serial.println("Count 0");
  Serial.println(load.DaySubSec[0].DayCount);
  Serial.println(load.DaySubSec[0].Temp);
  Serial.println(load.DaySubSec[0].Hum);
  Serial.println(load.DaySubSec[0].ToDay);
  Serial.println(load.DaySubSec[0].TimeBefore);
  Serial.println(load.DaySubSec[0].TimeAfter);

  Serial.println("Count 1");
  Serial.println(load.DaySubSec[1].DayCount);
  Serial.println(load.DaySubSec[1].Temp);
  Serial.println(load.DaySubSec[1].Hum);
  Serial.println(load.DaySubSec[1].ToDay);
  Serial.println(load.DaySubSec[1].TimeBefore);
  Serial.println(load.DaySubSec[1].TimeAfter);

  Serial.println("Count 2");
  Serial.println(load.DaySubSec[2].DayCount);
  Serial.println(load.DaySubSec[2].Temp);
  Serial.println(load.DaySubSec[2].Hum);
  Serial.println(load.DaySubSec[2].ToDay);
  Serial.println(load.DaySubSec[2].TimeBefore);
  Serial.println(load.DaySubSec[2].TimeAfter);

  Serial.println("Count 3");
  Serial.println(load.DaySubSec[3].DayCount);
  Serial.println(load.DaySubSec[3].Temp);
  Serial.println(load.DaySubSec[3].Hum);
  Serial.println(load.DaySubSec[3].ToDay);
  Serial.println(load.DaySubSec[3].TimeBefore);
  Serial.println(load.DaySubSec[3].TimeAfter);

  Serial.println("Count 4");
  Serial.println(load.DaySubSec[4].DayCount);
  Serial.println(load.DaySubSec[4].Temp);
  Serial.println(load.DaySubSec[4].Hum);
  Serial.println(load.DaySubSec[4].ToDay);
  Serial.println(load.DaySubSec[4].TimeBefore);
  Serial.println(load.DaySubSec[4].TimeAfter);

  Serial.println("Count 5");
  Serial.println(load.DaySubSec[5].DayCount);
  Serial.println(load.DaySubSec[5].Temp);
  Serial.println(load.DaySubSec[5].Hum);
  Serial.println(load.DaySubSec[5].ToDay);
  Serial.println(load.DaySubSec[5].TimeBefore);
  Serial.println(load.DaySubSec[5].TimeAfter);

  Serial.println("Count 6");
  Serial.println(load.DaySubSec[6].DayCount);
  Serial.println(load.DaySubSec[6].Temp);
  Serial.println(load.DaySubSec[6].Hum);
  Serial.println(load.DaySubSec[6].ToDay);
  Serial.println(load.DaySubSec[6].TimeBefore);
  Serial.println(load.DaySubSec[6].TimeAfter);

  Serial.println("Count 7");
  Serial.println(load.DaySubSec[7].DayCount);
  Serial.println(load.DaySubSec[7].Temp);
  Serial.println(load.DaySubSec[7].Hum);
  Serial.println(load.DaySubSec[7].ToDay);
  Serial.println(load.DaySubSec[7].TimeBefore);
  Serial.println(load.DaySubSec[7].TimeAfter);
}
