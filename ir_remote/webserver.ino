#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
//hadware transistor: BC547, ir led: TSAL6100, ir reciever: TSOP4838

IRsend irsend(4); //send pin = 13

IPAddress ip(192, 168, 1, 177);  
IPAddress gateway_ip ( 192,  168,   1,   1);
IPAddress subnet_mask(255, 255, 255,   0);

const char* ssid = "Rb";
const char* password = "";
 
WiFiServer server(80);
  
void setup() 
{
  WiFi.config(ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  irsend.begin();
  server.begin();
}
 
void loop() 
{

  //reset if wifi is not connected
  if (WiFi.status() == 6)
  {
      ESP.reset();
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) 
  {
    
   while(client.connected())
   {
     
     if (client.available()) 
     {  
        String request = client.readStringUntil('\r');
        client.flush();
     
        // Parse request
        if (request.indexOf("GET / HTTP/1.1") != -1)  
        {
        //index page
        }
        else if (request.indexOf("send") != -1)  
        {
          String returnResponse = "";
          returnResponse += "HTTP/1.1 200 OK\n";
          returnResponse += "Content-Type: text/html\n";
          returnResponse += "\n"; //  do not forget this one

          request.replace(" HTTP/1.1", "");
          request.replace("GET /send/", "");


          returnResponse += request;
          irsend.sendNEC(request.toInt(), 32);
          delay(300);
    
          client.println(returnResponse);
          client.stop();
          return;

        }
        else
        {
          client.println("HTTP/1.1 404 Not Found\n");
          client.stop();
          return;
        }
     
        // Return the response
        String returnResponse = "";
        
        returnResponse += "HTTP/1.1 200 OK\n";
        returnResponse += "Content-Type: text/html\n";
        returnResponse += "\n"; //  do not forget this one
        returnResponse += "LG TV"; //  do not forget this one

    
        client.println(returnResponse);
        client.stop();
      }
    }
  }
}
