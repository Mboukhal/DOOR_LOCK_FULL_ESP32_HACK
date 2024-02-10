#include "./wifi_management.hpp"
#include "./config_page.hpp"

WifiLock WL;
ConfigPage CP;

void setup() {
  Serial.begin(115200);

  WL.begin();
  CP.begin(&WL);

  // Setup GPIO for LED
  pinMode(2, OUTPUT);

}

void loop() {
  // Handle client requests
  CP.waitClient();
}



// void setup() {
//   Serial.begin(115200);
  

//   // WL.reset_auth_data();

//   // WL.print_auth_data();
  
//   Serial.println("---------------------------");
  

//   WL.print_auth_data();

//   Serial.println("ESP32 started!");


// }