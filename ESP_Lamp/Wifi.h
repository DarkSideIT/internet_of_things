#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WiFiMulti.h"


struct ip_addr_my {
  int a;
  int b;
  int c;
  int d;

  ip_addr_my() : a(0), b(0), c(0), d(0) {}

  ip_addr_my(int aa, int bb, int cc, int dd) : a(aa), b(bb), c(cc), d(dd) {};

  ip_addr_my(const ip_addr_my &other) : a(other.a), b(other.b), c(other.c), d(other.d) {};

};

  WiFiClient wiFiClient;

class WiFiWorker{
  ESP8266WiFiMulti wiFiMulti;
  ip_addr_my ip;
  String ap_pass;
  String ap_ssid;

public:

  WiFiWorker(ip_addr_my new_ip, String pass, String ssid) {
    ip = new_ip;
    ap_pass = pass;
    ap_ssid = ssid;
  };

  String id() {
    int mac_len = WL_MAC_ADDR_LENGTH;
    uint8_t mac[mac_len];
    WiFi.softAPmacAddress(mac);
    String mac_id = String(mac[mac_len - 2], HEX) + String(mac[mac_len - 1], HEX);

    return mac_id;
  };

  bool start_AP_mode() {
    IPAddress ap_IP(ip.a, ip.b, ip.c, ip.d);
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(ap_IP, ap_IP, IPAddress(255, 255, 255, 0));
    WiFi.softAP((ap_ssid + id()).c_str(), ap_pass.c_str());
    Serial.println("WiFI started in AP mode " + ap_ssid + " " + id());

    return true;
  };

  bool start_client_mode(String ssid, String pass) {
    WiFi.disconnect();
    wiFiMulti.addAP(ssid.c_str(), pass.c_str());
    if (wiFiMulti.run() == WL_CONNECTED) {
      Serial.println("wifi is working");
    } else {
      Serial.println("wifi is'n working");
    }
    return wiFiMulti.run() == WL_CONNECTED;
  }

  // bool stop_client_mode() {
  // }
};

WiFiWorker wifi(ip_addr_my(192, 168, 4, 1), AP_PASSWORD, AP_NAME);


// String ip = "IP not set";

// String id() {
//   int mac_len = WL_MAC_ADDR_LENGTH;
//   uint8_t mac[mac_len];
//   WiFi.softAPmacAddress(mac);
//   String mac_id = String(mac[mac_len - 2], HEX) + String(mac[mac_len - 1], HEX);

//   return mac_id;
// }


// bool start_AP_mode() {
//   IPAddress ap_IP(192, 168, 4, 1);
//   WiFi.disconnect();
//   WiFi.mode(WIFI_AP);
//   WiFi.softAPConfig(ap_IP, ap_IP, IPAddress(255, 255, 255, 0));
//   WiFi.softAP((AP_NAME + id()).c_str(), AP_PASSWORD.c_str());
//   Serial.println("WiFI started in AP mode " + AP_NAME + " " + id());

//   return true;
// }