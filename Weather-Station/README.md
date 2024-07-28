# Weather Station Project
This is meant to be a small IoT sensor that just provides the humidity and temperature of where it is placed via an http server.

## Requirements:
- the DHT11 Temperature and Humidity Sensor
- 3 jumper cables
- The ESP8266MOD development board
- A wireless network to connect the device to.

## Setup:
1. The signal wire for the DHT11 sensor should be connected to the D4 pin on the Arduino ESP8266 board
2. Install the libararies ( I used the DHT11 library from Dr. Rubasha which can be found here: https://github.com/dhrubasaha08/DHT11 )
3. Change the YOUR_SSID and YOUR_WIFI_PASSWORD in the code accordingly
4. Compile and upload
5. Watch the serial output for the ip address and that it successfully connected to the wifi network
6. Go to a web browser and verify the sensor is reachable and updating.

Try breathing on the sensor and refreshing the page to verify it is reading data.
