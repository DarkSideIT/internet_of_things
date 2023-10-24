#include <PubSubClient.h>
#include "LedController.h"


LedController led_controller;

PubSubClient mqtt_client(wiFiClient);
bool mqtt_work = false;

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("There is message on topic ");
  Serial.print(topic);
  Serial.print(" Message is: ");

  for (int i = 0; i < length; i++) {
    Serial.print( (char) payload[i]);
  }
  
  if ((char)payload[0] == 'u') {
    led_controller.On();
  } else {
    led_controller.Off();
  }

  Serial.println("");
}

bool init_MQTT() {
  mqtt_client.setServer(mqtt_broker, mqtt_port); // connect to broker
  mqtt_client.setCallback(callback);
  while (!mqtt_client.connected()) {
    String client_id = "esp8266_" + wifi.id();
    if (mqtt_client.connect(client_id.c_str())) {
      Serial.println("MQTT client connected with id: " + client_id);
      mqtt_work = true;
    } else {
      Serial.println("MQTT client failed to connect");
      delay(500);
    }
  }
  mqtt_client.subscribe(topic.c_str());
  return true;
}