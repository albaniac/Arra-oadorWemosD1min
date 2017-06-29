/*  Simple Web Server for ESP8266-12E by Tiago 
   alterado do exemplo de NattyFido 2015
   www.nattyfido.co.uk  (shameless plug!)
   https://esp8266.ru/forum/threads/umnyj-dom-dlja-chajnika.1581/page-9#post-22893
*/

#include <ESP8266WiFi.h>
#include <Ticker.h>       //https://github.com/esp8266/Arduino/tree/master/libraries/Ticker
#include "server.h"  // recupera dados da aba server

//******************** Conexão Wifi*******************//
IPAddress ip(192, 168, 1, 101); //NodeMCU static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "SuaSSID";                //  SSID of LAN/WLAN
const char* password = "SuaSenha";           //  password

//******************** WTD *******************//

Ticker secondtick;
volatile int watchdogCount = 0;

void ISRWatchdog() {
  watchdogCount++;
  if (watchdogCount > 100) {
    Serial.println("Watchdog bite!");
    //ESP.reset();
    ESP.restart();//
  }
}
//******************** Setup *******************//
void setup() {
  WiFi.persistent(false);
  Serial.begin(115200);                        //  start serial for debug
  delayMicroseconds(250);

  pinMode(led0, OUTPUT);                       //  all outputs for LEDs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led0, 0);                       //  all LEDs off to start
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
  digitalWrite(led3, 0);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);                    //  connect to WiFi network
  WiFi.config(ip, gateway, subnet);// ip fixo

  while (WiFi.status() != WL_CONNECTED) {        //  wait until connected
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();                                // Start the server
  Serial.println("Server started");
  Serial.println(WiFi.localIP());                // Print the servers IP address

  Eeprom();//recupera os dados da eeprom
  ntp(); //recupera valores do horaNTP
  secondtick.attach(1, ISRWatchdog);
}

//******************** Loop *******************//
void loop() {
  clientserver(); // carrega o webserver
}
