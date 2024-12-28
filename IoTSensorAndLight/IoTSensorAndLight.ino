#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT11.h>

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK "PASSWORD"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
int ledPin = 0; // D3
ESP8266WebServer server(80);
DHT11 dht11(5); // D1

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Handle root URL request
  server.on("/", HTTP_GET, []() {
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    
    server.send(200, "text/html", String("\
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
    <h1>Custom IoT Controller</h1>\
        <h2>LED Switch</h2>\
        <p><a href=\"/on\"><button>ON</button></a>&nbsp;<a href=\"/off\"><button>OFF</button></a></p>\
        <h2>Current Humidity and Temperature</h2>\
        <p>Temperature: "+String(temperature)+"C</p><p>Humidity: "+String(humidity)+"</p>\
    </div>\
    </body>\
    </html>\
    "));
  });
  
  // Handle LED ON request
  server.on("/on", HTTP_GET, []() {
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    digitalWrite(ledPin, HIGH);
    server.send(200, "text/html", "\
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
    <h1>Custom IoT Controller</h1>\
        <h2>LED Switch</h2>\
        <p><a href=\"/on\"><button>ON</button></a>&nbsp;<a href=\"/off\"><button>OFF</button></a></p>\
        <h2>Current Humidity and Temperature</h2>\
        <p>Temperature: "+String(temperature)+"C</p><p>Humidity: "+String(humidity)+"</p>\        
    </div>\
    </body>\
    </html>\
    ");
  });

  // Handle LED OFF request
  server.on("/off", HTTP_GET, []() {
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    digitalWrite(ledPin, LOW);
    server.send(200, "text/html", "\
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
    <h1>Custom IoT Controller</h1>\
        <h2>LED Switch</h2>\
        <p><a href=\"/on\"><button>ON</button></a>&nbsp;<a href=\"/off\"><button>OFF</button></a></p>\
        <h2>Current Humidity and Temperature</h2>\
        <p>Temperature: "+String(temperature)+"C</p><p>Humidity: "+String(humidity)+"</p>\
    </div>\
    </body>\
    </html>\
    ");
  });

  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}
