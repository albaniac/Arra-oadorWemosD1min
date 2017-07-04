//monta a pagina do webserver
#include "horaNTP.h" // busca hora NTP

WiFiServer server(80);

//******************** pinOut *******************//

const int led0 = BUILTIN_LED;
//     pino        //status        //auto     //delay
uint8_t led1 = D1; bool v1 = 0; bool a1 = 0; int tempoD1;
uint8_t led2 = D2; bool v2 = 0; bool a2 = 0; int tempoD2;
uint8_t led3 = D3; bool v3 = 0; bool a3 = 0; int tempoD3;

//******************** TImer config *******************/ /
#include "eeprom.h"
//timers
int  horaLiga = 7 ; int  horaLiga1 = 12; int  horaLiga2 = 18; // horario de acionamento
int  minutoLiga = 00;

String horaligar () {//gera string da hora de acionamento
  char horaligar[30];
  sprintf( horaligar, "%02d:%02d ", horaLiga, minutoLiga); //
  return  horaligar;
}
String horaligar1 () {//gera string da hora de acionamento
  char horaligar1[30];
  sprintf( horaligar1, ",%02d:%02d ", horaLiga1, minutoLiga); //
  return horaligar1;
}
String horaligar2 () {//gera string da hora de acionamento
  char horaligar2[30];
  sprintf( horaligar2, ",%02d:%02d ", horaLiga2, minutoLiga); //
  return horaligar2;
}
//******* LED1 **********//
String time1() {//gera string para exibir o delay 
  char time1[10];
  sprintf( time1, "%d",  tempoD1);
  return time1;
}

void al1() { //aciona o led
  digitalWrite(led1,  v1);
  delay(tempoD1);
  Serial.println("liga");
  v1 = 0;
}
void auto_al1() {// alimentador 1
  if (((int(hour()) == (int)horaLiga) || (int(hour()) == (int)horaLiga1) || (int(hour()) == (int)horaLiga2)) && int(minute()) == (int)minutoLiga && (second() <= 2)) {
    digitalWrite(led1,  v1);
    delay(tempoD1);
    Serial.println("liga1");
    v1 = 0;
    Serial.println("deslig1");
    delay(1400);

  }
}
//******* LED2 **********//
String time2() {//gera string para exibir o delay 
  char time2[10];
  sprintf( time2, "%d",  tempoD2);
  return time2;
}

void al2() { //aciona o led
  digitalWrite(led2,  v2);
  delay(tempoD2);
  Serial.println("liga2");
  v2 = 0;
}
void auto_al2() {// acionamento automatico alimentador 2
  if (((int(hour()) == (int)horaLiga) || (int(hour()) == (int)horaLiga1) || (int(hour()) == (int)horaLiga2)) && int(minute()) == (int)minutoLiga && (second() <= 2)) {
    digitalWrite(led2,  v2);
    delay(tempoD2);
    Serial.println("liga2");
    v2 = 0;
    Serial.println("deslig2");
    delay(1400);

  }
}

//******* LED3 **********//
String time3() {//gera string para exibir o delay 
  char time3[10];
  sprintf( time3, "%d",  tempoD3);
  return time3;
}
void al3() {//aciona o led
  digitalWrite(led3,  v3);
  delay(tempoD3);
  Serial.println("liga");
  v3 = 0;
}
void auto_al3() {// acionamento automatico alimentador 3
  if (((int(hour()) == (int)horaLiga) || (int(hour()) == (int)horaLiga1) || (int(hour()) == (int)horaLiga2)) && int(minute()) == (int)minutoLiga && (second() <= 2)) {
    digitalWrite(led3,  v3);
    delay(tempoD3);
    Serial.println("liga3");
    v3 = 0;
    Serial.println("deslig3");
    delay(1400);

  }
}
//******************** HTML *******************/ /

String HTMLHeader() {                             //  standard HTML header
  String h = "HTTP/1.1 200 OK\r\n";
  h += "Content-Type: text/html\r\n\r\n";
  h += "<!DOCTYPE HTML><html><head><META HTTP-EQUIV='Refresh' CONTENT='10;URL=/'><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  h += "<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.1/css/bootstrap.min.css' rel='stylesheet'></link><link rel=\"stylesheet\" href=\"http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.6.3/css/font-awesome.min.css\"><center><body>\n";
  return h;
}
String HTMLFooter() {                            //  standard HTML footer
  String f = "<BR><table width=\"100%\" bgcolor=\"black\" cellpadding=\"12\" border=\"0\">\n";
  f += "<tr><td><p style = \"color: white; background: black;font-size: 0.8em; font-weight: bold; text-align: center; margin: 0px 10px 0px 10px;\">\n";
  f += "Tiago Batista &copy; 2017</p></td></tr>";
  f += "</table></body></center></html>\n";
  return f;
}

String HTMLPage() {                        //   main HTML for page, edit to suit your application
  String p =  "<img src='http://goo.gl/IoorRu' width='250' />";
  p += "<h3>Simple Webserver</h3>\n";
  p += "<p>Running on a <b>Wemos D1 mini</b></p>\n";
  p +=  hora () + "<BR>";
  //  display links depending on current state of LEDs 1 & 2
  p += "<BR><table><tr>";
  //led1
  p += (a1) ? "<td><a href = \"/auto1/0\" class='btn btn-success'>Auto off <i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/auto1/1\" class='btn btn-primary'>Auto on <i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += (v1) ? "<td><a href = \"/led1/0\"  class='btn btn-success'>LED 1 off<i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/led1/1\"class='btn btn-primary'>LED 1 on<i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += "<td><a href = \"/delay1d\" class='btn btn-default'>Down<i class=\"fa fa-angle-down\"  aria-hidden=\"true\"></i></a></button>\n"; //<button type='button' class='btn btn-info'>
  p += "<strong style='font-size:16px;'>" + time1() +  " ms</strong>";// exibe o delay
  p += "<a href = \"/delay1u\" class='btn btn-default' role='button'>Up<i class=\"fa fa-angle-up\" aria-hidden=\"true\"></i></a></td>\n";
  p += "</tr><tr>";
  //led2
  p += (a2) ? "<td><a href = \"/auto2/0\" class='btn btn-success'>Auto off <i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/auto2/1\" class='btn btn-primary'>Auto on <i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += (v2) ? "<td><a href = \"/led2/0\"  class='btn btn-success'>LED 2 off<i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/led2/1\"class='btn btn-primary'>LED 2 on<i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += "<td><a href = \"/delay2d\"  class='btn btn-default'>Down<i  class=\"fa fa-angle-down\" aria-hidden=\"true\"></i></a>\n";
  p += "<strong style='font-size:16px;'>" + time2() + " ms</strong>"; // exibe o delay
  p += "<a href = \"/delay2u\"  class='btn btn-default'>Up<i class=\"fa fa-angle-up\" aria-hidden=\"true\"></i></a></td>\n";
  p += "</tr><tr>";
  //led3
  p += (a3) ? "<td><a href = \"/auto3/0\" class='btn btn-success'>Auto off <i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/auto3/1\" class='btn btn-primary'>Auto on <i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += (v3) ? "<td><a href = \"/led3/0\"  class='btn btn-success'>LED 3 off<i class=\"fa fa-toggle-on\" aria-hidden=\"true\"></i></a></td>\n" : "<td><a href = \"/led3/1\"class='btn btn-primary'>LED 3 on<i class=\"fa fa-toggle-off\" aria-hidden=\"true\"></i></a></td>\n";
  p += "<td><a href = \"/delay3d\"  class='btn btn-default'>Down<i  class=\"fa fa-angle-down\" aria-hidden=\"true\"></i></a>\n";
  p += "<strong style='font-size:16px;'>" + time3() + " ms</strong>"; // exibe o delay
  p += "<a href = \"/delay3u\"  class='btn btn-default'>Up<i class=\"fa fa-angle-up\" aria-hidden=\"true\"></i></a></td>\n";
  p += "</tr><tr>";
  p += "</tr></table><BR>";

  p += (F("<a href=\"?function=clear\"><button type='button' class='btn btn-info' style='margin: 5px'>clear</button></a><BR>"));
  p += "<p>Programado para ligar &#224;s <span class=\"label label-success\">";
  p += horaligar();
  p += horaligar1();
  p += horaligar2();
  p += " horas</span></p><BR>";
  return p;
}

void clientserver() {

  WiFiClient client = server.available();        // Check if a client has connected
  if (!client) {
    return;
  }
  Serial.println("New client");                  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }
  String req = client.readStringUntil('\r');     // Read the first line of the request
  Serial.println(req);
  client.flush();
  //LED1
  if (req.indexOf("/led1/0") != -1)              //  if req = /led1/0
    v1 = 0;                                      //  set flag to turn LED1 off
  else if (req.indexOf("/led1/1") != -1) {        //  if req = /led1/1
    v1 = 1;                                      //  set flag to turn LED1 on
    al1();                                // aciona LED1
  } else if (req.indexOf("/auto1/0") != -1)         //  if req = /auto/0
    a1 = 0;                                      //  set flag to turn auto off
  else if (req.indexOf("/auto1/1") != -1) {        //  if req = /auto/1
    a1 = 1;
    auto_al1(); // aciona função auto
  }

  else if (req.indexOf(F("/delay1u")) != -1) {
    tempoD1 = tempoD1 + 50;
   if (tempoD1> 1000) {
      tempoD1 = 00;
    }
  } else if (req.indexOf(F("/delay1d")) != -1) {
    tempoD1 = tempoD1 - 49;
    tempoD1--; if (tempoD1 < 00) {
      tempoD1 = 1000;
    }
  }
  //LED2
  else if (req.indexOf("/led2/0") != -1)         //  if req = /led2/0
    v2 = 0;                                      //  set flag to turn LED2 off
  else if (req.indexOf("/led2/1") != -1) {        //  if req = /led2/1
    v2 = 1;                                      //  set flag to turn LED2 on
    al2(); // aciona led2
  } else if (req.indexOf("/auto2/0") != -1)         //  if req = /auto/0
    a2 = 0;                                      //  set flag to turn auto off
  else if (req.indexOf("/auto2/1") != -1) {        //  if req = /auto/1
    a2 = 1;
    auto_al2(); // aciona função auto
  } else if (req.indexOf(F("/delay2u")) != -1) {
    tempoD2 = tempoD2 + 50;
    if (tempoD2 > 1000) {
      tempoD2 = 00;
    }
  } else if (req.indexOf(F("/delay2d")) != -1) {
   tempoD2 = tempoD2- 50;
     if (tempoD2< 00) {
      tempoD2= 1000;
    }
  }

  //led3
  else if (req.indexOf("/led3/0") != -1)         //  if req = /led2/0
    v3 = 0;                                      //  set flag to turn LED2 off
  else if (req.indexOf("/led3/1") != -1) {        //  if req = /led2/1
    v3 = 1;                                      //  set flag to turn LED2 on
    al3(); // aciona led3
  } else if (req.indexOf("/auto3/0") != -1)        //  if req = /auto/0
    a3 = 0;                                      //  set flag to turn auto off
  else if (req.indexOf("/auto3/1") != -1) {       //  if req = /auto/1
    a3 = 1;
    auto_al3(); // aciona função auto
  } else if (req.indexOf(F("/delay3u")) != -1) {
    tempoD3 = tempoD3 + 50;
    if (tempoD3 > 1000) {
      tempoD3 = 00;
    }
  } else if (req.indexOf(F("/delay3d")) != -1) {
    tempoD3 = tempoD3 - 50;
     if (tempoD3< 00) {
      tempoD3 = 1000;
    }
  }
  // limpa eeprom
  else if (req.indexOf(F("/clear")) != -1) {
    //   reset_config();
    clearEeprom();
  }  else {
    Serial.println("Invalid request");           //  URL not recognised
    String r = HTMLHeader();                     //  display home page
    r += HTMLPage();
    r += HTMLFooter();
    client.print(r);                              //  send page to clients browser
    client.stop();                                //  disconnect client
    return;
  }
  digitalWrite(led1, v1);                         //  set LED1 according to v1
  digitalWrite(led2, v2);                         //  set LED2 according to v2
  digitalWrite(led3, v3);                         //  set LED3 according to v3
  Save_Data();// armazena status na eeprom
  client.flush();

  String s = HTMLHeader();                        //  display page
  s += HTMLPage();
  s += HTMLFooter();


  digitalWrite(led0, 1);                          //  page is being sent
  client.print(s);                                //  send the response to the client
  client.stop();                                  //  disconnect client
  digitalWrite(led0, 0);                          //  finished sending page
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}


