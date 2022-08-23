//Dikarenakan plan Free (Cute Cat) dari MQTT sudah tidak tersedia maka disini saya hanya membuat konsep sederhana untuk publish dan subscribe ESP32 dan MQTT

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

char* ssid = "ssidwifi";
char* password = "passwordwifi";

char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int pot = 15;
int ADC_VALUE = 0;
int voltage_value = 0;

#define ldrsensor 36

#ifdef __cplusplus
extern "C"{
  
  #endif

  uint8_t temperature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temperature_sens_read();

void setup_wifi(){
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void reconnect(){
  while (!client.connected()){
    if (client.connect("ESP32Client")){

      char value_adc = client.subscribe("ESP32/ADC");
      char value_temp = client.subscribe("ESP32/TEMP");
      char value_sensor = client.subscribe("ESP32/SENSOR");
      Serial.print(value_adc);
      Serial.print(value_temp);
      Serial.print(value_sensor);
    }
  }
}

void loop(){
  if (!client.connected()){
    reconnect();
  }
  client.loop();
  long now = nillis();
  if (now - lastMsg > 5000){
    lastMsg = now;

    char adcString[8];
    ADC_VALUE = analogRead(pot);
    voltage_value = (ADC_VALUE * 3.3);
    dtostrf(voltage_value, 1, 2, adcString);
    client.publish("ESP/ADC", adcString);
    char tempString[8];
    int temp = ((temperature_sens_read() - 32)/1.8);
    dtostrf(temp, 1, 2, tempString);
    client.publish("ESP/TEMP", tempString);
    char sensorString[8];
    int ldrValue = analogRead(ldrsensor);
    dtostrf(ldrValue, 1, 2, sensorString);
    client.publish("ESP/SENSOR", sensorString);
  }
}
  
}
