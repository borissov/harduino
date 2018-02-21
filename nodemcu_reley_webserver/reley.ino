#include <ESP8266WiFi.h>
 
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
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}
 
void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  client.flush();
 
  // Parse request
  if (request.indexOf("ON") != -1)  
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
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
  client.println("<link rel=\"stylesheet\" type=\"text/css\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css\">");
  client.println("<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js\" type=\"text/javascript\"></script>");
  client.println("</head>");


  client.println("<div class=\"container py-5\">");
  client.println("<div class=\"col-md-6 offset-md-3\">");
  client.println("<div class=\"card card-outline-secondary\">"); 
  client.println("<div class=\"card-header\">"); 
  client.println("<h3 class=\"mb-0\">Rado NodeMCU</h3>");       
  client.println("</div>"); 


  client.println("<div class=\"card-body\">");
  for(i=0;i<8;i++)
  {
    client.println("<div class=\"form-group row\">");
    client.print("<label class=\"col-lg-8 col-form-label form-control-label\">Output Pin ");
    client.print(i);
    client.print(" : ");
    if(digitalRead(initializedOutputPins[i]) == LOW) 
    {
      client.print("On</label>");

      client.print("<div class=\"col-lg-2\"><a href=\"/");
      client.print(i);
      client.print("/OFF\"><button class=\"btn btn-danger\">Turn Off </button></a></div>");
    } 
    else 
    {
      client.print("Off</label>");
      client.print("<div class=\"col-lg-2\"><a href=\"/");
      client.print(i);
      client.print("/ON\"><button class=\"btn btn-success\">Turn On </button></a></div>");
    }
    client.println("</div>");
  }
  client.println("</div>"); 
  client.println("</div>"); 
  client.println("</div>"); 
  client.println("</div>");
  client.println("</html>");
  delay(1);
}
 
