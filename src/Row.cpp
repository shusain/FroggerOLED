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
#include <vector>
#include "Constants.h"

class Row : Rectangle {
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
          for(unsigned int i = 0; i < this->obstacles.size(); i++) {
            this->obstacles[i].show(display);
          }
        }

        Obstacle* hits(Rectangle collider){
          Obstacle* obstacle = NULL;
          for(unsigned int i = 0; i < this->obstacles.size(); i++) {
            if(collider.intersects(this->obstacles[i])) {
              obstacle = &(this->obstacles[i]);
            }
          }
          return obstacle;
        }
};
