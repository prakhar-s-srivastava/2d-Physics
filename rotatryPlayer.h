#ifndef ROTATRYPLAYER_H
#define ROTATRYPLAYER_H
#include "physics.h"
class rotatryPlayer :public rotatingObjects
{
private:
    /* data */
public:
    rotatryPlayer (float x,float y,float m);
    ~rotatryPlayer ();
    void playerMovement();
    float jumpTimer;
    bool takesCommand=false;
};





#endif