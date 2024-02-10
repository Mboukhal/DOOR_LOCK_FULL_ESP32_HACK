#include "wifi_management.hpp"

WifiLock WL;


void setup() {
  Serial.begin(115200);
  
  WL.begin();

  WL.reset_auth_data();

  WL.print_auth_data();
  
  Serial.println("---------------------------");
  
  WL.set_auth_data(
    "ssid",
    "password",
    "endpoint",
    "token"
  );
  WL.print_auth_data();
  WL.reset_auth_data();

  Serial.println("ESP32 started!");


}


void loop() {

}
