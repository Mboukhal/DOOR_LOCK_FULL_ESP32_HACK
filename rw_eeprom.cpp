#include "rw_eeprom.hpp"


void write_str(const String &str, uint8_t start_address){
  
	for(int i = start_address, j = 0; i < (str.length() + start_address); i++, j++){
    
      EEPROM.write(i, str[j]);
      // Serial.println("Write: \"" + String(str[j]) + "\", address: " + String(i));
  }
  EEPROM.write(start_address + str.length(), '\0');
  // EEPROM.commit();
}

void write_str(const String &str){
  write_str(str, 0);
}

String read_str(){
  return read_str(0);
}

String read_str(uint8_t start_address){
  
  char str[MAX_BUFFER_SIZE];

	for(int i = start_address, j = 0; i <= MAX_BUFFER_SIZE; i++, j++){
	
		str[j] = EEPROM.read(i);
    // Serial.println("Read: \"" + String(str[j]) + "\", address: " + String(i));
    if (str[j] == '\0')
      break;
	}
  return String(str);
}
