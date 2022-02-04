#include "player.h"
using namespace sf;

player::player(float X, float Y,float m)
{
    mass=m;
    RectangleShape::setScale(Vector2f(X,Y));
}

player::~player()
{
}

void player::playerMovement()
{
    if(!takesCommand) return ; 
    if(Keyboard::isKeyPressed(Keyboard::Up) && jumpTimer<=0)
    {       
           RectangleShape::move(0,-30);
           velocity.y-=30;
           jumpTimer=120; 
                 
    }
    else
    {
            if(jumpTimer>0) {  
             jumpTimer--;
            // std::cout<<"jumper reduced"<<std::endl;
            }
    }
    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        velocity.x=-3;
    }
    else if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        velocity.x=3;
    }
    
}