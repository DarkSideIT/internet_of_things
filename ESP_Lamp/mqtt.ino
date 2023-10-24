#include "Config.h"
#include "Wifi.h"
#include "Broker.h"
#include "Server.h"



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("");
  wifi.start_AP_mode();
  server_init();
}

void loop() {
  server.handleClient();
  if (mqtt_work) {
    mqtt_client.loop();
  }

}
