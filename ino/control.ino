#include <ESP8266WiFi.h>
 
const char* ssid = "WIFI";
const char* password = "PW";
 
int ledPin = 13; // GPIO13
int analogIn = A0; // GPIO13
int ledState = LOW;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);

  ledState = LOW;

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

 
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
 
  server.begin();
  Serial.println("Server started");
 
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  /* 
    HERE IS WHERE YOU SHOULD INTRODUCE YOUR COMMANDS
    CUSTOMIZE THEM TO WORK WITH YOUR USES
    VVV
   */
  if (request.indexOf("cmd=TURN_ON_LED") != -1)
    ledState = HIGH;
  }
  else if (request.indexOf("cmd=TURN_OFF_LED") != -1)
  {
    ledState = LOW;    
  }
  digitalWrite(ledPin, ledState);

  int photocell_value = analogRead(analogIn);
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(ledState == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"?cmd=TURN_ON_LED\"><button>Turn On </button></a>");
  client.println("<a href=\"?cmd=TURN_OFF_LED\"><button>Turn Off </button></a>");
  
 
  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
