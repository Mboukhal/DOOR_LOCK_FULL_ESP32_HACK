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
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);

    // // Read the response
    // String response = http.getString();
    // Serial.println("Server response: " + response);

    // // Parse the JSON response if needed
    // // JsonObject root = jsonDoc.parseObject(response);
    // // const char* message = root["message"];
    res = true;
  }
  // else {
  //   Serial.print("HTTP POST request failed, error: ");
  //   Serial.println(httpResponseCode);
  // }

  // Close connection
  http.end();

  // Wait for some time before making the next request
  delay(1000);
  return res;
}