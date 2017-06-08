#include <ESP8266WiFi.h>
 
const char* ssid = "net virtua 1450 apto 701";
const char* password = "juniorlia1";

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

WiFiServer server(80);
int presence;
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW);

  pinMode(D5, INPUT);
  
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
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
 
void loop() {
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
 
  // Match the request
  // Função que cuida de acender e apagar o led
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(D7, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(D7, LOW);
    value = LOW;
  }

  // Função que cuida do sensor de presença
  if (digitalRead(D5) == LOW) {
    presence=0;
  } else  {
    presence = 1;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  //Parte HTML
  client.println("HTTP/1.1 200 OK");
  //client.println("Content-Type: text/html");
  //client.println("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\" />");
  
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
  
  if(presence == 1) 
    client.println("Sensor de presença ligado!");
   else if (presence == 0) 
    client.println("Sensor de presença desligado!");
  
  client.println("</font> ");
  client.println("</td>");
  client.println("</tr>");
  client.println("</table> ");

  client.println("");
  client.println("");
  client.println("");
  
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
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
 
