#ifndef PLAYER_H
#define PLAYER_H
#include"physics.h"

class player:public rectangleObjects
{
private:
    int jumpTimer=0;
    
    /* data */
public:
    float takesCommand=false;
    player(float X=1,float Y=1,float m=1);
    ~player();
    void playerMovement();
};




#endif