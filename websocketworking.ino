
#include "defines.h"

#include <WebSockets2_Generic.h>
#include <ESP8266WiFi.h>
const int LED = 14;
using namespace websockets2_generic;
int val=0;
char ch;

WebsocketsClient client;


 char readval(){
    val = random(0,100);
    // ch=val;
    return val;
    
  }
  void sendval(int val){
    // val= val>100? 0:val; 
    String masg=(String(val) + "");
    client.send(masg);
    

  }
void onEventsCallback(WebsocketsEvent event, String data) 
{
  (void) data;
  
  if (event == WebsocketsEvent::ConnectionOpened) 
  {
    Serial.println("Connnection Opened");
  } 
  else if (event == WebsocketsEvent::ConnectionClosed) 
  {
    Serial.println("Connnection Closed");
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("It's the fucking WIFI");
      // Connect to wifi
      WiFi.begin(ssid, password);
      pinMode(LED, OUTPUT); 
      // Wait some time to connect to wifi
      for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) 
      {
        Serial.print(".");
        delay(1000);
      }

    }
    while(!client.connect(websockets_server_host, websockets_server_port, "/ws?client=node"))
    {
      Serial.println("Oops we are fucked, let me try to fix it");
      delay(1000);
    }
  } 
  else if (event == WebsocketsEvent::GotPing) 
  {
    Serial.println("Got a Ping!");
  } 
  else if (event == WebsocketsEvent::GotPong) 
  {
    Serial.println("Got a Pong!");
  }
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  Serial.print("\nStart ESP8266-Client on "); Serial.println(ARDUINO_BOARD);
  Serial.println(WEBSOCKETS2_GENERIC_VERSION);
  
  // Connect to wifi
  WiFi.begin(ssid, password);
  pinMode(LED, OUTPUT); 
  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) 
  {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("No Wifi for fucks sake!");
    return;
  }

  Serial.print("Connected to Wifi, Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);
 
  // run callback when messages are received
  client.onMessage([&](WebsocketsMessage message) 
  {
    Serial.print("Got Message: ");
    String str = message.data();
    if(str == "on"){
      digitalWrite(LED, HIGH);

    }else{
      digitalWrite(LED, HIGH);
    }
    Serial.println(message.data());
  });

  // run callback when events are occuring
  client.onEvent(onEventsCallback);
  
  // try to connect to Websockets server
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/socket.io/?transport=websocket");
  
  // while(connected&&val!=0) 
  // {
  //   Serial.println("Connected!");

  //   String WS_msg = String("Hello to Server from ") + BOARD_NAME;
  //   String rand= ""+random();
  //   int count=0;
  // ch = count;
  // client.send(ch);
  // delay(2000);
  // count++;
  // val--;

  // } 
 
  
}

void loop() 
{
  client.poll();
  int val = readval();
    sendval(val);
    delay(1000);
  
}