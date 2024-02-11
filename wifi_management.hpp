#pragma once
#include "rw_eeprom.hpp"
#include <WiFi.h>

struct AUTH_DATA {
  String ssid;
  String password;
  String endpoint;
  String token;
};


#define SSID_SIZE 50
#define PASSWORD_SIZE 50
#define ENDPOINT_SIZE 150
#define TOKEN_SIZE 150

class WifiLock {

  private:
    AUTH_DATA authData;

  public:
    void begin(void);
    void get_auth_data(void);
    void set_auth_data(void);
    void print_auth_data(void);
    void reset_auth_data(void);
    bool valid_config(void);
    void connect_to_wifi(void);
    bool Config_set = false;
    String get_endpoint(void);
    String get_token(void);
    void set_auth_data(const String &ssid,
                        const String &password,
                        const String &endpoint,
                        const String &token);


};

// WifiLock WL;

