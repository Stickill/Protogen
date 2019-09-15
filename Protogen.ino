
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

// animation delay between frames in ms
int an_delay = 20;
int fade_delay = 1;

void startup() {
  for(uint16_t i = 0; i < 16; i++) {
    // scan eyes
    eye_r.drawFastVLine(i, 0, 8, LED_ON);
    eye_l.drawFastVLine(16 - i, 0, 8, LED_ON);
    
    eye_r.writeDisplay();
    eye_l.writeDisplay();
    
    eye_r.clear();
    eye_l.clear();

    // scan back of mouth at the same time
    mouth_back_r.drawFastVLine(i, 0, 8, LED_ON);
    mouth_back_l.drawFastVLine(16 - i, 0, 8, LED_ON);
    
    mouth_back_r.writeDisplay();
    mouth_back_l.writeDisplay();
    
    mouth_back_r.clear();
    mouth_back_l.clear();
    
    delay(an_delay);
  }
  // clear finished part of animation
  eye_r.writeDisplay();
  eye_l.writeDisplay();
  mouth_back_r.writeDisplay();
  mouth_back_l.writeDisplay();

  // scan front part of mouth
  for(uint16_t i = 0; i < 16; i++) {
    mouth_front_r.drawFastVLine(i, 0, 8, LED_ON);
    mouth_front_l.drawFastVLine(16 - i, 0, 8, LED_ON);
    
    mouth_front_r.writeDisplay();
    mouth_front_l.writeDisplay();
    
    mouth_front_r.clear();
    mouth_front_l.clear();
    delay(an_delay);
  }
  mouth_front_r.writeDisplay();
  mouth_front_l.writeDisplay();

//  // blink nose
//  for(uint i = 0; i < 10; i++) {
//      nostril_l.writeDisplay();
//      nostril_r.fillScreen(LED_ON);
//      nostril_r.writeDisplay();
//      nostril_r.clear();
//      delay(50);
//      nostril_r.writeDisplay();
//      nostril_l.fillScreen(LED_ON);
//      nostril_l.writeDisplay();
//      nostril_l.clear();
//      delay(50);
//  }
//  nostril_l.writeDisplay();

  // fade everything
  for(uint i = 0; i < 3; i++) {
      nostril_r.fillScreen(LED_ON);
      nostril_l.fillScreen(LED_ON);

      mouth_back_l.fillScreen(LED_ON);
      mouth_back_r.fillScreen(LED_ON);
      mouth_front_l.fillScreen(LED_ON);
      mouth_front_r.fillScreen(LED_ON);

      eye_l.fillScreen(LED_ON);
      eye_r.fillScreen(LED_ON);

      for(uint8_t i = 0; i < 16; i++){
          nostril_r.setBrightness(i);
          nostril_l.setBrightness(i);

          mouth_back_l.setBrightness(i);
          mouth_back_r.setBrightness(i);
          mouth_front_l.setBrightness(i);
          mouth_front_r.setBrightness(i);
    
          eye_l.setBrightness(i);
          eye_r.setBrightness(i);
          
          nostril_r.writeDisplay();
          nostril_l.writeDisplay();

          mouth_back_l.writeDisplay();
          mouth_back_r.writeDisplay();
          mouth_front_l.writeDisplay();
          mouth_front_r.writeDisplay();
    
          eye_l.writeDisplay();
          eye_r.writeDisplay();
          
          delay(fade_delay);
      }

      for(uint8_t i = 0; i < 16; i++){
          nostril_r.setBrightness(15 - i);
          nostril_l.setBrightness(15 - i);
          
          mouth_back_l.setBrightness(15 - i);
          mouth_back_r.setBrightness(15 - i);
          mouth_front_l.setBrightness(15 - i);
          mouth_front_r.setBrightness(15 - i);
    
          eye_l.setBrightness(15 - i);
          eye_r.setBrightness(15 - i);
          
          nostril_r.writeDisplay();
          nostril_l.writeDisplay();

          mouth_back_l.writeDisplay();
          mouth_back_r.writeDisplay();
          mouth_front_l.writeDisplay();
          mouth_front_r.writeDisplay();
    
          eye_l.writeDisplay();
          eye_r.writeDisplay();
          delay(fade_delay);
      }

  }

}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello world I am St1cki11");

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

  eye_r.clear();
  eye_l.clear();
  nostril_r.clear();
  nostril_l.clear();
  mouth_back_r.clear();
  mouth_front_r.clear();
  mouth_front_l.clear();
  mouth_back_l.clear();

  eye_r.writeDisplay();
  eye_l.writeDisplay();
  nostril_r.writeDisplay();
  nostril_l.writeDisplay();
  mouth_back_r.writeDisplay();
  mouth_front_r.writeDisplay();
  mouth_front_l.writeDisplay();
  mouth_back_l.writeDisplay();

  startup();
  
}
static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
full_bmp[] =
{ B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
},
nostril_1_bmp[] =
{
  B01111110,
  B00111111,
  B00000011,
  B00000011,
  B00000001,
  B00000000,
  B00000000,
  B00000000
},
nostril_2_bmp[] =
{
  B01111110,
  B11111100,
  B11000000,
  B11000000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
},
eye_angry_1_bmp[] =
{ B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000111,
  B00011111,
  B01111111,
  B11111111
},
eye_angry_2_bmp[] =
{
  B00000111,
  B00011111,
  B01111111,
  B11111111,
  B11111111,
  B11111111,
  B11111110,
  B10000000
},
eye_circle_1_bmp[] =
{
  B00000011,
  B00000111,
  B00001111,
  B00011111,
  B00011111,
  B00001111,
  B00000111,
  B00000011
},
eye_circle_2_bmp[] =
{
  B11000000,
  B11100000,
  B11110000,
  B11111000,
  B11111000,
  B11110000,
  B11100000,
  B11000000
},
eye_vwv_1_bmp[] =
{
  B00000000,
  B00011100,
  B00011100,
  B00110110,
  B00110110,
  B01100011,
  B01100011,
  B11000001
},
eye_vwv_2_bmp[] =
{
  B00000000,
  B00011100,
  B00011100,
  B00110110,
  B00110110,
  B01100011,
  B11100011,
  B11000001
},
eye_no_1_bmp[] =
{
  B01000010,
  B01100010,
  B01110010,
  B01011010,
  B01001110,
  B01000110,
  B01000010,
  B00000000
},
eye_no_2_bmp[] =
  {
  B00011100,
  B00100010,
  B01000001,
  B01000001,
  B01000001,
  B00100010,
  B00011100,
  B00000000
},
eye_uwu_1_bmp[] =
{
  B00110000,
  B00110000,
  B00011000,
  B00011000,
  B00001100,
  B00001110,
  B00000111,
  B00000001
},
eye_uwu_2_bmp[] =
{
  B00001100,
  B00001100,
  B00011000,
  B00011000,
  B00110000,
  B01110000,
  B11100000,
  B10000000
},
eye_happy_21_bmp[] =
{
  B00000000,
  B00000011,
  B00000111,
  B00001111,
  B00011100,
  B00011000,
  B00000000,
  B00000000
},
eye_happy_22_bmp[] =
{
  B11110000,
  B11111100,
  B11111110,
  B11111111,
  B00001111,
  B00000110,
  B00000000,
  B00000000
},
eye_happy_11_bmp[] =
{
  B00001111,
  B00111111,
  B01111111,
  B11111111,
  B11110000,
  B01100000,
  B00000000,
  B00000000
},
eye_happy_12_bmp[] =
{
  B00000000,
  B11000000,
  B11100000,
  B11110000,
  B00111000,
  B00011000,
  B00000000,
  B00000000
},
mouth_21_bmp[] =
{
  B00000000,
  B00000000,
  B00000000,
  B00000111,
  B00011111,
  B01111000,
  B11100000,
  B10000000
},
mouth_22_bmp[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11100000,
  B01111000,
  B00011110,
  B00000111
}, mouth_23_bmp[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000001,
  B00000111,
  B00011110,
  B01111000,
  B11100000
}, mouth_24_bmp[] = {
  B00000100,
  B00011110,
  B01111011,
  B11100011,
  B11111111,
  B00000000,
  B00000000,
  B00000000
}, mouth_11_bmp[]=
{
  B00100000,
  B01111000,
  B11011110,
  B11000111,
  B11111111,
  B00000000,
  B00000000,
  B00000000
},mouth_12_bmp[]=
{
  B00000000,
  B00000000,
  B00000000,
  B10000000,
  B11100000,
  B01111000,
  B00011110,
  B00000111
}, mouth_13_bmp[]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000111,
  B00011110,
  B01111000,
  B11100000
}, mouth_14_bmp[]=
{
  B00000000,
  B00000000,
  B00000000,
  B11100000,
  B11111000,
  B00011110,
  B00000111,
  B00000001
}
;


bool startup_done = false;

void fade_in(){
  for(uint8_t i = 0; i < 16; i++){
      nostril_r.setBrightness(i);
      nostril_l.setBrightness(i);
      mouth_back_l.setBrightness(i);
      mouth_back_r.setBrightness(i);
      mouth_front_l.setBrightness(i);
      mouth_front_r.setBrightness(i);
      eye_l.setBrightness(i);
      eye_r.setBrightness(i);
      delay(fade_delay);
  }

  startup_done = true;

}

void angrymouth(){
  uint16_t points[10] = {0};

  for(uint8_t i = 0; i < 10; i++){
    points[i] = random(8);
  }

  mouth_back_l.clear();
  mouth_front_l.clear();

  mouth_back_l.drawLine(0, points[0], 8, points[1], LED_ON);
  mouth_back_l.drawLine(8, points[1], 15, 4, LED_ON);
  mouth_front_l.drawLine(0, 4, 8, points[2], LED_ON); 
  mouth_front_l.drawLine(8, points[2], 15, points[0], LED_ON);

  mouth_back_l.writeDisplay();
  mouth_front_l.writeDisplay();

  mouth_back_r.clear();
  mouth_front_r.clear();

  mouth_back_r.drawLine(0, 4, 8, points[4], LED_ON);
  mouth_back_r.drawLine(8, points[4], 15, points[3], LED_ON);
  mouth_front_r.drawLine(0, points[3], 8, points[5], LED_ON); 
  mouth_front_r.drawLine(8, points[5], 15, 4, LED_ON);

  mouth_back_r.writeDisplay();
  mouth_front_r.writeDisplay();

  delay(30);
  
}

void loop() {
//  Eyes
  eye_r.clear();
  eye_r.drawBitmap(0, 0, eye_happy_11_bmp, 8, 8, LED_ON);
  eye_r.drawBitmap(8, 0, eye_happy_12_bmp, 8, 8, LED_ON);
  eye_r.writeDisplay();

  eye_l.clear();
  eye_l.drawBitmap(0, 0, eye_happy_21_bmp, 8, 8, LED_ON);
  eye_l.drawBitmap(8, 0, eye_happy_22_bmp, 8, 8, LED_ON);
  eye_l.writeDisplay();

//  eye_r.clear();
//  eye_r.drawBitmap(0, 0, eye_uwu_1_bmp, 8, 8, LED_ON);
//  eye_r.drawBitmap(8, 0, eye_uwu_2_bmp, 8, 8, LED_ON);
//  eye_r.writeDisplay();
//
//  eye_l.clear();
//  eye_l.drawBitmap(0, 0, eye_uwu_1_bmp, 8, 8, LED_ON);
//  eye_l.drawBitmap(8, 0, eye_uwu_2_bmp, 8, 8, LED_ON);
//  eye_l.writeDisplay();

    
  //Nostril 
  nostril_r.clear();
  nostril_r.drawBitmap(0, 0, nostril_2_bmp, 8, 8, LED_ON);
  nostril_r.writeDisplay();

  nostril_l.clear();
  nostril_l.drawBitmap(0, 0, nostril_1_bmp, 8, 8, LED_ON);
  nostril_l.writeDisplay();
  
  //Mouth
//  mouth_back_r.clear();
//  mouth_back_r.drawBitmap(0,0,mouth_11_bmp,8,8, LED_ON);
//  mouth_back_r.drawBitmap(8,0,mouth_12_bmp,8,8, LED_ON);
//  mouth_back_r.writeDisplay();
//
//  mouth_front_r.clear();
//  mouth_front_r.drawBitmap(0,0,mouth_13_bmp,8,8, LED_ON);
//  mouth_front_r.drawBitmap(8,0,mouth_14_bmp,8,8, LED_ON);
//  mouth_front_r.writeDisplay();
//
//  mouth_front_l.clear();
//  mouth_front_l.drawBitmap(0,0,mouth_21_bmp,8,8, LED_ON);
//  mouth_front_l.drawBitmap(8,0,mouth_22_bmp,8,8, LED_ON);
//  mouth_front_l.writeDisplay();
//
//  mouth_back_l.clear();
//  mouth_back_l.drawBitmap(0,0,mouth_23_bmp,8,8, LED_ON);
//  mouth_back_l.drawBitmap(8,0,mouth_24_bmp,8,8, LED_ON);
//  mouth_back_l.writeDisplay();

  if(!startup_done) {
    fade_in();
  }
  else {
    angrymouth();
  }
}
