IoTtweet

IoTtweet library for https://www.iottweet.com dashboard using. Internet of Things cloud data storage and control
What is IoTtweet ?
IoTtweet.com is web APIs for storage and control your Internet of Things over network. Anywhere, anytime in the world.
How to start ?
[step 1.] 
Signup account with https://www.iottweet.com/signup/register.php
[step 2.]
Prepare your IoT device and install 2 library as below into your computer.
2.1) ESP8266WiFi.h library
    - Open Arduino IDE on your computer.
    - Go to preferences.
    - Add link "http://arduino.esp8266.com/stable/packageesp8266comindex.json" into Board Manager URLs.
    - Save and re-start Arduino IDE.
    - Go to Tool > Boards > Boards Manager.
    - Scroll down and find "esp8266 by ESP8266 community". This is contained a library of ESP8266WiFi.h.
    - Click install, and after installed complete, click close.
    - Restart Arduino IDE again.
    - Open example, you will see some examples code of ESP8266WiFi.h. And now ready to coding ESP8266.
2.2) ArduinoJson.h library
    - Open Arduino IDE on your computer.
    - Go to Sketch> Include Libraries > Manage Libraries 
    - Search "ArduinoJson" in search box, and make install it.
    - Restart Arduino IDE again.
2.3) IoTtweet.h library (we provided in this GITHUB)
    - Download this repository into your computer.
    - Extract files.
    - Copy folder name IoTtweet which contained 2 files of IoTtweet.h and IoTtweet.cpp, paste this folder at Arduino > libraries.
    - Restart Arduino IDE, ready to use IoTtweet command.
[step 3.]
Upload example code in this repository and change some parameter to your parameter.
const char *userid = "yourIoTtweetuserID"; 
const char *key = "yourregisteredIoTdevicekey"; 
const char *ssid = "yourwifissid"; 
const char *password = "yourwifipassword"; 
float data0, data1, data2, data3; 
const char *private_tweet = "Hello%20World"; 
const char *public_tweet = "I%20am%20Internet%20of%20Things";
