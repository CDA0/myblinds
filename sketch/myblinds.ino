#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 
 
const char* ssid = "FusionZoo";
const char* password = "mcveycam";
 
ESP8266WebServer server(80);

Servo myservo;

int pos = 0;
 
void handleRoot() {
  server.send(200, "text/plain", "Hello from My Blinds!");
}

void handleOpen() {
  open();
  server.send(200, "text/plain", "Opened");
}

void handleClose() {
  close();
  server.send(200, "text/plain", "Closed");
}

void handleToggle() {
  toggle();
  server.send(200, "text/plain", "Toggled!");
}

void handleStatus() {
  server.send(200, "text/plain", pos == 0 ? "Closed" : "Open");
}

void handleSlideOpen() {
  slideOpen();
  server.send(200, "text/plain", "Sliding");
}
 
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void){
  myservo.attach(2);  // attaches the servo on GIO2 to the servo object 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.begin(ssid, password);
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  MDNS.begin("esp8266");
 
  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.on("/slide", handleSlideOpen);
 
  server.onNotFound(handleNotFound);
 
  server.begin();

  
}
 
void loop(void){
  server.handleClient();
}

void open()
{            
    pos = 180; 
    myservo.write(pos);  
}
void close()
{             
    pos = 0;
    myservo.write(pos);  
}

void toggle() {
  pos = pos == 180 ? 0 : 180;
  myservo.write(pos);  
}

int slidePos = 0;

void slideOpen(){
  digitalWrite(LED_BUILTIN, HIGH);
  for(int i = 0; i < 10; i++){
    for(int j=0;j<360;j+=10){
      setSlidingServo(j);
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setSlidingServo(int j){
   slidePos = j;
  delay(20);
}
