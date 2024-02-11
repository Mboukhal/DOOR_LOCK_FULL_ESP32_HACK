// #define LEDS 16

#include "./wifi_management.hpp"
#include "./config_page.hpp"
#include "./request.hpp"

#include <Wiegand.h>

WIEGAND wg;
WifiLock WL;
ConfigPage CP;

#define RESET 26
#define LEDS 25
#define SWITCH 27
#define BUZZER 14

#define WD0 33
#define WD1 32

void reset(void);
void badge_code(void);
void wifi_manager(void);


void setup() {
  // Serial.begin(115200);

  WL.begin();
  CP.begin(&WL);

  // WL.reset_auth_data();

  pinMode(LEDS, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RESET, INPUT);

  wg.begin(WD0, WD1);
}



void loop() {

  badge_code();
  wifi_manager();
}

void wifi_manager(void) {

  if (WL.Config_set) {
    if (digitalRead(RESET) == 0) {
      reset();
    } else {
      if (WiFi.status() == WL_CONNECTED) {
        return;
      }
      else
      {
        WL.connect_to_wifi();
        WL.print_auth_data();
        while(WiFi.status() != WL_CONNECTED){
            if (digitalRead(RESET) == 0) {
              reset();
              return;
            } 
            digitalWrite(LEDS, HIGH);
            delay(50);
            digitalWrite(LEDS, LOW);
            delay(50);
        }
        // Serial.println("\nConnected to the WiFi network");
        // Serial.print("Local ESP32 IP: ");
        // Serial.println(WiFi.localIP());
      }
    }
  }
  else {
    CP.waitClient();
    digitalWrite(LEDS, HIGH);
    delay(200);
    digitalWrite(LEDS, LOW);
    delay(200);
  }
}

void beep(int note, int duration) {
  tone(BUZZER, note, duration);
  delay(duration);
}


void playSuccessSound() {
  // Beep twice quickly for success
  beep(523, 200);
  delay(50);
  beep(740, 200);
}

void playFailSound() {
  // Beep three times quickly for failure
  beep(220, 200);
  delay(40);
  beep(196, 200);
  delay(40);
  beep(175, 200);
}

void badge_code(void) {

  if(wg.available()) {

    unsigned long code = wg.getCode();
		// Serial.print("Badge Code: ");
		// Serial.println(code);

    if (request(WL.get_endpoint(), WL.get_token(), String(code))) {

      playSuccessSound();
      digitalWrite(LEDS, HIGH);
      digitalWrite(SWITCH, HIGH);
      
      // song();
      delay(2000);

      digitalWrite(SWITCH, LOW);
      digitalWrite(LEDS, LOW);
      // delay(2000);
    } else {
      playFailSound();
    }
    while(wg.available()) {
      code = wg.getCode();
    }
	}
}

void reset(void) {

  WL.reset_auth_data();
  WiFi.disconnect();
  CP.begin();
}