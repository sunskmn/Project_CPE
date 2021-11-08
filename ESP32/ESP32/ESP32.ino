#include <WiFi.h>
#include <PubSubClient.h>
#include "Nextion.h"
#include "DHT.h"
#include <Wire.h>
#include <RTClib.h>

const char* ssid = "Xopterser";
const char* password = "12345678";

const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "623c49cf-ffb3-43b8-aa3c-663811176ee3";
const char* mqtt_username = "yjjEhE6dP3HkFhUbwf49NgKyg7fSxW31";
const char* mqtt_password = "j6UBG*lcCe*y5f~5-4lo_XaB665Xxgll";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[100];

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
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
}

void loop() {
  client.loop();
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("@msg/led");
      client.subscribe("@msg/temp");
      client.subscribe("@msg/hum");

      client.subscribe("@msg/SetDayStart");
      client.subscribe("@msg/SetDayEnd");
      client.subscribe("@msg/SetTimeStart");
      client.subscribe("@msg/SetTimeEnd");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
  String data = "/" + String(random(0, 100)) + "/" + String(random(0, 100));
  data.toCharArray(msg, (data.length() + 1));
  client.publish("@msg/led", msg);
  delay(2000);
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrive [");
  Serial.print(topic);
  Serial.print("]");

  String message;
  String CheckTopic;
  float float_massage;

  for (int i = 0; i < 9; i++) {
    CheckTopic += topic[i];
  }

  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }

  float_massage = message.toFloat();

  Serial.print("IN : ");
  Serial.println(message);

  if (message == "GET") {
    /*
      //client.publish("@msg/led", "LEDON");
      Serial.println("Send !");
      return;
    */
  }
  if (message == "LEDON") {
    /*
      digitalWrite(2, 1);
      //Serial.println(message);
    */
  }
  if (message == "LEDOFF") {
    /*
      digitalWrite(2, 0);
      //Serial.println(message);
    */
  }
  if (CheckTopic == "@msg/temp") {
    /*
      Temp_Setting = float_massage;
      utoa(int(Temp_Setting), buffer_temp, 10);
      Serial.print("Temp_Setting : ");
      Serial.println(Temp_Setting);
      Get_Value = true;
    */
  }
  if (CheckTopic == "@msg/hum") {
    /*
      Hum_Setting = float_massage;
      utoa(int(Hum_Setting), buffer_hum, 10);
      Serial.print("Hum_Setting : ");
      Serial.println(Hum_Setting);
      Get_Value = true;
    */
  }
  /*
    if (Get_Value == true) {
    GoToPage4.show();
    SetPage = 1;
    SetStringNULL_1.setText("Temp :");
    SetStringNULL_2.setText("Hum :");
    SetValueNULL_1.setText(buffer_temp);
    SetValueNULL_2.setText(buffer_hum);
    Serial.print("buffer_temp");
    Serial.println(buffer_temp);
    Serial.print("buffer_hum");
    Serial.println(buffer_hum);
    Get_Value = false;
    }
  */
}
