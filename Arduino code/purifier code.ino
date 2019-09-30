#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <ESP8266wifi.h>
#include <PubSubClient.h>

#define tdspin A0
#define deepsleep  30

#define wifi_ssid "vigneshx"
#define wifi_password "vigneshx"

#define mqtt_server "m14.cloudmqtt.com"
#define mqtt_user "oemdvjkd"
#define mqtt_password "HzbChqKbMwML"
#define tdstopic "/TDS"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 13562);
  pinMode(tdspin,INPUT);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("\nCONNECTED");
    } else {
      Serial.print("Failed\tState:");
      Serial.print(client.state());
      Serial.println("...try again in 5 seconds");
      delay(5000);
    }
  }
}

bool checkBound(float newValue,float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}
long lastmsg = 0;
long now;
float tds = 0;
float diff = 1;

void loop() {
  if (!client.connected()) {
    connect();
  }
  client.loop();
  
  float newtds =analogRead(tdspin);
  float probe = newtds * (5.0 / 1023.0);
  if(probe>=0.1){
    if (checkBound(newtds, tds, diff)) {
      tds = newtds;
      Serial.println("TDS value: ");
      Serial.print(String(tds).c_str());
      client.publish(tdstopic, String(tds).c_str(), true);
    }else{
      Serial.print("\nTDS value: ");
      Serial.println(String(tds).c_str());
    }
    
    Serial.print("\nClosing MQTT connection...");
    client.disconnect();

    Serial.print("\nClosing Wi-Fi Connection...");
    WiFi.disconnect();
    
    Serial.print("\n\nEnter in Deepsleep mode for ");
    Serial.print(deepsleep);
    Serial.print(" seconds...\n");
    ESP.deepSleep(deepsleep * 1000000, WAKE_RF_DEFAULT);
    delay(100);
 
  }else{ 
      Serial.print("\n\nPlease insert probe...");
      client.publish(tdstopic, "Insert Probe", true);
      while(probe<=0.1){
        now = millis();
        if(now - lastmsg > 10000){
          lastmsg = now;
          Serial.print("\n\nPlease insert Probe...");
          client.publish(tdstopic, "Insert Probe", true);
        }
        newtds =analogRead(tdspin);
        probe = newtds * (5.0 / 1023.0);
        delay(100);
      }
   }
}
