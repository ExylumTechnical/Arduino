#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80
DHT11 dht11(2); // Set pin for DHT11 sesor to be pin D4

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
//String getDHTSensorInfo();

void setup(void){
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  dht11.setDelay(500); // Set this to the desired delay. Default is 500ms. for DHT11 sensor
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("YOUR_SSID", "YOUR_WIFI_PASSWORD");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("YOUR_OTHER_SSID", "YOUR_OTHER_WIFI_PASSWORD");   // for redundancy
  wifiMulti.addAP("ANOTHER_SSID", "ANOTHER_WIFI_PASSWORD");   

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
    String post;
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);

    if (result == 0) {
      server.send(200, "text/html", String("<!DOCTYPE html><html><head><title>Temp/Humidity Sensor</title></head><body><h1>Sensor Data</h1><p>Temperature: "+String(temperature)+"C</p><p>Humidity: "+String(humidity)+"</p></body></html>"));
// server.send(200, "text/plain", String(String(temperature)+","+String(humidity)+"%")); // for CSV style data accquisition
    } else {
        // Print error message based on the error code.
    server.send(200, "text/html", String("<!DOCTYPE html><html><head><title>Temp/Humidity Sensor</title></head><body><h1>Sensor Data</h1><p>Sensor Error:"+String(DHT11::getErrorString(result))+" </p></body></html>"));
//    server.send(200, "text/plain",String(DHT11::getErrorString(result)));
    }
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

