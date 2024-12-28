#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void setup(void){
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");// add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {
  server.send(200, "text/plain", "\
<!doctype html>\
<html>\
<head>\
    <title>IoT Device</title>\
    <meta charset=\"utf-8\" />\
    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\
    <style type=\"text/css\">\
    body {\
        background-color: #f0f0f2;\
        margin: 0;\
        padding: 0;\
        font-family: -apple-system, system-ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;\
        \
    }\
    div {\
        width: 600px;\
        margin: 5em auto;\
        padding: 2em;\
        background-color: #fdfdff;\
        border-radius: 0.5em;\
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);\
    }\
    a:link, a:visited {\
        color: #38488f;\
        text-decoration: none;\
    }\
    @media (max-width: 700px) {\
        div {\
            margin: 0 auto;\
            width: auto;\
        }\
    }\
    </style>    \
</head>\
\
<body>\
<div>\
    <h1>Example Interface</h1>\
    <p></p>\
</div>\
</body>\
</html>\
");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

