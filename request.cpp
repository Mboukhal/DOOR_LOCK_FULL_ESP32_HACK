#include "./request.hpp"

bool request(const String &endpoint, const String &token, const String &id_code) {

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["badge_id"] = id_code;
  jsonDoc["target_token"] = token;

  bool res = false;

  String payload;
  serializeJson(jsonDoc, payload);

  // Create HTTPClient object
  HTTPClient http;

  // Make POST request
  http.begin(endpoint);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == 200) {
    res = true;
  }

  // Close connection
  http.end();

  // Wait for some time before making the next request
  delay(1000);
  return res;
}