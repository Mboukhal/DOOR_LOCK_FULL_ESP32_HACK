#include <WiFi.h>
#include "wifi_management.hpp"


#define SSID_AP "1337-DOORLOCK-CONFIG"
#define PASSWORD_AP "+@@1337@@+"


class ConfigPage {
  private:
    String header;
    String ssid;
    String password;
    String endpoint;
    String token;
    WifiLock *WL;
    
  public:
    void begin(WifiLock *WL);
    void waitClient(void);
    void handleClient(WiFiClient client);
    void handleFormSubmission();
    void displayHtmlForm(WiFiClient client);

};