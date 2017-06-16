
#include <vector>


// This #include statement was automatically added by the Particle IDE.
#include "Obstacle.h"

// This #include statement was automatically added by the Particle IDE.
#include "Row.h"

// This #include statement was automatically added by the Particle IDE.
#include "Rectangle.h"

// This #include statement was automatically added by the Particle IDE.
#include "Frog.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_SSD1306.h"

#include "Constants.h"

/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#define OLED_RESET D4
Adafruit_SSD1306 display(OLED_RESET);

// #define NUMFLAKES 10
// #define XPOS 0
// #define YPOS 1
// #define DELTAY 2


// #define LOGO16_GLCD_HEIGHT 16
// #define LOGO16_GLCD_WIDTH  16
// static const unsigned char logo16_glcd_bmp[] =
// { 0B00000000, 0B11000000,
//   0B00000001, 0B11000000,
//   0B00000001, 0B11000000,
//   0B00000011, 0B11100000,
//   0B11110011, 0B11100000,
//   0B11111110, 0B11111000,
//   0B01111110, 0B11111111,
//   0B00110011, 0B10011111,
//   0B00011111, 0B11111100,
//   0B00001101, 0B01110000,
//   0B00011011, 0B10100000,
//   0B00111111, 0B11100000,
//   0B00111111, 0B11110000,
//   0B01111100, 0B11110000,
//   0B01110000, 0B01110000,
//   0B00000000, 0B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Frog *frog;

int width = 128;
int height = 96;
int grid_size = 50;

Row rowArray[10] = {
    Row(            0, 1,    0,         width,   0,   0, true),
    Row(    grid_size, 1,    0,         width,   0,   0, true),
    Row(2 * grid_size, 2,  0.5, 4 * grid_size, 400,  10, true),
    Row(3 * grid_size, 3, -1.3, 2 * grid_size, 200,  30, true),
    Row(4 * grid_size, 2,  2.3, 3 * grid_size, 250,  25, true),
    Row(5 * grid_size, 1,    0,         width,   0,   0, true),
    Row(6 * grid_size, 3,  1.2, 1 * grid_size, 150, 100, false),
    Row(7 * grid_size, 2, -3.5, 1 * grid_size, 200, 150, false),
    Row(8 * grid_size, 2,    2, 2 * grid_size, 300,   0, false),
    Row(9 * grid_size, 2,    0,         width,   0,   0, true),
};

std::vector<Row> rows (rowArray, rowArray + sizeof(rowArray) / sizeof(rowArray[0]) );

// Handles game reset if the frog dies, or at the initial load.
void resetGame() {
  frog = new Frog(width / 2, height - grid_size, grid_size);
}

void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);

  display.clearDisplay();

  //Begin game logic setup

  width = 128;
  resetGame();
}


void loop() {
  display.clearDisplay();

  Obstacle* intersects = NULL;

  for(unsigned int i = 0; i < rows.size(); i++) {
    rows.at(i).show(display);
    rows[i].update();
    if(frog->intersects(rows[i])) {
      intersects = rows[i].hits(*frog);
      if((intersects != NULL) ^ rows[i].inverted) {
        resetGame();
      }
    }
  }

  frog->attach(*intersects);
  frog->update();
  frog->show(display);
}
