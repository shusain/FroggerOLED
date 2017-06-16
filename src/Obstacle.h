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

#ifndef Obstacle_h_
#define Obstacle_h_
#include "Rectangle.h"
class Obstacle : public Rectangle {
    public:
        int speed;
        Obstacle(int x, int y, int w, int h, int s);
        void update();
};
#endif
