#include <WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Nextion.h"
#include "DHT.h"
#include <RTClib.h>

#define cfgStart 0

struct storeStruct_t {
  char ssid[10] = "Motuthree";
  char pass[10] = "08123456";
   int CountSYS;
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

const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "623c49cf-ffb3-43b8-aa3c-663811176ee3";
const char* mqtt_username = "yjjEhE6dP3HkFhUbwf49NgKyg7fSxW31";
const char* mqtt_password = "j6UBG*lcCe*y5f~5-4lo_XaB665Xxgll";
char msg[100];

WiFiClient espClient;
PubSubClient client(espClient);
RTC_DS1307 myRTC;
DateTime nowTime;

storeStruct_t settings;

String Split(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connectionâ€¦");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      //client.subscribe("@msg/led");
      client.subscribe("@msg/DataSys");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  SetDefaultDataInEEPROM();

  // Connect WIFI
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(settings.ssid, settings.pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //myRTC.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //myRTC.adjust(DateTime(2020, 12, 21, 12, 0, 0));
  pinMode(2, OUTPUT);

  for (int i = 0 ; i < 16; i++) {
    Serial.println(settings.DaySubSec[i].Temp);
    Serial.println(settings.DaySubSec[i].Hum);
    Serial.println(settings.DaySubSec[i].ToDay);
    Serial.println(settings.DaySubSec[i].TimeBefore);
    Serial.println(settings.DaySubSec[i].TimeAfter);
    Serial.println("--------------------------------------");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*
    // Show Time
    nowTime = myRTC.now();
    Serial.print("Now date/time :: ");
    Serial.print(nowTime.hour());
    Serial.print(":");
    Serial.print(nowTime.minute());
    Serial.print(":");
    Serial.print(nowTime.second());
    Serial.print(" :: ");
    Serial.print(nowTime.day());
    Serial.print("/");
    Serial.print(nowTime.month());
    Serial.print("/");
    Serial.print(nowTime.year());
    Serial.println();
  */

  // Sent Data Random
  String data = "/" + String(random(0, 100)) + "/" + String(random(0, 100));
  data.toCharArray(msg, (data.length() + 1));
  client.publish("@msg/led", msg);
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  String CheckTopic;
  String DataSYS[5];

  for (int i = 0; i < length; i++) {
    CheckTopic += topic[i];
  }
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }

  Serial.print("Message arrive [");
  Serial.print(topic);
  Serial.print("]");
  Serial.print("IN : ");
  Serial.println(message);

  if (CheckTopic == "@msg/DataSys" && settings.CountSYS < 15) {
    Serial.println("Sent OK");
    for (int i = 0; i < 5; i++) {
      DataSYS[i] = Split(message, '/', i);
      Serial.println(DataSYS[i]);
    }
    if (settings.CountSYS < 16) {
      settings.CountSYS++;
      Serial.println("CountSYS : " + String(settings.CountSYS));
    }
    settings.DaySubSec[settings.CountSYS].Temp = DataSYS[0].toFloat();
    settings.DaySubSec[settings.CountSYS].Hum = DataSYS[1].toInt();
    DataSYS[2].toCharArray(settings.DaySubSec[settings.CountSYS].ToDay, 10);
    DataSYS[3].toCharArray(settings.DaySubSec[settings.CountSYS].TimeBefore, 8);
    DataSYS[4].toCharArray(settings.DaySubSec[settings.CountSYS].TimeAfter, 8);
    SaveEEPROM();
    client.publish("@msg/alert", "Sent OK");
  }
}
