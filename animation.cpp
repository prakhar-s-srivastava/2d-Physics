#include"animation.h"





//***************constructor & deconstructor**************//


animation::animation(const Texture& texture,unsigned int X,unsigned int Y)
{
    spriteTexture=&texture;
    imagesX=X;
    imagesY=Y;
    framesize.x= spriteTexture->getSize().x/imagesX;
    framesize.y = spriteTexture->getSize().y/imagesY;


    
}

//assignment operator
void animation::operator=(const animation &a) 
{
    spriteTexture=a.spriteTexture;
    animationRectangle=a.animationRectangle;
    framesize=a.framesize;
    spriteAnimationStart=a.spriteAnimationStart;
    spriteAnimationEnd=a.spriteAnimationEnd;
    timer=a.timer;
    animationSpeed=a.animationSpeed;
    previousAnimation=a.previousAnimation;
    currentAnimation=a.currentAnimation;
    imagesX=a.imagesX;
    imagesY=a.imagesY;
    offsetx=a.offsetx;
    offsety=a.offsety;
    frameReducer=a.frameReducer;
    currentCondition=a.currentCondition;
    preeviousCondition=a.preeviousCondition;
}


//copy constructor
animation::animation(const animation &a) 
{
    spriteTexture=a.spriteTexture;
    animationRectangle=a.animationRectangle;
    framesize=a.framesize;
    spriteAnimationStart=a.spriteAnimationStart;
    spriteAnimationEnd=a.spriteAnimationEnd;
    timer=a.timer;
    animationSpeed=a.animationSpeed;
    previousAnimation=a.previousAnimation;
    currentAnimation=a.currentAnimation;
    imagesX=a.imagesX;
    imagesY=a.imagesY;
    offsetx=a.offsetx;
    offsety=a.offsety;
    frameReducer=a.frameReducer;
    currentCondition=a.currentCondition;
    preeviousCondition=a.preeviousCondition;

}
animation::~animation()
{

}
//--------------------constructor & deconstructor-----------------//




void animation::setSpriteAnimation(const String& name,const Vector2u &animationStart,const Vector2u &animationEnd )
{
    spriteAnimationStart.insert(pair<string,unsigned int>(name,imagesX*animationStart.y+animationStart.x));
    spriteAnimationEnd.insert(pair<string,unsigned int>(name,imagesX*animationEnd.y+animationEnd.x));
    

}


void animation::play(Sprite &sprite,const String& name,const bool complete)
{

if(!currentCondition){
    //check if new animation is being played;
    if (currentAnimation != name)
    {
        timer=spriteAnimationStart[name];
        previousAnimation=currentAnimation;
        currentAnimation=name;
        preeviousCondition=currentCondition;
        currentCondition=complete;

    }
}
else
{
    if (currentAnimation != name &&timer>= spriteAnimationEnd[currentAnimation] )
    {
        timer=spriteAnimationStart[name];
        previousAnimation=currentAnimation;
        currentAnimation=name;
        preeviousCondition=currentCondition;
        currentCondition=complete;

    }
}
    

    //check is timer reached its limit
    if (timer> spriteAnimationEnd[currentAnimation])
    {
        timer = spriteAnimationStart[currentAnimation];
    }

    timer+=animationSpeed;

    //set texture rectagle
    offsetx= (int(timer)%imagesX);
    offsety= int(timer/imagesX);
    animationRectangle = IntRect(offsetx*framesize.x,offsety*framesize.y,framesize.x-frameReducer.x,framesize.y-frameReducer.y);
    sprite.setTextureRect(animationRectangle);

}

void animation::play(RectangleShape &sprite,const String& name,const bool complete)
{
   
if(!currentCondition){
    //check if new animation is being played;
    if (currentAnimation != name)
    {
        timer=spriteAnimationStart[name];
        previousAnimation=currentAnimation;
        currentAnimation=name;
        preeviousCondition=currentCondition;
        currentCondition=complete;

    }
}
else
{
    if (currentAnimation != name &&timer>= spriteAnimationEnd[currentAnimation] )
    {
        timer=spriteAnimationStart[name];
        previousAnimation=currentAnimation;
        currentAnimation=name;
        preeviousCondition=currentCondition;
        currentCondition=complete;

    }
}
    

    //check is timer reached its limit
    if (timer> spriteAnimationEnd[currentAnimation])
    {
        timer = spriteAnimationStart[currentAnimation];
    }

    timer+=animationSpeed;

    //set texture rectagle
    offsetx= (int(timer)%imagesX);
    offsety= int(timer/imagesX);
    animationRectangle = IntRect(offsetx*framesize.x,offsety*framesize.y,framesize.x-frameReducer.x,framesize.y-frameReducer.y);
    sprite.setTextureRect(animationRectangle);
}

//*****************Debuging functions*****************//
void animation::spitTexture(const String& name )
{
    cout<<spriteAnimationStart[name]<<endl;
    cout<<spriteAnimationEnd[name]<<endl;
}






//------------------END Debugging functions----------//