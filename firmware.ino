/*  Simple Web Server for ESP8266-12E by Tiago 
   alterado do exemplo de NattyFido 2015
   www.nattyfido.co.uk  (shameless plug!)
   https://esp8266.ru/forum/threads/umnyj-dom-dlja-chajnika.1581/page-9#post-22893
*/

#include <ESP8266WiFi.h>
#include <Ticker.h>       //https://github.com/esp8266/Arduino/tree/master/libraries/Ticker
#include "OTA.h" // executa a aba OTA
#include "server.h"       // recupera dados da aba server

/******************** LibSimpleTIMER *******************//
#include <SimpleTimer.h>// substitui o delay que trava funções do esp8266
SimpleTimer timer;

//******************** Conexão Wifi*******************//
IPAddress ip(192, 168, 1, 101); //NodeMCU static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "SuaSSID";                //  SSID of LAN/WLAN
const char* password = "SuaSenha";           //  password

//******************** WTD *******************//

Ticker secondtick;
volatile int watchdogCount = 0;

void restart(){
ESP.restart();//
}
void reset_config(void) {
 // Serial.println("*WifiRTC: O ESP ira resetar agora");
  delay(1500);
  ESP.reset();
}

void ISRWatchdog() {
  watchdogCount++;
  if (watchdogCount > 70) {
 //   Serial.println("*WifiRTC: Watchdog bite! Reiniciando");
    ESP.reset();
  }
}

//******************** Setup *******************//
void setup() {
  WiFi.persistent(false);
  Serial.begin(115200);                        //  start serial for debug
  delayMicroseconds(250);

  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D5, OUTPUT);                       //  all outputs for LEDs
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
 // pinMode(led3, OUTPUT);
  digitalWrite(BUILTIN_LED, 1);                       //  all LEDs off to start
  digitalWrite(D5, 0);
  digitalWrite(D7, 0);
  digitalWrite(D8, 0);
  
  //Define conexão direta
  WiFi.config(ip, gateway, subnet);// ip fixo
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED, 0);
    delay(500);
    digitalWrite(BUILTIN_LED, 1);
    Serial.print(".");
  }

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println(F("*WifiRTC: Falha na conexão! Reiniciando..."));
    timer.setTimeout((5000L), restart); // aciona depois de X segundos
  }

  Serial.println(F("*WifiRTC: Conectado"));
  server.begin();

  OTA(); // executa a função OTA na setup
  Eeprom();//recupera os dados da eeprom
  ntp(); //recupera valores do horaNTP
  
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

//******************** Loop *******************//
void loop() {
  watchdogCount = 0;        //Zera Watchdog
  webpage();                //carrega o webserver
  TimedAction(); // verifica que o o botão auto esta ativado
  ArduinoOTA.handle(); // aciona arduino OTA colar no loop

}
