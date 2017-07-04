#include <ESP8266WiFi.h>
#include <DHT.h>
#include <IRremoteESP8266.h> //INCLUSÃO DE BIBLIOTECA
 
const char* ssid = "MotoG3";
const char* password = "qwertyui";

//defines - mapeamento de pinos do NodeMCU
#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1

//defines - DHT22
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DHTPIN 4 // GPIo4 ou porta D2 do NodeMCU

// Infravermelho
IRsend irsend(12); //FUNÇÃO RESPONSÁVEL PELO MÉTODO DE ENVIO DO SINAL IR / UTILIZA O GPIO12(D6)

int tamanho = 68; //TAMANHO DA LINHA RAW(68 BLOCOS)
int frequencia = 32; //FREQUÊNCIA DO SINAL IR(32KHz)

//Variáveis usadas para calcular o tempo de execução
unsigned long tic;  
unsigned long toc;

//Dados Raw para infravermelho
// BOTÃO LIGA / DESLIGA
unsigned int LD[68]= {9000,4550,650,1700,600,1750,600,650,600,650,600,650,650,550,650,600,650,1700,650,1700,650,600,650,1700,600,650,650,1650,650,600,600,1750,650,600,650,600,650,600,650,600,650,600,650,1700,600,650,650,600,650,1700,650,1700,650,1700,650,1700,650,1700,650,600,650,1700,600,1750,650,600,650};
// BOTÃO CIMA
unsigned int UP[68] = {8950,4600,600,1750,650,1700,600,650,600,650,600,650,600,650,650,600,650,1700,650,1700,600,650,600,1750,600,650,600,1750,600,650,600,1750,600,600,600,650,600,650,650,600,600,650,600,1750,600,1750,650,600,600,1750,600,1750,600,1750,600,1700,650,1700,600,650,600,650,600,1750,650,600,600};
// BOTÃO BAIXO
unsigned int DOWN[68] = {9000,4550,600,1750,600,1750,600,650,550,650,600,650,600,650,600,650,600,1750,600,1750,600,650,600,1750,600,650,600,1700,600,600,600,1700,600,600,600,650,600,1750,600,650,600,650,600,1750,600,1750,600,650,600,1700,600,1750,600,650,600,1750,600,1750,600,650,600,650,600,1750,600,650,600};
// BOTÃO ESQUERDA
unsigned int LEFT[68] = {8950,4600,600,1750,600,1750,600,650,600,650,600,650,600,650,600,600,600,1700,600,1750,600,650,600,1750,600,650,600,1750,600,650,600,1750,600,650,600,1750,600,1750,600,600,600,650,600,1750,600,1750,600,650,600,1750,600,650,600,650,600,1750,600,1750,600,650,600,650,600,1750,600,650,600};
// BOTÃO OK
unsigned int OKK[68] = {8900,4550,600,1750,600,1750,600,650,600,650,600,650,600,650,600,650,600,1750,600,1750,600,700,550,1750,600,650,600,1750,600,600,600,1700,600,600,600,1700,600,650,600,1750,600,650,600,600,600,650,600,650,600,1750,600,650,600,1750,600,650,600,1750,600,1750,600,1750,600,1750,600,650,600};
// BOTÃO MENU
unsigned int MENU[68] = {8900,4600,550,1750,600,1750,600,650,600,650,600,600,600,600,600,600,600,1700,600,1700,600,600,600,1700,600,650,600,1750,600,650,600,1750,600,650,600,650,600,1750,600,650,600,1750,600,1750,600,650,600,650,600,1750,600,1750,600,650,600,1750,600,650,600,650,600,1750,600,1750,600,650,600};
// BOTÃO MENU
unsigned int NULO[68] = {0,0,0,0,0,0,0,0,0,0,0,0,0,600,600,600,600,1700,600,1700,600,600,600,1700,600,650,600,1750,600,650,600,1750,600,650,600,650,600,1750,600,650,600,1750,600,1750,600,650,600,650,600,1750,600,1750,600,650,600,1750,600,650,600,650,600,1750,600,1750,600,650,600};

WiFiServer server(80);      //Porta usada para se comunicar no WIFI
int presence;               //Variável usada para controle do sensor de presença

  //Sensor DHT22
  DHT dht(DHTPIN, DHTTYPE,11); //Criação do objeto de leitura DHT
  float t,h; //variáveis que armazenarão os valores lidos de temperatura e umidade;

  //Sensor de luz (LDR)
  int ldrPin = 0; //LDR no pino analógico 
  int ldrValor = 0; //Valor lido do LDR
 
void setup() {
  irsend.begin();
  Serial.begin(115200);
  dht.begin(); //Inicia o sensor
  delay(10);
 
  pinMode(D7, OUTPUT);                //Inicializamos o GPIO2 como saída
  digitalWrite(D7, LOW);              //Led ligado no GPIO2 começa apagado
  pinMode(D5,INPUT);                      //Recebe sinal do sensor de presença
  pinMode(D4,INPUT);                  //Chave que troca o Nodemcu de AP para Station
  pinMode(D3,OUTPUT);                     //Controla led do sensor de presença
  pinMode(D1,OUTPUT);                     //Controla led do ldr

  int R=digitalRead(D4);              //Faz a leitura da chave que troca o nodemcu para AP
  
  if (R==LOW){                        //Caso a chave esteja em sinal baixo (zero de tensão), configura modo AP
  server.begin();                         //inicializamos o servidor
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);                    //Rede aberta
 
  Serial.println();
 
  Serial.print("Direccion IP Access Point - por defecto: ");      //Imprime la dirección IP
  Serial.println(WiFi.softAPIP()); 
  Serial.print("Direccion MAC Access Point: ");                   //Imprime la dirección MAC
  Serial.println(WiFi.softAPmacAddress()); 
 
    }
  if(R==HIGH){                        //Caso a chave esteja em sinal alto (3.3V), configura modo station
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    Serial.print(".");
  }

  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  }
 
}
 
void loop() {
  tic = millis(); 
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Acender e apagar o led
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(D7, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(D7, LOW);
    value = LOW;
  }

  // Controle do sensor de presença
  if (digitalRead(D5) == LOW) {
    presence = 0;
    digitalWrite(D3, LOW);
  } else  {
    presence = 1;
    digitalWrite(D3, HIGH);
  }

  // Controla sensor LDR
  ldrValor = analogRead(ldrPin);
  if(ldrValor > 500) {
    digitalWrite(D1, HIGH);
  } else  {
    digitalWrite(D1, LOW);
  }
  Serial.print("LDR ");
  Serial.println(ldrValor);

  //leitura dos sensores de temperatura e umidade
  t=dht.readTemperature(); //Função de leitura da temperatura
  h=dht.readHumidity();//Função de leitura da umidade

  // Controle do infravermelho
  // Condição que liga / desliga projetor
  if (request.indexOf("/LIGA") != -1)  {
    irsend.sendRaw(LD,tamanho,frequencia);  // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
    Serial.println("Comando enviado: Liga / Desliga");
    delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  
  // Condição botão seta para cima
  if (request.indexOf("/CIMA") != -1)  {
        irsend.sendRaw(UP,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Aumenta volume");
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  // Condição botão seta para baixo
  if (request.indexOf("/BAIXO") != -1)  {
        irsend.sendRaw(DOWN,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Abaixa volume");
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  // Condição botão seta para esquerda
  if (request.indexOf("/ESQUERDA") != -1)  {
        irsend.sendRaw(LEFT,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Aumenta canal");
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  // Condição botão OK
  if (request.indexOf("/OK") != -1)  {
        irsend.sendRaw(OKK,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Diminui canal");
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  // Condição botão menu
  if (request.indexOf("/MENU") != -1)  {
        irsend.sendRaw(MENU,tamanho,frequencia); // PARÂMETROS NECESSÁRIOS PARA ENVIO DO SINAL IR
        Serial.println("Comando enviado: Diminui canal");
        delay(50); // TEMPO(EM MILISEGUNDOS) DE INTERVALO ENTRE UM COMANDO E OUTRO
  }
  
  //Parte HTML
  client.println("HTTP/1.1 200 OK");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<meta charset='UTF-8'>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta http-equiv=\"refresh\" content=\"3\">");        //Faz atualização da página web de 3 em 3 segundos
  client.println("</head>");
  //client.println("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />");
  
  // Criação de caixa para apresentar o status do sensor de presença
  client.println("<table width=\"280\" cellspacing=\"1\" cellpadding=\"3\" border=\"0\" bgcolor=\"#1E679A\"> ");
  client.println("<tr> ");
  client.println("<td><font color=\"#FFFFFF\" face=\"arial, verdana, helvetica\"> ");
  client.println("<b>Status do sensor de presença</b> ");
  client.println("</font></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td bgcolor=\"#ffffcc\">"); 
  client.println("<font face=\"arial, verdana, helvetica\">");
  if(presence == 1) {
    client.println("Sensor de presença ligado!");
  }
   else if (presence == 0){
    client.println("Sensor de presença desligado!");
   }
  client.println("</font> ");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table> ");
  client.println("<br><br>");
    
  //Controle do led no html
  // Criação de caixa para apresentar o status do led
  client.println("<table width=\"280\" cellspacing=\"1\" cellpadding=\"3\" border=\"0\" bgcolor=\"#1E679A\"> ");
  client.println("<tr> ");
  client.println("<td><font color=\"#FFFFFF\" face=\"arial, verdana, helvetica\"> ");
  client.println("<b>Led pin is now: </b> ");
  client.println("</font></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td bgcolor=\"#ffffcc\">"); 
  client.println("<font face=\"arial, verdana, helvetica\">");
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("</font> ");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table> ");
  client.println("<br><br>");

  // Criação de caixa para apresentar o status do sensor de luz
  client.println("<table width=\"280\" cellspacing=\"1\" cellpadding=\"3\" border=\"0\" bgcolor=\"#1E679A\"> ");
  client.println("<tr> ");
  client.println("<td><font color=\"#FFFFFF\" face=\"arial, verdana, helvetica\"> ");
  client.println("<b>Status do sensor de luninosidade</b> ");
  client.println("</font></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td bgcolor=\"#ffffcc\">"); 
  client.println("<font face=\"arial, verdana, helvetica\">");
  if(ldrValor > 500) {
    client.println("Led do LDR ligado!");
  } else  {
    client.println("Led do LDR desligado!");
  }
  client.println("</font> ");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table> ");
  client.println("<br><br>");

  //Criação de caixa para apresentar o status do sensor de temperatura e umidade
  client.println("<table width=\"280\" cellspacing=\"1\" cellpadding=\"3\" border=\"0\" bgcolor=\"#1E679A\"> ");
  client.println("<tr> ");
  client.println("<td><font color=\"#FFFFFF\" face=\"arial, verdana, helvetica\"> ");
  client.println("<b>Sensor de temperatura</b><br> ");
  client.println("<b>Sensor de umidade</b> ");
  client.println("</font></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td bgcolor=\"#ffffcc\">"); 
  client.println("<font face=\"arial, verdana, helvetica\">");
  client.println("Temperatura = ");
  client.println(t);
  client.println("°C<br>");
  client.println("Umidade = ");
  client.println(h);
  client.println("%<br>");
  client.println("</font> ");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table> ");
  client.println("<br><br>");

  // Criação de caixa para apresentar sensor infravermelho
  client.println("<table width=\"280\" cellspacing=\"1\" cellpadding=\"3\" border=\"0\" bgcolor=\"#1E679A\"> ");
  client.println("<tr> ");
  client.println("<td><font color=\"#FFFFFF\" face=\"arial, verdana, helvetica\"> ");
  client.println("<b>Infravermelho: </b> ");
  client.println("</font></td>");
  client.println("</tr>");
  client.println("<tr>");
  client.println("<td bgcolor=\"#ffffcc\">"); 
  client.println("<font face=\"arial, verdana, helvetica\">");
 
  client.println("<br><br>");
  client.println("<a href=\"/LIGA\"\"><button> On / Off </button></a><br/>");
  client.println("<a href=\"/CIMA\"\"><button>CIMA</button></a>");
  client.println("<a href=\"/BAIXO\"\"><button>BAIXO</button></a><br/>");
  client.println("<a href=\"/ESQUERDA\"\"><button>ESQUERDA</button></a>");
  client.println("<a href=\"/MENU\"\"><button>MENU</button></a>");
  client.println("<a href=\"/OK\"\"><button>OK</button></a><br/>");
  client.println("</html>");
 
  delay(1);
  Serial.println(t);
  Serial.println(h);
  Serial.println("Client disconnected");
  Serial.println("");
  
  toc = millis() - tic;
  Serial.println(toc);          //Imprime tempo de execução na serial

}
