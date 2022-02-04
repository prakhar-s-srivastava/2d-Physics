
/////////this class has animations stored
///      those animations are played when play function is called
///      the animations have a map with their respective names
///      the play function has a will complete option  
///      
///
/////////

#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include<map>
#include<string>

//********declaring all the namespaces required********//
using namespace std;
using namespace sf;
//--------------END declaring all the namespaces required-----//


class animation
{
private:
//*******variables*****//
    const Texture *spriteTexture;
    unsigned int imagesX=1,imagesY=1,offsetx,offsety;
    bool currentCondition=false;
    bool preeviousCondition=false;
    map<String,unsigned int> spriteAnimationStart;
    map<String,unsigned int> spriteAnimationEnd;
    float animationSpeed=0.3;
    Vector2u framesize;
    String previousAnimation;
//-------END variables------//

    /* data */

/////////******************************************/////////////////////////////////////////////
/////////---------------------------------------------/////////////////////////////////////

public:
    IntRect animationRectangle;
    Vector2f frameReducer=Vector2f(0,0);
    String currentAnimation;
    float timer=0;

     ///////////////
    //asiigns the animation to sprite
    //
    ///////////////
    void play(Sprite &sprite,const String&  name,const bool complete = false );

     ///////////////
    //asiigns the animation to shape
    //
    ///////////////   
    void play(RectangleShape &sprite,const String&  name,const bool complete = false );
    //debugging function
    void spitTexture(const String& name = "nothing");//soul purpose of this function is debugging
    
     ///////////////
    //assigns names and
    //start end position 
    //on texture sheet
    ///////////////
    void setSpriteAnimation(const String& name="nothing",const Vector2u &animationStart=Vector2u(0,0),const Vector2u &animationEnd = Vector2u(0,0) );
    ///////////////
    //takes in texture that it animates 
    //and the number of rows and columns
    ///////////////
    animation(const Texture &texture = Texture(),unsigned int X=1,unsigned int Y=1);

    animation(const animation &a);
    void operator=(const animation &a);
    ~animation();
};








#endif