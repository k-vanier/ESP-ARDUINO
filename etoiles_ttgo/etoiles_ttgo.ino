// Animates white pixels to simulate flying through a star field
// updated 2020-11-09 for 135x240 TFT display of TTGO T-Display

#include <SPI.h>
#include <TFT_eSPI.h>

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

int16_t h = 135;
int16_t w = 240;

// With 1024 stars the update rate is ~65 frames per second
#define NSTARS 9000
uint8_t sx[NSTARS] = {};
uint8_t sy[NSTARS] = {};
uint8_t sz[NSTARS] = {};

uint8_t za, zb, zc, zx;

// Fast 0-255 random number generator from http://eternityforest.com/Projects/rng.php:
uint8_t __attribute__((always_inline)) rng()
{
  zx++;
  za = (za^zc^zx);
  zb = (zb+za);
  zc = ((zc+(zb>>1))^za);
  return zc;
}



void setup() {
  za = random(256);
  zb = random(256);
  zc = random(256);
  zx = random(256);

  Serial.begin(115200);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_RED);

  // fastSetup() must be used immediately before fastPixel() to prepare screen
  // It must be called after any other graphics drawing function call if fastPixel()
  // is to be called again
  //tft.fastSetup(); // Prepare plot window range for fast pixel plotting
}

void loop()
{
  unsigned long t0 = micros();
  uint8_t spawnDepthVariation = 255;

  for(int i = 0; i < NSTARS; ++i)
  {
    if (sz[i] <= 1)
    {
      sx[i] = w/2 - h/2 + rng();
      sy[i] = rng();
      sz[i] = spawnDepthVariation--;
    }
    else
    {
      int old_screen_x = ((int)sx[i] - w/2) * 256 / sz[i] + w/2;
      int old_screen_y = ((int)sy[i] - h/2) * 256 / sz[i] + h/2;

      // This is a faster pixel drawing function for occassions where many single pixels must be drawn
      tft.drawPixel(old_screen_x, old_screen_y,TFT_BLACK);

      sz[i] -= 2;
      if (sz[i] > 1)
      {
        int screen_x = ((int)sx[i] - w/2) * 256 / sz[i] + w/2;
        int screen_y = ((int)sy[i] - h/2) * 256 / sz[i] + h/2;
  
        if (screen_x >= 0 && screen_y >= 0 && screen_x < 320 && screen_y < 240)
        {
          uint8_t r, g, b;
          r = g = b = 255 - sz[i];
          tft.drawPixel(screen_x, screen_y, tft.color565(r,g,b));
        }
        else
          sz[i] = 0; // Out of screen, die.
      }
    }
  }
  unsigned long t1 = micros();
  //static char timeMicros[8] = {};

 // Calcualte frames per second
  Serial.println(1.0/((t1 - t0)/1000000.0));
  Serial.println(zc) ;
}
