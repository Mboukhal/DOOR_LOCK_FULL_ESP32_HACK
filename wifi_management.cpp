#include "wifi_management.hpp"

void WifiLock::begin(void) {
  EEPROM.begin(500);
  this->Config_set = this->valid_config();
}

void WifiLock::get_auth_data() {

  int address = 0; 
  this->authData.ssid = read_str(address);
  address += SSID_SIZE + 1;
  this->authData.password = read_str(address);
  address += PASSWORD_SIZE + 1;
  this->authData.endpoint = read_str(address);
  address += ENDPOINT_SIZE + 1;
  this->authData.token = read_str(address);
}

void WifiLock::set_auth_data(
  const String &ssid,
  const String &password,
  const String &endpoint,
  const String &token) {

  this->authData.ssid = ssid;
  this->authData.password = password;
  this->authData.endpoint = endpoint;
  this->authData.token = token;
  this->set_auth_data();
  this->Config_set = this->valid_config();

  // if (this->Config_set)
  //    WiFi.mode(WIFI_AP);

}

void WifiLock::set_auth_data() {

  int address = 0; 
  write_str(this->authData.ssid, address);
  address += SSID_SIZE + 1;
  write_str(this->authData.password, address);
  address += PASSWORD_SIZE + 1;
  write_str(this->authData.endpoint, address);
  address += ENDPOINT_SIZE + 1;
  write_str(this->authData.token, address);
}


void WifiLock::reset_auth_data() {
  this->set_auth_data("\0", "\0", "\0", "\0");
  this->Config_set = false;
}

void WifiLock::print_auth_data() {

  this->get_auth_data();
  int address = 0;
  Serial.println("SSID: [" + this->authData.ssid + "]");
  address += SSID_SIZE + 1;
  Serial.println("PASSWORD: [" + this->authData.password + "]");
  address += PASSWORD_SIZE + 1;
  Serial.println("ENDPOINT: [" + this->authData.endpoint + "]");
  address += ENDPOINT_SIZE + 1;
  Serial.println("TOKEN: [" + this->authData.token + "]");
}


bool WifiLock::valid_config(void) {

  this->get_auth_data();
  if (this->authData.ssid != "\0" &&
    this->authData.endpoint != "\0" &&
    this->authData.token != "\0"
  )
    return true;
  return false;
}


void WifiLock::connect_to_wifi(void) {

  this->get_auth_data();

  WiFi.disconnect();
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(this->authData.ssid, this->authData.password);
  // Serial.println("ssid: [" + this->authData.ssid + "], password: [" + this->authData.password + "]");

  // Serial.println("\nConnected to the WiFi network");
  // Serial.print("Local ESP32 IP: ");
  // Serial.println(WiFi.localIP());
}
