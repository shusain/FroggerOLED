// Daniel Shiffman
// http://codingrainbow.com
// http://patreon.com/codingrainbow

/* Implements a rectangle for testing collisions.
 *
 * x: left side x position
 * y: top side y position
 * w: width of this Rectangle
 * h: height of this Rectangle
 */

#include "Adafruit_SSD1306.h"
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

};
