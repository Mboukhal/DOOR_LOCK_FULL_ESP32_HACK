#pragma once
#include <EEPROM.h>


#define MAX_BUFFER_SIZE 512

void write_str(const String &str, uint8_t start_address);
void write_str(const String &str);
String read_str(uint8_t start_address);
String read_str();