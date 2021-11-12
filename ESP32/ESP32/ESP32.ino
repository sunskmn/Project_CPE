#include <WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Nextion.h"
#include "DHT.h"
#include <RTClib.h>

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

//const char* ssid = "Xopterser";
//const char* password = "12345678";

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
storeStruct_t load;

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
    Serial.print("Attempting MQTT connection…");
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

  if (message == "GET") {
  }
  if (message == "LEDON") {
  }
  if (message == "LEDOFF") {
  }
  if (CheckTopic == "@msg/DataSys") {
    client.publish("@msg/alert", "Sent OK");
    Serial.println("Sent OK");
    for (int i = 0; i < 5; i++) {
      DataSYS[i] = Split(message, '/', i);
      Serial.println(DataSYS[i]);
    }
    /* .toInt();
        .toFloat();
        String text = "IOXhop";
      char tChar[50];
      text.toCharArray(tChar, 50);
    */
    for (int i = 0; i < 15; i++) {
      settings.DaySubSec[CountSYS].Temp = DataSYS[i].toFloat();
    }
    settings.DaySubSec[0].Temp = 0;
    settings.DaySubSec[0].Hum = 0;
    settings.DaySubSec[0].ToDay = 0;
    settings.DaySubSec[0].TimeBefore[8] = 0;
    settings.DaySubSec[0].TimeAfter[8] = 0;
  }
}
