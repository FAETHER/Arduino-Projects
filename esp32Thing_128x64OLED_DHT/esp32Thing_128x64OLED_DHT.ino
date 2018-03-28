int demoMode = 0;

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>    // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

#define DHTPIN 33         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
SSD1306  display(GEOMETRY_128_64, 0x3c, 21, 22);
#define DEMO_DURATION 3000
typedef void (*Demo)(void);

void setup() {
  Serial.begin(9600); 

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  
  // Initialize device.
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void drawFontFaceDemo() {
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    sensors_event_t event;  
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
    display.drawString(0,0, "Error reading temperature!");
    Serial.print("error temp ");
     }else{
    display.clear();
    Serial.print("Temperature: ");
    display.drawString(0,0, "You temp is:");
    Serial.print(event.temperature);
    //event.temperature = " ";
    display.drawString(0,10, String(event.temperature));
    Serial.println(" *C");
    display.drawString(60,0, "*C");

   // */--- There is a bug in moisture measurement somewhere ---/*
    
//    dht.humidity().getEvent(&event);
//    if (isnan(event.relative_humidity)) {
//    Serial.println("Error reading humidity!");
//    display.drawString(0,0, "Error reading humidity!");
//    }else{
//    display.clear();  
//    Serial.print("Humidity: ");
//    Serial.print(event.relative_humidity);
//    Serial.println("%");
//    display.drawString(0,70, "You hum is:");
//    display.drawString(0,80, String(event.relative_humidity));
//    display.drawString(60,0, "%");
}
     }
//}
     
void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  Demo demos[] = {drawFontFaceDemo};

  display.clear();
  // draw the current demo method
  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
  }
