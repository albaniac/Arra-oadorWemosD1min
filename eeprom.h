#include <EEPROM.h>

//******************** EEPROM *******************//
// Endereços reservados na memória
uint8_t addr  = 6;    // a1
uint8_t addr1 = 7;    // a2
uint8_t addr2 = 8;    // a3
uint8_t addr3 = 9;    // delay1
uint8_t addr4 = 10;    // delay2
uint8_t addr5 = 11;    // delay3

// Funções para gerenciamento

void Save_Data() {
  EEPROM.write(addr,  (byte) a1);
  EEPROM.write(addr1, (byte) a2);
  EEPROM.write(addr2, (byte) a3);
  EEPROM.write(addr3, (byte) delay1);
  EEPROM.write(addr4, (byte) delay2);
  EEPROM.write(addr5, (byte) delay3);
  EEPROM.commit();
  Serial.println("*WifiRTC: Dados salvos na EEPROM");
}

void Read_Data() {
  a1 = EEPROM.read(addr);
  a2 = EEPROM.read(addr1);
  a3 = EEPROM.read(addr2);
  delay1 = EEPROM.read(addr3);
  delay2 = EEPROM.read(addr4);
  delay3 = EEPROM.read(addr5);
  Serial.println("*WifiRTC: Dados lidos da EEPROM");
}


//
void Eeprom() { //colocar no setup
  EEPROM.begin(256);
  Read_Data();
  delay(250);
}

void clearEeprom() {
  for (int i = 0; i <= 255; i++) {
    EEPROM.write(i, 0);
    EEPROM.end();
  }
}


