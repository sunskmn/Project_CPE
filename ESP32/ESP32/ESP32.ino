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
  } DaySubSec[15];
};

struct Str {
  String Today;
  String TimeBefore;
  String TimeAfter;
} Count[7];

int Today[7][3];
int TimeBefore[7][3];
int TimeAfter[7][3];

String dataSSID[14];
String SelectSSID;

//const char* ssid = "Xopterser";
//const char* password = "12345678";

const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "623c49cf-ffb3-43b8-aa3c-663811176ee3";
const char* mqtt_username = "yjjEhE6dP3HkFhUbwf49NgKyg7fSxW31";
const char* mqtt_password = "j6UBG*lcCe*y5f~5-4lo_XaB665Xxgll";

char msg[100];

storeStruct_t settings;
storeStruct_t load;

WiFiClient espClient;
PubSubClient client(espClient);
RTC_DS1307 myRTC;
DateTime nowTime;

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
      client.subscribe("@msg/ReceivedIonic");
      client.subscribe("@msg/DataSys");

      client.subscribe("@msg/SetDayStart");
      client.subscribe("@msg/SetDayEnd");
      client.subscribe("@msg/SetTimeStart");
      client.subscribe("@msg/SetTimeEnd");
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
  WiFi.begin(load.ssid, load.pass);
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
  client.loop();

  if (!client.connected()) {
    reconnect();
  }

  // Send data from ESP32 to App Android
  String data = "/" + String(random(0, 100)) + "/" + String(random(0, 100));
  data.toCharArray(msg, (data.length() + 1));
  client.publish("@msg/led", msg);

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

  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  String AddressTopic;
  String DataSetSystem[5];
  
  // รับ Topic
  for (int i = 0; i < length; i++) {
    AddressTopic += topic[i];
  }

  // รับ Message
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  
  Serial.print("Message arrive [");
  Serial.print(topic);
  Serial.print("]");
  Serial.print("IN : ");
  Serial.println(message);

  if (AddressTopic == "@msg/DataSys") {
    Serial.println("Sent data");
    for (int i = 0; i <= 4; i++) {
      DataSetSystem[i] = Split(message, '/', i);
      load.DaySubSec[0].Temp = 0;
      load.DaySubSec[0].Hum = 0;
      DataSetSystem[2].toCharArray(load.DaySubSec[0].ToDay, 10);
      DataSetSystem[3].toCharArray(load.DaySubSec[0].TimeBefore, 8);
      DataSetSystem[4].toCharArray(load.DaySubSec[0].TimeAfter, 8);
      Serial.println(DataSetSystem[i]);
    }
  }
}
/*
char ToDay[11];
    char TimeBefore[10];
    char TimeAfter[10];
    */
/*
      utoa(int(Temp_Setting), buffer_temp, 10); // แปลง int ให้เป็น char และแสดงผลออกมาโดยหาขนาดของ string
*/
