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

#ifndef Rectangle_h_
#define Rectangle_h_
#include "Adafruit_SSD1306.h"
class Rectangle {
    public:
        int x;
        int y;
        int w;
        int h;
        Rectangle(int x, int y, int w, int h);

        bool intersects(Rectangle other);
        void move(int x, int y);
        void show(Adafruit_SSD1306 display);

};

#endif
