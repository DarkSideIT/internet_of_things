#include <ESP8266WebServer.h>

ESP8266WebServer server(WEB_SERVER_PORT);


void handle_root() {
  String page_code = "<form action=\"\/post\" method=\"post\"><input type=\"text\" name=\"ssid\" placeholder=\"SSID\"><input type=\"text\" name=\"pass\" placeholder=\"Password\"><input type=\"submit\" value=\"Submit\"><\/form>";

  server.send(200,
              "text/html",
              page_code);
}

void handle_post() {
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");
  Serial.println(ssid + " " + pass);
  bool is_work = wifi.start_client_mode(ssid, pass);
  if (is_work) {
    init_MQTT();
    server.send(200, "text/plain", ssid + " " + pass + " work:)");
  } else {
    server.send(400, "text/plain", ssid + " " + pass + " don't work");
  }
  
}

void handle_led(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handle_not_found() {
  server.send(404, "text/html", "404: check URL");
}


void server_init() {
  server.on("/", HTTP_GET, handle_root);
  server.on("/LED", HTTP_POST, handle_led);
  server.on("/post", HTTP_POST, handle_post);
  server.onNotFound(handle_not_found);

  server.begin();
  Serial.print("Server started on port ");
  Serial.println(WEB_SERVER_PORT);
}