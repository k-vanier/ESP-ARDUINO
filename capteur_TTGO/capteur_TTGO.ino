/*  
 vanier kevin 05/10/2024
 capteur de pouls + temperature 

 ####################################################################*/

//affichage
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
#define TFT_GREY 0x5AEB // New colour





void setup(void) {
  tft.init();
  tft.setRotation(3);
  
}

void loop() {
    


//deuxieme champ 
  tft.setCursor(0, 55, 5);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(4);
  tft.print("pouls-> "); tft.println(beatsPerMinute);
  
  


  
  
}



