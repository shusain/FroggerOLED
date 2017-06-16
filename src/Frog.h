// Daniel Shiffman
// http://codingrainbow.com
// http://patreon.com/codingrainbow

/* Implementation of the frog
 *
 * x: initial x position of the frog
 * y: initial y position of the frog
 * size: the width & height of the frog
 */

#ifndef Frog_h_
#define Frog_h_

class Frog: public Rectangle {
    public:
        Frog(int x, int y, int size);
        Frog(int x, int y, int size, Obstacle obs);
        void attach(Obstacle);
        void update();
};

#endif // Frog_h_
