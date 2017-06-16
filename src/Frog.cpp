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

#include "Rectangle.h"
#include "Obstacle.h"
#include "Constants.h"

#include "Adafruit_SSD1306.h"
class Frog : Rectangle {
    public:
        Obstacle *sitting_on;
        int size;

        Frog(int x, int y, int size, Obstacle other) : Rectangle(x, y, size, size) {

          this->sitting_on = &other;
        }
        Frog(int x, int y, int size) : Rectangle(x, y, size, size) {
          this->sitting_on = NULL;
        }
        void attach(Obstacle other) {
          this->sitting_on = &other;
        }
        void update() {

          if(this->sitting_on != NULL) {
            this->x += this->sitting_on->speed;
          }
          this->x = constrain(this->x, 0, C_WIDTH - this->w);
        }

        void show(Adafruit_SSD1306 display){
            display.fillRect(this->x, this->y, this->size, this->size, 1);
        }
};
