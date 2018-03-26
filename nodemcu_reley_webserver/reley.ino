#include <ESP8266WiFi.h>

IPAddress ip(192, 168, 1, 177);  
IPAddress gateway_ip ( 192,  168,   1,   1);
IPAddress subnet_mask(255, 255, 255,   0);

const char* ssid = "Rb";
const char* password = "";
 
WiFiServer server(80);

int initializedOutputPins[] = {16,5,4,0,2,14,12,13,15};
int i;
  
void setup() 
{
  for(i=0;i<8;i++)
  {
    pinMode(initializedOutputPins[i], OUTPUT);
    digitalWrite(initializedOutputPins[i], HIGH);
  } 

  WiFi.config(ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

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
        else if (request.indexOf("ON") != -1)  
        {
          request.replace("/ON HTTP/1.1", "");
          request.replace("GET /", "");
          digitalWrite(initializedOutputPins[request.toInt()], LOW);
        }
        else if (request.indexOf("OFF") != -1)  
        {
          request.replace("/OFF HTTP/1.1", "");
          request.replace("GET /", "");
          digitalWrite(initializedOutputPins[request.toInt()], HIGH);
        }
        else if (request.indexOf("TOGGLE") != -1)  
        {
          request.replace("/TOGGLE HTTP/1.1", "");
          request.replace("GET /", "");
          if(digitalRead(initializedOutputPins[request.toInt()]) == LOW) 
          {
             client.println("HTTP/1.1 200 OK\nContent-Type: text/html\n\nOFF");
             digitalWrite(initializedOutputPins[request.toInt()], HIGH);
          }
          else
          {
            
             client.println("HTTP/1.1 200 OK\nContent-Type: text/html\n\nON");
             digitalWrite(initializedOutputPins[request.toInt()], LOW);
          }
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
        returnResponse += "<!DOCTYPE HTML>";
        returnResponse += "<html>";
        returnResponse += "<head>";
        returnResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        returnResponse += "<link rel=\"stylesheet\" type=\"text/css\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\">";
        returnResponse += "<script src=\"//ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\" type=\"text/javascript\"></script>";
        returnResponse += "<script src=\"//maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\" type=\"text/javascript\"></script>";
        returnResponse += "<title>Rado NodeMCU</title>";
        returnResponse += "</head>";
        returnResponse += "<body style=\"min-width:400px\">";
      
      
        returnResponse += "<div class=\"container py-5\">";
        returnResponse += "<div class=\"col-md-5 offset-md-3\">";
        returnResponse += "<div class=\"card card-outline-secondary\">"; 
        returnResponse += "<div class=\"card-header text-center\">"; 
        returnResponse += "<h3 class=\"mb-0\">Rado NodeMCU</h3>";       
        returnResponse += "</div>"; 
    
    
        returnResponse += "<div class=\"card-body\">";
        for(i=0;i<8;i++)
        {
          returnResponse += "<div class=\"form-group row\">";
          returnResponse += "<label class=\"col-lg-8 col-form-label form-control-label\"> GPIO ";
          returnResponse += String(i);
          returnResponse += " : ";
          returnResponse +="</label>";
          if(digitalRead(initializedOutputPins[i]) == LOW) 
          {
            returnResponse +="<div class=\"col-lg-4\"><a href=\"/";
            returnResponse += String(i);
            returnResponse +="/OFF\"><button class=\"btn btn-danger\"> Turn Off </button></a></div>";
          } 
          else 
          {
            returnResponse +="<div class=\"col-lg-4\"><a href=\"/";
            returnResponse += String(i);
            returnResponse += "/ON\"><button class=\"btn btn-success\"> Turn On </button></a></div>";
          }
         returnResponse += "</div>";
        }
        returnResponse += "</div>"; 
        returnResponse += "</div>"; 
        returnResponse += "</div>"; 
        returnResponse += "</div>";
        returnResponse += "</body>";
        returnResponse += "</html>";
    
        client.println(returnResponse);
        client.stop();
      }
    }
  }
}

