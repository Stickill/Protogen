#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


Adafruit_8x16matrix eye_r = Adafruit_8x16matrix();
Adafruit_8x16matrix eye_l = Adafruit_8x16matrix();
Adafruit_8x8matrix nostril_r = Adafruit_8x8matrix();
Adafruit_8x8matrix nostril_l = Adafruit_8x8matrix();
Adafruit_8x16matrix mouth_back_r = Adafruit_8x16matrix();
Adafruit_8x16matrix mouth_front_r = Adafruit_8x16matrix();
Adafruit_8x16matrix mouth_front_l = Adafruit_8x16matrix();
Adafruit_8x16matrix mouth_back_l = Adafruit_8x16matrix();

WiFiServer server(8080);
const char* ssid = "****";
const char* pass = "****";

#define fbsize 112
static uint8_t framebuffer[fbsize];

void clearall() {
  eye_r.clear();
  eye_l.clear();
  nostril_r.clear();
  nostril_l.clear();
  mouth_back_r.clear();
  mouth_front_r.clear();
  mouth_front_l.clear();
  mouth_back_l.clear();
}

void writeall() {
  eye_r.writeDisplay();
  eye_l.writeDisplay();
  nostril_r.writeDisplay();
  nostril_l.writeDisplay();
  mouth_back_r.writeDisplay();
  mouth_front_r.writeDisplay();
  mouth_front_l.writeDisplay();
  mouth_back_l.writeDisplay();
}

void displayfb() {
  clearall();
  
  memcpy(&eye_r.displaybuffer, framebuffer, 16);
  memcpy(&eye_l.displaybuffer, framebuffer + 16, 16);


  // Nostril memory layout is f*cked
  for(int i = 0; i < 8; i++) {
    nostril_r.displaybuffer[i] = framebuffer[i + 32];
  }

  for(int i = 0; i < 8; i++) {
    nostril_l.displaybuffer[i] = framebuffer[i + 40];
  }

  //memcpy(&nostril_r.displaybuffer, framebuffer + 32, 8);
  //memcpy(&nostril_l.displaybuffer, framebuffer + 40, 16);

  memcpy(&mouth_back_r.displaybuffer, framebuffer + 48, 16);
  memcpy(&mouth_front_r.displaybuffer, framebuffer + 64, 16);

  memcpy(&mouth_front_l.displaybuffer, framebuffer + 80, 16);
  memcpy(&mouth_back_l.displaybuffer, framebuffer + 96, 16);

  writeall();
}

void initmatrices() {

  eye_r.begin(0x70); //no solder
  eye_l.begin(0x71);
  nostril_r.begin(0x72); 
  nostril_l.begin(0x73); 
  mouth_back_r.begin(0x74); //solder A2
  mouth_front_r.begin(0x75); //solder A2 A0
  mouth_front_l.begin(0x76); //solder A2 A1
  mouth_back_l.begin(0x77); //solder All

  eye_r.setRotation(1);
  eye_l.setRotation(3);
  nostril_r.setRotation(1);
  nostril_l.setRotation(1);
  mouth_back_r.setRotation(1);
  mouth_front_r.setRotation(3);
  mouth_front_l.setRotation(1);
  mouth_back_l.setRotation(3);

  clearall();

  writeall();
}

void setup()
{

  initmatrices();

  Serial.begin(9600);
  Serial.println();

  WiFi.begin(ssid, pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  
  server.begin();
}

void loop() {
  displayfb();
  
  WiFiClient client = server.available();

  while (client.connected()) {

    int available = client.available();
    
    if (available >= fbsize) {

      client.readBytes(framebuffer, fbsize);
      client.write((uint8_t) available);
      Serial.println("Rcv succes");
      displayfb();
    } 

    yield();
  }

  client.stop();
}
