// Daniel Shiffman
// http://codingrainbow.com
// http://patreon.com/codingrainbow

/* Implements the features of the Car object from the processing version,
 * but renamed to reflect that the logs also use this object.
 *
 * x: x position of the obstacle
 * y: y position of the obstacle
 * w: Obstacle width
 * h: Obstacle height
 * s: x speed of the obstacle
 */

#include "Adafruit_SSD1306.h"
#include "Rectangle.h"
#include "Constants.h"

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
          display.fillRect(this->x, this->y, this->w, this->h, 1);
        }
};
