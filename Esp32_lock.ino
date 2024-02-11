#include "./wifi_management.hpp"
#include "./config_page.hpp"

WifiLock WL;
ConfigPage CP;

void setup() {
  // Serial.begin(115200);

  WL.begin();
  CP.begin(&WL);

  WL.reset_auth_data();

  // Setup GPIO for LED
  pinMode(2, OUTPUT);
}

void loop() {

  // Handle client requests
  if (WL.Config_set) {
    if (WiFi.status() != WL_CONNECTED) {
      // WL.print_auth_data();
      WL.connect_to_wifi();
      delay(5000);
    }
  }
  else {
    CP.waitClient();
  }
}
