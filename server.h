//monta a pagina do webserver
#include "horaNTP.h" // busca hora NTP
#include "runanyway.h"

//******************** botões comandos *******************//
uint8_t status_gpio = 0;      // Define condição para GPIO
uint8_t status_auto;          // Define status do botão auto

//******************** Função Temporizada *******************//


int  horaLiga = 7, horaLiga1 = 12,  horaLiga2 = 18, minutoLiga = 10;
//uint8_t pin1 = D1, pin2 = D2, pin3 = D3;
int tempoD1, tempoD2, tempoD3;

String time1() {
  char time1[10];
  sprintf( time1, "%d",  (tempoD1 ));
  return time1;
}

String time2() {
  char time2[10];
  sprintf( time2, "%d",  (tempoD2));
  return time2;
}

String time3() {
  char time3[10];
  sprintf( time3, "%d",  (tempoD3));
  return time3;
}

String time4() {
  char time1[10];
  sprintf( time1, "%d",  minutoLiga);
  return time1;
}

String time5() {
  char time1[10];
  sprintf( time1, "%d",  horaLiga);
  return time1;
}
String horaligar () {//
  char horaligar[30];
  sprintf( horaligar, "%02d:%02d ", horaLiga, minutoLiga); //
  return  horaligar;
}
String horaligar1 () {//
  char horaligar1[30];
  sprintf( horaligar1, ",%02d:%02d ", horaLiga1, minutoLiga); //
  return horaligar1;
}
String horaligar2 () {//
  char horaligar2[30];
  sprintf( horaligar2, ",%02d:%02d ", horaLiga2, minutoLiga); //
  return horaligar2;
}


// ------------------------------ - HTML------------------------ -


void TimedAction() {  //executa

  if (status_auto == true) {
    if (((int(hour()) == (int)horaLiga) || (int(hour()) == (int)horaLiga1) || (int(hour()) == (int)horaLiga2)) && int(minute()) == (int)minutoLiga && (second() <= 2)) {
      status_gpio = 1;
      digitalWrite(BUILTIN_LED, 1);                       //  all LEDs off to start
      runAndWait(D5, status_gpio, tempoD1);
      runAndWait(D7, status_gpio, tempoD2);
      runAndWait(D8, status_gpio, tempoD3);
      status_gpio = 0;
    }
  }
   if (status_auto == true) {
    if ((int(hour()) == 22) && int(minute()) == (int)minutoLiga && (second() <= 2)) {
      status_gpio = 1;
      digitalWrite(BUILTIN_LED, 1);                       //  all LEDs off to start
      runAndWait(D5, status_gpio, tempoD1/2);
      runAndWait(D7, status_gpio, tempoD2/2);
      runAndWait(D8, status_gpio, tempoD3/2);
      status_gpio = 0;
    }
  }
}


#include "eeprom.h"

// ------------------------------ - HTML------------------------ -

WiFiServer server(80);

String HTMLHeader() {
  String h = "HTTP/1.1 200 OK\r\n";
  h += "Content-Type: text/html\r\n\r\n";
  h += "<!DOCTYPE HTML><html><head><META HTTP-EQUIV='Refresh' CONTENT='10;URL=/'><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  h += "<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link><link rel=\"stylesheet\" href=\"http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.6.3/css/font-awesome.min.css\"><center><body>\n";
  h += "<link rel=\"stylesheet\" href=\"http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.6.3/css/font-awesome.min.css\">";
  h += "<title>WebServer ESP8266</title>";
  h += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;}</style>";
  h += "</head>";
  h += "<body><div class=\"panel panel-primary\">";
  h += "<div class=\"panel-heading\"><h3>Simple Webserver</h3></div>";
  h += "<div class=\"panel-body\">";
  h += "<div id=\"txt\" style=\"font-weight:bold;\"></div>";
  return h;
}

String HTMLFooter() {                            //  standard HTML footer
  String f = "<BR><table width=\"100%\" bgcolor=\"black\" cellpadding=\"12\" border=\"0\">";
  f += "<tr><td><p style = \"color: white; background: black;font-size: 0.8em; font-weight: bold; text-align: center; margin: 0px 10px 0px 10px;\">";
  f += "Tiago Batista &copy; 2017</p></td></tr>";
  f += "</table></body></center></html>";
  return f;
}
String HTMLPage() {
  String p = "</p><div class='container'>";
  p += "<h4>Wemos D1mini</h4>";
  p += "<div class='btn-group'>";
  p += "<BR><table><tr>";
  p += (status_auto) ? "<td><a href=\"/Auto/off\" class='btn btn-primary'>Auto ON <i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a>" : "<td><a href=\"/Auto/on\" class='btn btn-success'>Auto OFF <i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a>";
  //De acordo com o status da GPIO
  TimedAction();
  p += (status_gpio) ? "<a href=\"/rele/off\" class='btn btn-danger'><i class=\"fa fa-power-off\" aria-hidden=\"true\"></i> Desligar</a></td>" : "<a href=\"/rele/on\" class='btn btn-success'><i class=\"fa fa-power-off\" aria-hidden=\"true\"></i> Ligar</a></td>";
  p += "</tr></table></div><BR>";
  p += (F("<div class='btn-group'><p>"));

  p += "<BR><table><tr>";
  p += (F("<td><span><a href=\"/tempoD1/u\"><button type='button' class='btn btn-info' style='margin: 5px'>D1 Up</button></a>"));
  p += "<strong style='font-size:16px;'>" + time1() +  " ms</strong>";//armazena na eeprom;// exibe o delay
  p += (F("</span><a href=\"/tempoD1/d\"; URL=/'><button type='button' class='btn btn-info' style='margin: 5px'>D1 down</button></a></td>"));
  p += "</tr><tr>";
  p += (F("<td><span><a href=\"/tempoD2/u\"><button type='button' class='btn btn-info' style='margin: 5px'>D2 Up</button></a>"));
  p += "<strong style='font-size:16px;'>" + time2() +  " ms</strong>";// exibe o delay
  p += (F("</span><a href=\"/tempoD2/d\"><button type='button' class='btn btn-info' style='margin: 5px'>D2 down</button></a></td>"));
  p += "</tr><tr>";
  p += (F("<td><span><a href=\"/tempoD3/u\"><button type='button' class='btn btn-info' style='margin: 5px'>D3 Up</button></a>"));
  p += "<strong style='font-size:16px;'>" + time3() +  " ms</strong>";// exibe o delay
  p += (F("</span><a href=\"/tempoD3/d\"><button type='button' class='btn btn-info' style='margin: 5px'>D3 down</button></a></td>"));
  p += "</tr></table>";

  //  //horaliga
  //  p += "<td><a href = \"/hora/d\"  class='btn btn-default'>Down<i  class=\"fa fa-angle-down\" aria-hidden=\"true\"></i></a>\n";
  //  p += "<strong style='font-size:16px;'>hora  " + time5() + "</strong>"; // exibe o delay
  //  p += "<a href = \"/hora/u\"  class='btn btn-default'>Up<i class=\"fa fa-angle-up\" aria-hidden=\"true\"></i></a></td>\n";
  //  //minutoliga
  //  p += "<td><a href = \"/min/d\"  class='btn btn-default'>Down<i  class=\"fa fa-angle-down\" aria-hidden=\"true\"></i></a>\n";
  //  p += "<strong style='font-size:16px;'>min" + time4() + "</strong>"; // exibe o delay
  //  p += "<a href = \"/min/u\"  class='btn btn-default'>Up<i class=\"fa fa-angle-up\" aria-hidden=\"true\"></i></a></td>\n";

  p += "</p></div>";//container
  p += "</div> ";
  //reset
  p += (F("<a href=\"/reset\"><button type='button' class='btn btn-info' style='margin: 5px'>reset</button></a><BR>"));

  //************************************
  p += "<p>last update  "; // DIV para hora
  p += String(hora ());
  p += "<p>Programado para ligar &#224;s <span class=\"label label-success\">";
  p += horaligar();
  p += horaligar1();
  p += horaligar2();
  p += " horas</span></p><BR>";
  return p;
}


void webpage() {

  // ------------------------------ - server ------------------------ -
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("*WifiRTC: Nova conexao requisitada..."));
  while (!client.available()) {
    delay(1);
  }
  Serial.println (F("*WifiRTC: Nova conexao OK..."));
  String req = client.readStringUntil('\r');  //Le a string enviada pelo cliente
  Serial.println(req);                        //Mostra a string enviada
  client.flush();                             //Limpa dados/pfer
  TimedAction(); //verifica as condições da  eeprom


  // unsigned long currentMillis = millis();
  if (req.indexOf(F("Auto/on")) != -1) {
    status_auto = true;

  } else if (req.indexOf(F("Auto/off")) != -1) {
    status_auto = false;

  } else if (req.indexOf(F("rele/on")) != -1) {
    status_gpio = 1;// Muda botão ligar para ON
    digitalWrite(BUILTIN_LED, 1);                       //  all LEDs off to start
    runAndWait(D5, status_gpio, tempoD1);
    runAndWait(D7, status_gpio, tempoD2);
    runAndWait(D8, status_gpio, tempoD3);
    status_gpio = 0;
  } else if (req.indexOf(F("rele/off")) != -1) {
    // stateRelay = false;
    status_gpio = 0; //Muda botão ligar para OFF

  } else if (req.indexOf(F("tempoD1/u")) != -1) {
    tempoD1 = tempoD1 + 20;
    if (tempoD1 > 1000) {
      tempoD1 = 0;
    }
  } else if (req.indexOf(F("tempoD1/d")) != -1) {
    tempoD1 = tempoD1 - 20;
    if (tempoD1 < 0) {
      tempoD1 = 1000;
    }
  } else if (req.indexOf(F("tempoD2/u")) != -1) {
    tempoD2 = tempoD2 + 20;
    if (tempoD2 > 1000) {
      tempoD2 = 0;
    }
  } else if (req.indexOf(F("tempoD2/d")) != -1) {
    tempoD2 = tempoD2 - 20;
    if (tempoD2 < 0) {
      tempoD2 = 1000;
    }
  } else if (req.indexOf(F("tempoD3/u")) != -1) {
    tempoD3 = tempoD3 + 20;
    if (tempoD3 > 1000) {
      tempoD3 = 0;
    }
  } else if (req.indexOf(F("tempoD3/d")) != -1) {
    tempoD3 = tempoD3 - 20;
    if (tempoD3 < 0) {
      tempoD3 = 1000;
    }
  }   else if (req.indexOf(F("/reset")) != -1) {
    ESP.restart();//
  }  //
  //else if (req.indexOf(F("/hora/d")) != -1) { // controle do horario de acionamento
  //    horaLiga = horaLiga - 1;
  //    if (horaLiga < 0) {
  //      horaLiga = 23;
  //    }
  //  }   else if (req.indexOf(F("/hora/u")) != -1) {
  //    horaLiga = horaLiga + 1;
  //    if (horaLiga > 23) {
  //      horaLiga = 00;
  //    }
  //  } else if (req.indexOf(F("/min/u")) != -1) {
  //    minutoLiga = minutoLiga + 1;
  //    if (minutoLiga > 59) {
  //      minutoLiga = 00;
  //    }
  //  } else if (req.indexOf(F("/min/d")) != -1) {
  //    minutoLiga = minutoLiga - 1;
  //    if (minutoLiga < 0) {
  //      minutoLiga = 59;
  //    }
  // }
  else {
    // Serial.println(F("*WifiRTC: Requisicao invalida"));
  }

  Save_Data();//armazena na eeprom
  //Prepara a resposta para o cliente e carrega a pagina

  //Monta a pagina HTML
  String r = HTMLHeader();                     //  monta o cabeçalho
  r += HTMLPage(); //monta o corpo da pagina
  r += HTMLFooter(); // monta rodapé

  client.print(r);                              //  send page to clients browser

  client.flush();
  client.stop();
  //Serial.println(F("*WifiRTC: Cliente desconectado!"));
}


