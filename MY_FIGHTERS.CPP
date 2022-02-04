#include<iostream>
#include<SFML/Graphics.hpp>
#include<thread>
#include"animation.h"
#include"physics.h"
#include"player.h"
#include "rotatryPlayer.h"

using namespace sf;

int main(int argc,char* argv[])
{
    float x,y;
    cin>>x>>y;
   //x=0.1;
  // y=-2;

//*********window Settings******//
    RenderWindow gameWindow(VideoMode(800,600),"MY FIGHTERS");
    gameWindow.setPosition(Vector2i(500,500));
    gameWindow.setFramerateLimit(120);
    View view(Vector2f(0,0),Vector2f(4000,4000));
    gameWindow.setView(view);
    ContextSettings setting;    
    setting.antialiasingLevel=8;
//----------end of window settings--------//

std::cout<<"1"<<std::endl;


//*****************font setting***********//
    Font heal;
    heal.loadFromFile("resources/heal.ttf");
    Text Velocity,Accelration;
    Velocity.setCharacterSize(100);
    Velocity.setFont(heal);
    Velocity.setPosition(-1500,-1500);
//----------------END font setting---------//


std::cout<<"2"<<std::endl;

//********************test objects**************//

    physics phy;
    bool cas =true;


    player rect(200,200,10);
    rect.takesCommand=true;
    Texture tex;
   // tex.loadFromFile("resources/Idle.png");
    //rect.setTexture(&tex);
    rect.setPosition(500,00);
    rect.setFillColor(Color::Red);
    rect.resistance=0.05;
    animation anim(tex,6,1);
    anim.setSpriteAnimation("Idle",Vector2u(0.00,0.0),Vector2u(4,0.0));
    phy.colliderSystem.push_back(&rect);
   // rect.velocity=Vector2f(y,0);
    
    rectangleObjects rect1(14000,400,10000);
    rect1.setPosition(00,1300);
    rect1.moveable=false;
    rect1.gravity.y=00;
    rect1.setFillColor(Color::Yellow);
    phy.colliderSystem.push_back(&rect1);

   player king(200,200,5);
    king.setFillColor(Color::Green);
    king.move(Vector2f(3,0));
    king.velocity=Vector2f(x,y);
    phy.colliderSystem.push_back(&king);

    player rect2(200,200,20);
    rect2.takesCommand=true;
    rect2.setPosition(150,-3);
    rect2.setFillColor(Color::Red);
    phy.colliderSystem.push_back(&rect2);

    rectangleObjects strayObject(40,40,20);
    strayObject.setPosition(-1500,20);
    strayObject.setFillColor(Color::Red);
    phy.colliderSystem.push_back(&strayObject);

    std::cout<<"3"<<std::endl;
   /* textureObjects king(0.2,0.2);
    king.velocity=Vector2f(x,y);
    Texture tex;
    tex.loadFromFile("resources/Blesefore.png");
    king.setTexture(tex);
    king.setTextureRect(IntRect(tex.getSize().x/8,tex.getSize().y/5,tex.getSize().x/8,tex.getSize().y/5));
    */
//-------------------END test objects-----------//


//****************Constraints trhread-----//
physics* Constraints=&phy;
    

//----------end constraints thread----------//
std::cout<<"4"<<std::endl;
//*********main game loop*******//
    while (gameWindow.isOpen())
    {
      //  cout<<"event loop entered \n";
        Event event;
        gameWindow.pollEvent(event);
//************main game events**********//
/////////////////////////////////////////////////////////////////////////////////////     
////////////////////////////////////////////////////////////////////////////////////
   /*
    king.mainLoop();
    rect.mainLoop();
    Velocity.setString("x:"+to_string(int(king.velocity.x))+"  y:"+to_string(int(king.velocity.y)));
    gameWindow.draw(Velocity);
    if(king.bounds.intersects(rect.bounds)){
        if(cas){
    phy.collisionPhysics(king,rect);
    cas=false;
        }

    }
    else
    {
        cas=true;
    }
    */
   phy.join=false;
   std::thread physicsConstraintThread(&physics::runConstraints,Constraints);
   anim.play(rect,"Idle");
   phy.runSimulation(); 
  //******Simulator runner***//
  /*
    std::vector<collider*>::iterator itr;
     std::vector<collider*>::iterator i;
    for( itr=phy.colliderSystem.begin();itr<phy.colliderSystem.end();itr++)
    {
         collider* hello = *itr;
          for (i = itr+1.; i!=phy.colliderSystem.end() ; i++)
        {
            phy.collisionPhysics(**itr,**i);
         
        }
        hello->mainLoop();
        hello->velocity+=hello->gravity;

       
        
    }
    */
    //----------end simulator runner------//
   rect.playerMovement();
   
    gameWindow.draw(king);
    gameWindow.draw(rect1);
    gameWindow.draw(rect2);
    gameWindow.draw(rect);
   





 phy.join=true;

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//------------END main game events----------//
        gameWindow.display();
        gameWindow.clear(Color::Blue);
         physicsConstraintThread.join();
//*********close sfml window and application******//
        if(event.type == Event::Closed)
        {
           
            gameWindow.close();
            //system("exit");
        }
//---------application and window closed------//
    }

//----------main game loop end----------//

return 0;

}