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
