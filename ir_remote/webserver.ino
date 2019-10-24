/*
 * Network Remote control for old LG TV
 * 
 * hadware list:
 * controller: NodeMCU v1
 * transistor: BC547 
 * ir led: TSAL6100 
 * ir reciever: TSOP4838
 * 
 */

#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>





/*
 
#define          REMOTE_KEY_INPUT                551538735
#define          REMOTE_KEY_ENERGY_SAVING        551528790
#define          REMOTE_KEY_POWER                551489775
#define          REMOTE_KEY_TVRADIO              551489520
#define          REMOTE_KEY_AV_MODE              551488755
#define          REMOTE_KEY_1                    551520375
#define          REMOTE_KEY_2                    551504055
#define          REMOTE_KEY_3                    551536695
#define          REMOTE_KEY_4                    551495895
#define          REMOTE_KEY_5                    551528535
#define          REMOTE_KEY_6                    551512215
#define          REMOTE_KEY_7                    551544855
#define          REMOTE_KEY_8                    551491815
#define          REMOTE_KEY_9                    551524455
#define          REMOTE_KEY_0                    551487735
#define          REMOTE_KEY_LIST                 551537205
#define          REMOTE_KEY_QVIEW                551508135
#define          REMOTE_KEY_VOLUMEUP             551502015
#define          REMOTE_KEY_VOLUMEDOWN           551534655
#define          REMOTE_KEY_MUTE                 551522415
#define          REMOTE_KEY_CHANNELUP            551485695
#define          REMOTE_KEY_CHANNELDOWN          551518335
#define          REMOTE_KEY_UP                   551486205
#define          REMOTE_KEY_DOWN                 551518845
#define          REMOTE_KEY_LEFT                 551542815
#define          REMOTE_KEY_RIGHT                551510175
#define          REMOTE_KEY_OK                   551494365
#define          REMOTE_KEY_MENU                 551535165
#define          REMOTE_KEY_EXIT                 551541285
#define          REMOTE_KEY_RED                  551505585
#define          REMOTE_KEY_GREEN                551521905
#define          REMOTE_KEY_YELLOW               551536185
#define          REMOTE_KEY_BLUE                 551519865
#define          REMOTE_KEY_TEXT                 551486715
#define          REMOTE_KEY_TOPT                 551519355
#define          REMOTE_KEY_SUBTITLE             551525475
#define          REMOTE_KEY_SIMPLILINK           551517825
#define          REMOTE_KEY_QMENU                551527005
#define          REMOTE_KEY_INFO                 551507370
#define          REMOTE_KEY_GUIDE                551540010
#define          REMOTE_KEY_FAVORITES            551516295
#define          REMOTE_KEY_RECORD               551533890
#define          REMOTE_KEY_BACK                 551490795
#define          REMOTE_KEY_HOME                 551501505
#define          REMOTE_KEY_RECORD               551533890
#define          REMOTE_KEY_STOP                 551521650
#define          REMOTE_KEY_PLAY                 551489010
#define          REMOTE_KEY_PAUSE                551509410
#define          REMOTE_KEY_FORWARD              551514510
#define          REMOTE_KEY_BACKWARD             551547150


*/




IRsend irsend(4); //send GPIO-4 = D2 on NodeMCU

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
        else if (request.indexOf("GET /favicon.ico HTTP/1.1") != -1)  
        {
        //index page
        }
        else if (request.indexOf("send") != -1)  
        {
          request.replace(" HTTP/1.1", "");
          request.replace("GET /send/", "");


          String jsonResponse = "{\"command\":\""+request+"\"}";
          String returnResponse = "";
          returnResponse += "HTTP/1.1 200 OK\r\n";
          returnResponse += "Content-Type: application/json\r\n";
          returnResponse += "Connection: close\r\n";
          returnResponse += "Content-Length: " + String(jsonResponse.length()) + "\r\n\r\n";
          returnResponse += jsonResponse;

    
          client.println(returnResponse);
          client.stop();
        
          irsend.sendNEC(request.toInt(), 32);
          delay(100);
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
        returnResponse += "LG TV"; 

    
        client.println(returnResponse);
        client.stop();
      }
    }
  }
}
