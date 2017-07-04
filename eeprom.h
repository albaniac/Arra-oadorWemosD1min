#include <EEPROM.h>

//******************** EEPROM *******************//
// Endereços reservados na memória
uint8_t addr  = 6;    // a1
uint8_t addr1 = 7;    // a2
uint8_t addr2 = 8;    // a3
uint8_t addr3 = 9;    // tempoD1
uint8_t addr4 = 10;    // tempoD2
uint8_t addr5 = 11;    // tempoD3

// Funções para gerenciamento

void Save_Data() {
  EEPROM.write(addr,  (byte) a1);
  EEPROM.write(addr1, (byte) a2);
  EEPROM.write(addr2, (byte) a3);
  EEPROM.write(addr3, (byte) tempoD1);
  EEPROM.write(addr4, (byte) tempoD2);
  EEPROM.write(addr5, (byte) tempoD3);
  EEPROM.commit();
  Serial.println("*WifiRTC: Dados salvos na EEPROM");
}

void Read_Data() {
  a1 = EEPROM.read(addr);
  a2 = EEPROM.read(addr1);
  a3 = EEPROM.read(addr2);
  tempoD1 = EEPROM.read(addr3);
  tempoD2 = EEPROM.read(addr4);
  tempoD3 = EEPROM.read(addr5);
  Serial.println("*WifiRTC: Dados lidos da EEPROM");
}


//
void Eeprom() { //colocar no setup
  EEPROM.begin(512);
  Read_Data();
  delay(250);
}

void clearEeprom() {
  for (int i = 0; i <= 512; i++) {
    EEPROM.write(i, 0);
    EEPROM.end();
  }
}


