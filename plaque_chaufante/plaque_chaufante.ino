/**************************************************************************
  Vanier kevin 27/03/2022
 
 -> pin's I2C > A4 A5 addresse du bus I2C 0x3C pour l'ecran Oled
 -> faire un reset de la carte au moment de l'upload 
 -> utilisation de millis() pour ne pas bloquer l'algo avec delay()
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "max6675.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define RELAIS        2
#define LED           13 // la LED  build_in 
#define BUTTON_1      9
#define BUTTON_2      8
#define PROBE_TEMP    25
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
int etatbouton_1 = 0 ;
int etatbouton_2 = 0 ;
float temp_plate = 214.10 ; // pour test hors sonde 
float temp_select = 160 ;
float decalage = 0 ;
unsigned long startTime;
unsigned long currentTime;
const unsigned long period_sonde = 300; // temps mini de refresh pour le max_6675 (sinon freeze)



MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(RELAIS, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(PROBE_TEMP, INPUT);



  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D pour certains 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(1000);
  // Clear the buffer
  display.clearDisplay();
  display.display();
  delay(1000);
  display.clearDisplay();

  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    display.clearDisplay();
    //delay(10);
  }

  delay(100);
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    //delay(10);
  }

  delay(1000);

}

void aff_ecran() { 
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.print("Sonde type-K  MAX6675");


  display.setTextSize(1);
  display.setCursor(0, 25);
  display.setTextColor(SSD1306_WHITE);
  display.print("plaque ->");
  display.setTextSize(2);
  display.setCursor(56, 22);
  display.print(temp_plate);

  display.setTextSize(1);
  display.setCursor( 0, 55);
  display.setTextColor(SSD1306_WHITE);
  display.print("select ->");
  display.setTextSize(2);
  display.setCursor(56, 50 );
  display.print(temp_select);
  display.display();
}



void  read_tmp() {
  currentTime = millis();
    if (currentTime - startTime >= period_sonde)
    {
       temp_plate = thermocouple.readCelsius();
        startTime = currentTime;
    }
  
 
}

void temp_sel() {

  etatbouton_2 = digitalRead(BUTTON_2);

  if ( etatbouton_2 == 1) {
    temp_select = temp_select + 2 ;
  }
  if (temp_select >= 245 ) {
    temp_select = 245 ;
  }

  etatbouton_1 = digitalRead(BUTTON_1);

  if ( etatbouton_1 == 1) {
    temp_select = temp_select - 2 ;
  }
  if (temp_select <= 140 ) {
    temp_select = 140 ;
    
  }

}


void relais() {
  
  decalage = temp_plate - 10 ;
  
  if (temp_plate > temp_select ) {
    digitalWrite(RELAIS, LOW);
     digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(RELAIS, HIGH);
    digitalWrite(LED, HIGH);
  }



}


void debug_serial() {
  Serial.print("buttonState_1   ");
  Serial.println(etatbouton_1);
  Serial.print("buttonState_2   ");
  Serial.println(etatbouton_2);
  Serial.print("C =  ");
  Serial.println(temp_plate);
  Serial.print("TEMP_decalage   ");
  Serial.println(decalage );
}

void loop() { 
  temp_sel();
  read_tmp();
  relais() ;
  aff_ecran();
  debug_serial();
  

}
