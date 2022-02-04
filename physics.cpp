#include"physics.h"
#define signum(x) (x<0? -1:1)
#define mod(x) (x<0? -x:x)
//*************collider*********//
collider::collider()
{
    velocity = Vector2f(0,0);
    acceleration = Vector2f(0,0);
    gravity= Vector2f(0,0.36);
}

collider::~collider()
{

}
//----------------------END collider------------//




//*********************textured Objects******************//
textureObjects::textureObjects(float x ,float y,float m)
{
    Sprite::setScale(x,y);
    mass=m;
    depth= atan(y/x);

}
textureObjects::~textureObjects()
{

}

void textureObjects::mainLoop()
{
    location = Sprite::getPosition();
    bounds = Sprite::getGlobalBounds();
    kinetics();
    Sprite::move(velocity);
}
//------------------END textured Objects----------------//



//********************rectangle Objects******************///
rectangleObjects::rectangleObjects(float x,float y,float m)
{
    RectangleShape::setSize(Vector2f(x,y));
    mass=m;
    RectangleShape:setOrigin(x/2,y/2);
    depth= atan(y/x);   
    physicsStepRatio.x *= x;
   physicsStepRatio.y *= y; 

}
rectangleObjects::~rectangleObjects()
{

}

void rectangleObjects::mainLoop()
{
    kinetics();
    if(moveable)
    RectangleShape::move(velocity);
    bounds=RectangleShape::getGlobalBounds();
    location= RectangleShape::getPosition();
    
}

//------------END rectangle Objects--------------//



//***************infinite mass***********//
infiniteMass::infiniteMass(float x ,float y)
{RectangleShape::setSize(Vector2f(x,y));
    depth = atan(y/x);
    velocity=Vector2f(0,0);
    gravity=Vector2f(0,0);
    }

infiniteMass::~infiniteMass(){}
//----------------END infinite mass-----//





//***************rotating objects************//
rotatingObjects::rotatingObjects(float x ,float y ,float m)
{
    RectangleShape::setSize(Vector2f(x,y));
    mass=m;
    RectangleShape::setOrigin(x/2,y/2);
    depth= atan(y/x);
    physicsStepRatio.x *= x;
   physicsStepRatio.y *= y; 
}

rotatingObjects::~rotatingObjects(){}

void rotatingObjects::mainLoop()
{
   // std::cout<<"hwll"<<resistance<<std::endl;
    kinetics();
     RectangleShape::move(velocity);
    RectangleShape::rotate(angularVelocity);
    location= RectangleShape::getPosition();
    bounds=RectangleShape::getGlobalBounds();
   
}


//-------------------END rotatinng objrcts---------//






//***********physics******************//
physics::physics()
{
}

physics::~physics()
{
}


void physics::collisionPhysics(collider& c1,collider& c2)
{
    
    if(c1.bounds.intersects(c2.bounds))
    {
        if(c1.mass!=0 && c2.mass!=0){
        std::cout<<"they collided"<<std::endl;
    float totalMass =c1.mass+c2.mass;
    Vector2f initialVelocity1,initialVelocity2,finalVelocity1,finalVelocity2;
    initialVelocity1=c1.velocity;
    initialVelocity2=c2.velocity;
    
    /*
    Vector2f totalMomentum = (operator*<float>(int(c1.mass),c1.velocity)+operator*<float>(int(c2.mass),c2.velocity));
    Vector2f sharedVelocity = operator/<float>(totalMomentum,int(totalMass));
        c1.velocity=operator*<float>(int(c1.mass),sharedVelocity);
        c2.velocity=operator*<float>(int(c2.mass),sharedVelocity);
        */
    c1.velocity.x= float((int(c1.mass-c2.mass)*int(initialVelocity1.x) +2*int(c2.mass)*int(initialVelocity2.x))/int(totalMass));
    c1.velocity.y = float((int(c1.mass-c2.mass)*int(initialVelocity1.y) +2*int(c2.mass)*int(initialVelocity2.y))/int(totalMass));
    c2.velocity.x= float((int(c2.mass-c1.mass)*int(initialVelocity2.x) +2*int(c1.mass)*int(initialVelocity1.x))/int(totalMass));
    c2.velocity.y = float((int(c2.mass-c1.mass)*int(initialVelocity2.y) +2*int(c1.mass)*int(initialVelocity1.y))/int(totalMass));
       // std::cout<<"c1 :"<<c1.velocity.x<<std::endl;
        //std::cout<<"c2 :"<<c2.velocity.x<<std::endl;
    finalVelocity1=c1.velocity;
    finalVelocity2=c2.velocity;
    //********************appliying rotation****************************//
        if(c1.location.y>c2.location.y)
        {
            c1.angularVelocity+=(c1.velocity.x-initialVelocity1.x)/int(totalMass);
        }
        else
        {
            c1.angularVelocity-=(c1.velocity.x-initialVelocity1.x)/int(totalMass);
        }
        
        if(c1.location.x>c2.location.x)
        {
            c1.angularVelocity+=(c1.velocity.y-initialVelocity1.y)/int(totalMass);
        }
        else
        {
            c1.angularVelocity-=(c1.velocity.y-initialVelocity1.y)/int(totalMass);
        }
        c2.angularVelocity += -1*c1.angularVelocity;
    /*    
    c1.velocity.x = signum(c1.location.x-c2.location.x);
        c1.velocity.y=signum(c1.location.y-c2.location.y);
    c2.velocity.x = signum(c2.location.x-c1.location.x);
        c2.velocity.y=signum(c2.location.y-c1.location.y);
        */
    //---------END appliyinig rotation-------//
    if(c1.mass>c2.mass)
    {
        constraints(c1,c2);
    }
    else
    {
        constraints(c2,c1);
    }
    /*
    int count=0;
       while(c1.bounds.intersects(c2.bounds) && count<10 ){
        if(c1.mass<=c2.mass)
       // c1.mainLoop();
       // c1.move(Vector2f(signum(c1.location.x-c2.location.x),signum(c1.location.y-c2.location.y)));
       constraints(c2,c1);
        if(c1.mass>c2.mass)
       // c2.mainLoop();
       // c2.move(Vector2f(signum(c2.location.x-c1.location.x),signum(c2.location.y-c1.location.y)));
        constraints(c1,c2);
        count++;
       }
        c1.velocity=finalVelocity1;
        c2.velocity=finalVelocity2;
        */
    }
    else{
         float totalMass =c1.mass+c2.mass+100*c1.mass+100*c2.mass;
    Vector2f initialVelocity1,initialVelocity2,finalVelocity;
    initialVelocity1=c1.velocity;
    initialVelocity2=c2.velocity;
        float Exchanger;
        if (c1.mass==0)
        {
          finalVelocity.y = float((int(c2.mass-c1.mass)*int(initialVelocity2.y) +2*int(c1.mass)*int(initialVelocity1.y))/int(totalMass));   
             c2.velocity.y=signum(c2.location.y-c1.location.y);
            while(c1.bounds.intersects(c2.bounds))
            {
            c2.mainLoop();
            }
            c2.velocity=finalVelocity;
            
        }
        else if(c2.mass==0)
        {
             finalVelocity.y= float((int(c1.mass-c2.mass)*int(initialVelocity1.y) +2*int(c2.mass)*int(initialVelocity2.y))/int(totalMass));
            c1.velocity.y=signum(c1.location.y-c2.location.y);
            while(c1.bounds.intersects(c2.bounds))
            {
            c1.mainLoop();
            }
            c1.velocity=finalVelocity;
        }
        
    }
        
    }

}



void physics::constraints(collider& c1,collider& c2)
{
    Vector2f moveAmount=Vector2f(0,0);
    Vector2f direction = c2.location-c1.location;
    float angle = atan(direction.y/direction.x);
    if(angle>-1*c1.depth && angle<c1.depth)
    {
        if(mod(direction.y)<(c1.bounds.height/2 + c2.bounds.height/2)-1)
        moveAmount.x= signum(c2.location.x-c1.location.x);
       
    }
    else
    {
        if(mod(direction.x)<(c1.bounds.width/2 + c2.bounds.width/2)-1)
        moveAmount.y= 0.2*signum(c2.location.y-c1.location.y);
          
    }
     c2.move(Vector2f(c2.physicsStepRatio.x* /*(c2.velocity.x+0.00001)*/ moveAmount.x,c2.physicsStepRatio.y* /*(c2.velocity.y+0.00001)*/ moveAmount.y));
    // c2.move(moveAmount);
     c1.move(Vector2f(c1.physicsStepRatio.x* /*(c1.velocity.x+0.00001)*/ moveAmount.x*-1,c1.physicsStepRatio.y* /*(c1.velocity.y+0.00001)*/ moveAmount.y*-1));
    //c1.move(Vector2f(moveAmount.x*-1,moveAmount.y*-1));
}

void physics::runConstraints(){ 
    int count=0;
    while (!join)
    {
       
    
     std::vector<collider*>::iterator itr;
     std::vector<collider*>::iterator i;
    for( itr=colliderSystem.begin();itr<colliderSystem.end();itr++)
    {
        
        

        for (i = colliderSystem.begin(); i!=itr ; i++)
        {
            collider* one=*itr;
            collider* two=*i;
            if(one->bounds.intersects(two->bounds))
            {
                if(one->mass>two->mass)
           constraints(**itr,**i);
           else
           {
              constraints(**i,**itr); 
           }
           
            }
        }
        
    }
    count++;
    }
    if(count>10)
    join=true;
}

void physics::collisionPhysics(infiniteMass& im,collider& c1)
{
    if(c1.bounds.intersects(im.getGlobalBounds())){
    Vector2f direction = c1.location-im.getPosition();
    float angle = atan(direction.y/direction.x);
    if(angle<im.depth&&angle>-1*im.depth)
    {
        c1.velocity.x = -1*c1.velocity.x;
        if(c1.location.x>im.getPosition().x)
        {
            c1.angularVelocity+=c1.velocity.y;
        }
        else
        {
         c1.angularVelocity-=c1.velocity.y;    
        }      
        if(c1.location.y>im.getPosition().y)
        {
            c1.angularVelocity+=c1.velocity.x;
        }
        else
        {
         c1.angularVelocity-=c1.velocity.x;    
        }      
    }    
    else
    {
        c1.velocity.y=-1*c1.velocity.y;
    }
    }

    //set angular velocity
    while(c1.bounds.intersects(im.getGlobalBounds()))
    {
        c1.mainLoop();
    }

}

void physics::collisionPhysics(collider &c1,infiniteMass &im)
{
    collisionPhysics(im,c1);
}

void physics::runSimulation()
{
    std::vector<collider*>::iterator itr;
     std::vector<collider*>::iterator i;
    for( itr=colliderSystem.begin();itr<colliderSystem.end();itr++)
    {
         collider* hello = *itr;
        hello->mainLoop();
        hello->velocity+=hello->gravity;

        for (i = itr+1.; i!=colliderSystem.end() ; i++)
        {
            collisionPhysics(**itr,**i);
         
        }
        
    }
    
    
}

//------------END physics-----------//