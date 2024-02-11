#pragma once


#include <HTTPClient.h>
#include <ArduinoJson.h>

bool request(const String &endpoint, const String &token, const String &id_code);