#include "FastLED.h"
#include <ESP8266WiFi.h>
//#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

// How many leds in your strip?
#define NUM_LEDS 100

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 5
#define CLOCK_PIN 13
#define COLOR_ORDER GRB
#define BRIGHTNESS  64
#define UPDATES_PER_SECOND 100

int status = WL_IDLE_STATUS;


CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


/* Set these to your desired credentials. */
const char s[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>ESP8266 Web Form Demo</title>"
"<style>"
"\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
"</style>"
"</head>"
"<body>"
"<h1> 20 Gallon LED Controller </h1>"
"<FORM action=\"/\" method=\"post\"> <input type=hidden name=hiddenarg value=1>"
"<P>"
"Color<br>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Red\">Red<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Blue\">Blue<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Gold\">Gold<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Green\">Green<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"White\">White<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Orange\">Orange<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Pink\">Pink<BR>"
//"<INPUT type=\"radio\" name=\"LED\" value=\"SetupTotallyRandomPalette\">Random<BR>"
"<INPUT type=\"radio\" name=\"LED\" value=\"Off\">Off<BR>"
"<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
"</P>"
"</FORM>"
"</body>"
"</html>";



// Define the array of leds
CRGB leds[NUM_LEDS];
void Blue(){
  for(int i=0;i<100;i++){
  leds[i] = CRGB( 0, 0, 255); //another way to define colors
  }
    FastLED.show();
  }
  
  void Green(){
  for(int i=0;i<100;i++){
  leds[i] = CRGB::Green;
  }
   FastLED.show();
  }
  
   void Red(){
    for(int i=0;i<100;i++){
  leds[i] = CRGB::Red;
  }
   FastLED.show();

  }

  void Off(){
    for(int i=0;i<100;i++){
  leds[i] = CRGB::Black;
   }
     FastLED.show();
   }


  void White(){
for(int i=0;i<100;i++){
  leds[i] = CRGB::White;
}
  FastLED.show();

  }

  void Orange(){
for(int i=0;i<100;i++){
  leds[i] = CRGB(255,90,0);
}
  FastLED.show();

  }

  void Gold(){
for(int i=0;i<100;i++){
  leds[i] = CRGB::Gold;
}
  FastLED.show();

  }

  void Pink(){
for(int i=0;i<100;i++){
  leds[i] = CRGB(255, 20,147); 
}
  FastLED.show();

  }

  void SetupTotallyRandomPalette()
{
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    for( int i = 0; i < 100; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
        uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, startIndex, brightness, currentBlending);
        startIndex += 3;
    }
      FastLED.show();

}

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", s);
 Serial.println("Someone is looking at me!");
   if (server.hasArg("hiddenarg")) {
    handleSubmit();
  }
}
void handleSubmit()
{
  String LEDvalue;

  LEDvalue = server.arg("LED");
  Serial.println("I've submitted something");
  if (LEDvalue == "Blue") {
  Blue();
  Serial.println("TURN Blue ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Red") {
  Red();
  Serial.println("TURN Red ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Green") {
  Green();
  Serial.println("TURN Green ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Gold") {
  Gold();
  Serial.println("TURN Gold ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "White") {
  White();
  Serial.println("TURN white ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Orange") {
  Orange();
  Serial.println("TURN Orange ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Pink") {
  Pink();
  Serial.println("TURN Pink ON");
    server.send(200, "text/html", s);
  }
  else if (LEDvalue == "Off") {
    Off();
    Serial.println(" off");
    server.send(200, "text/html", s);
  }

  else if (LEDvalue == "SetupTotallyRandomPalette") {
    SetupTotallyRandomPalette();
    Serial.println(" Random");
    server.send(200, "text/html", s);
  }

}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
//	WiFi.softAP(ssid, password);
  delay(10);
  Serial.println('\n');
  // WiFi.begin("dlink");
  WiFi.begin("ATTfXj99MS", "nz#gh8tjj=uq");
  Serial.print("Connecting to ");
  Serial.print("Home WiFi"); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer

	server.on("/", handleRoot);
//  server.on("/ledon", handleLEDon);
//  server.on("/ledoff", handleLEDoff);
	server.begin();
	Serial.println("HTTP server started");

}

void loop() {
	server.handleClient();
  //FastLED.show();
}
