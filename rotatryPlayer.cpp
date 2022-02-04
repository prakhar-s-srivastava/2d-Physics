#include "rotatryPlayer.h"

rotatryPlayer ::rotatryPlayer (float x,float y,float m)
{
    RectangleShape::setSize(Vector2f(x,y));
    mass=m;
}

rotatryPlayer ::~rotatryPlayer ()
{
}

void rotatryPlayer::playerMovement()
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