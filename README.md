# FroggerOLED

A Particle project for running a "frogger like" game on an OLED display.  The application.cpp has the core functions of the application that were ported from the CodingTrain version of the game and drawing routines.

In the application.cpp file there is a call to `Particle.function("move", moveHandler);` that allows you to use the web hook for your device to call the move function, the function takes a string command and reads the first character of the string to decide what direction to move, 'u' for up, 'd' for down, 'l' for left, 'r' for right.

The game is usig a b/w OLED display and due to that restriction the player flashes on screen to indicate their position when either on a black or white object.

### Example

https://www.youtube.com/watch?v=9RTrC0jM-hg


Based on the [CodingTrain](https://github.com/CodingTrain/Frogger) Frogger Example
