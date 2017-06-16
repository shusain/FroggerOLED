
#include <vector>

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_GFX.h"

// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_SSD1306.h"


#define C_WIDTH 128
#define C_HEIGHT 64
#define C_GRID_SIZE 4

int count = 0;

class Rectangle {
    public:
        int x;
        int y;
        int w;
        int h;

        Rectangle(int x, int y, int w, int h){
          this->x = x;
          this->y = y;
          this->w = w;
          this->h = h;
        }

        bool intersects(Rectangle other){

          return !(
            this->x + this->w  <= other.x            ||
            this->x           >= other.x + other.w  ||
            this->y + this->h  <= other.y            ||
            this->y           >= other.y + other.h
          );
        }
        void move(int x, int y){
          this->x += x;
          this->y += y;
        }
        void show(Adafruit_SSD1306 display){
            display.fillRect(this->x, this->y, this->w, this->h, 1);
        }
        void debugInfo(){
            Serial.printf("x: %d", this->x);
            Serial.printf("y: %d", this->y);
            Serial.printf("w: %d", this->w);
            Serial.printlnf("h: %d", this->h);
        }

};



class Obstacle : public Rectangle {
    public:
        int speed;

        Obstacle(int x, int y, int w, int h, int s) : Rectangle(x,y,w,h){
            this->speed = s;
        }

        void update(){
          this->move(this->speed, 0);
          if(this->x > C_WIDTH + C_GRID_SIZE) {
            this->x = - this->w - C_GRID_SIZE;
          }
          if(this->x < - this->w - C_GRID_SIZE) {
            this->x = C_WIDTH + C_GRID_SIZE;
          }
        }
        void show(Adafruit_SSD1306 display){
          //Serial.println("showing obstacle");
          display.fillRect(this->x, this->y, this->w, this->h, 1);
        }
};

class Row : public Rectangle {
    public:
        std::vector<Obstacle> obstacles;
        bool inverted;
        
        Row(int y, int count, int speed, int obs_width, int spacing, int offset, bool inverted) : Rectangle(0, y, C_WIDTH, C_GRID_SIZE) {

          this->inverted = inverted;
          for(unsigned int i = 0; i < count; i++) {
            int x = i * spacing + offset;
            (this->obstacles).push_back(Obstacle(x, y, obs_width, C_GRID_SIZE, speed));
          }
        }
        void update() {
          for(unsigned int i = 0; i < this->obstacles.size(); i++) {
            this->obstacles[i].update();
          }
        }

        void show(Adafruit_SSD1306 display) {
          // Serial.println("showing row");
          // this->debugInfo();
          for(unsigned int i = 0; i < this->obstacles.size(); i++) {
            this->obstacles[i].show(display);
          }
        }

        Obstacle* hits(Rectangle collider){
          Obstacle* obstacle = nullptr;
          for(unsigned int i = 0; i < this->obstacles.size(); i++) {
            if(collider.intersects(this->obstacles[i])) {
                Serial.println("Found an intersection");
              obstacle = &(this->obstacles[i]);
            }
          }
          return obstacle;
        }
};



class Frog : public Rectangle {
    public:
        Obstacle *sitting_on;
        bool sitting_on_something;

        Frog(int x, int y, int size, Obstacle other) : Rectangle(x, y, size, size) {
          this->sitting_on = &other;
          this->sitting_on_something = false;
          Serial.println("Created a frog sitting on something");
        }
        Frog(int x, int y, int size) : Rectangle(x, y, size, size) {
          this->sitting_on = nullptr;
          this->sitting_on_something = false;
          Serial.println("Created a frog sitting on nothing");
        }
        void attach(Obstacle *other) {
          if(other){
            this->sitting_on = other;
            this->sitting_on_something = true;  
          }
          else{
            this->sitting_on_something = false;
          }
          
        }
        void update() {
          if(this->sitting_on_something) {
            Serial.println("Frog is on something");
            Serial.println(this->sitting_on->x);
          
            this->x += this->sitting_on->speed;
          }
          this->x = constrain(this->x, 0, C_WIDTH - this->w);
        }

        void show(Adafruit_SSD1306 display){
            // Serial.print("Showing the frog: ");
            // this->debugInfo();
            display.fillRect(this->x, this->y, this->w, this->h, count%2);
        }
};


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

Row rowArray[10] = {
    Row(            0, 1,    0,         C_WIDTH,   0,   0, true),
    Row(    C_GRID_SIZE, 1,    0,         C_WIDTH,   0,   0, true),
    Row(2 * C_GRID_SIZE, 2,  0.5, 4 * C_GRID_SIZE, 400,  10, true),
    Row(3 * C_GRID_SIZE, 3, -1.3, 2 * C_GRID_SIZE, 200,  30, true),
    Row(4 * C_GRID_SIZE, 2,  2.3, 3 * C_GRID_SIZE, 250,  25, true),
    Row(5 * C_GRID_SIZE, 1,    0,         C_WIDTH,   0,   0, true),
    Row(6 * C_GRID_SIZE, 3,  1.2, 1 * C_GRID_SIZE, 150, 100, false),
    Row(7 * C_GRID_SIZE, 2, -3.5, 1 * C_GRID_SIZE, 200, 150, false),
    Row(8 * C_GRID_SIZE, 2,    2, 2 * C_GRID_SIZE, 300,   0, false),
    Row(9 * C_GRID_SIZE, 2,    0,         C_WIDTH,   0,   0, true),
};

std::vector<Row> rows (rowArray, rowArray + sizeof(rowArray) / sizeof(rowArray[0]) );

// Handles game reset if the frog dies, or at the initial load.
void resetGame() {
  Serial.println("resetting game");
  frog = new Frog(C_WIDTH / 2, C_HEIGHT - C_GRID_SIZE, C_GRID_SIZE);
}

int moveReceived(String command){
    switch(command.charAt(0)){
        case 'u':
            Serial.println("Move Up");
            frog->debugInfo();
            frog->move(0, -C_GRID_SIZE);
        break;
        case 'd':
            Serial.println("Move Down");
            frog->debugInfo();
            frog->move(0, C_GRID_SIZE);
        break;
        case 'l':
            Serial.println("Move Left");
            frog->debugInfo();
            frog->move(-C_GRID_SIZE, 0);
        break;
        case 'r':
            Serial.println("Move Right");
            frog->debugInfo();
            frog->move(C_GRID_SIZE, 0);
        break;
    }
    return 0;
}

void setup()   {
  Particle.function("move", moveReceived);
  Serial.begin(9600);
  delay(20000);
  resetGame();

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  Serial.println("starting in 10s");
  delay(10000);
  display.display();
  delay(2000);

  display.clearDisplay();
  display.fillRect(1,1,100,100,1);
  display.display();
}


void loop() {
    count++;
  // Serial.println("looping");
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

  frog->attach(intersects);
  frog->update();
  frog->show(display);
  display.display();
  delay(30);
}
