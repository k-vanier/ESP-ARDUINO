/**************************************************************************
 Vanier kevin 27/04/2020
 pin I2C > A4 A5
 addresse du bus I2C 0x3C 
 
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 // 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

int intX=00;
int intY=00;
int intZ=00;

const int xPin = A2;
const int yPin = A1;
const int zPin = A0;

void setup() {
  Serial.begin(9600);

 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D pour certains 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(1000); 
  // Clear the buffer
  display.clearDisplay();
  display.display();
  delay(1000);
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
     display.clearDisplay();
    delay(10);
  }

  delay(300);
   for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(10);
  }

  delay(100);
}

void loop() {

affi_angle ();
}


void  affi_angle () {
  
int intX =analogRead(xPin);
int intY =analogRead(yPin);
int intZ =analogRead(zPin);

  display.clearDisplay();
  display.setTextSize(1);  
  display.setCursor(0,0);    
  display.setTextColor(SSD1306_WHITE); 
  display.print("accelerometre ADX335"); 

  display.setTextSize(2);  
  display.setCursor(0, 16);    
  display.setTextColor(SSD1306_WHITE); 
  display.print("axe_X ");  display.println(intX); 

 
  display.setTextSize(2);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 33);   
  display.print("axe_Y ");  display.println(intY); 
 

  display.setTextSize(2);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 50);   
  display.print("axe_Z ");  display.println(intZ); 
  display.display();

}
