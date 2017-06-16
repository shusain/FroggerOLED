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

#ifndef Row_h_
#define Row_h_
class Row : public Rectangle {
    public:
        bool inverted;
        Row(int y, int count, int speed, int obs_width, int spacing, int offset, bool inverted);
        void update();
        Obstacle* hits(Rectangle collider);
};

#endif
