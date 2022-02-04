#ifndef PHYSICS_H
#define PHYSICS_H
#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<vector>

using namespace sf;


class collider{
    public:
    float angularVelocity=0;
    FloatRect bounds ;
    float mass,depth=0;
    float threshold=0.08;
    float resistance=0.05;
    Vector2f location;
    Vector2f velocity;
    Vector2f acceleration;
    Vector2f gravity ;
    float ratioX;
    float ratioY;
    Vector2f physicsStepRatio=Vector2f(0.005,0.005);
    bool moveable=true;
    
    void kinetics()
    {
        
        if(velocity.x !=0)
        {
            if(velocity.x>threshold)
            velocity.x -= resistance;
            else if(velocity.x<-1*threshold)
            velocity.x+=resistance;
            else
            velocity.x=0;
        }
        if(velocity.y !=0)
        {
            if(velocity.y>threshold)
            velocity.y-=resistance;
            else if(velocity.y<-1* threshold)
            velocity.y+=resistance;
            else
            velocity.y=0;
        }
        velocity.x += acceleration.x;
        velocity.y += acceleration.y;

         if(angularVelocity !=0)
        {
            if(angularVelocity>threshold)
            angularVelocity -= resistance;
            else if(angularVelocity<-1*threshold)
            angularVelocity+=resistance;
            else
            angularVelocity=0;
        }

        

        
    }
    virtual void mainLoop(){
        
    }
    virtual void move(Vector2f amount){

    }
    
    collider();
    ~collider();
  private:
    
};


class textureObjects :public collider,public Sprite
{
    public:
    textureObjects(float x=1,float y=1,float m=1);
    ~textureObjects();

    void mainLoop();
        

};
class rectangleObjects :public collider,public RectangleShape
{
    public:
    
    rectangleObjects(float x=1,float y=1,float m=1);
    ~rectangleObjects();
    void move(Vector2f amount){
        if(moveable)
        RectangleShape::move(amount);
    }
    void mainLoop();
        

};

class infiniteMass:public rectangleObjects
{
    public:
    infiniteMass(float x=1 ,float y=1);
    ~infiniteMass();
    void mainLoop(){
     }
    float depth ;


};
class rotatingObjects:public collider,public RectangleShape
 {
     public:
     rotatingObjects(float x=1,float y =1,float m=1);
     ~rotatingObjects();
      void move(Vector2f amount){
          if(moveable)
        RectangleShape::move(amount);
    }
     void mainLoop();
     

 };

class physics
{
private:
    /* data */
public:
    void collisionPhysics(collider& c1,collider& c2);
     void collisionPhysics(collider& c1,infiniteMass& im);
     void collisionPhysics(infiniteMass& im,collider& c1);
     void runSimulation();
     void runConstraints();
     void constraints(collider& c1,collider& c2);
     std::vector<collider*> colliderSystem;
    bool join=false;
    physics();
    ~physics();
};

 



#endif