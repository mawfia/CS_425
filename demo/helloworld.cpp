#include <iostream>
#include "Engine.h"
#include "Component.h"

#include "EntityComponentSystem.cpp"


using namespace std;


/*
void SetupCallback() {
    cout << "Setup complete." << '\n';
}

void UpdateCallback(char key) {
    cout << key << ' ';
}*/


int main( int argc, const char* argv[] ) {

    using namespace engine;

    auto SetupCallback = [](Engine& engine) { 
        
        

        engine.sound.LoadSound("blurp", "assets/sounds/blurp.wav");
        engine.sound.LoadSound("win", "assets/sounds/win.mp3");
        engine.graphics.loadImage("carrot", "assets/images/carrot.jpg");
        engine.graphics.loadImage("liberty", "assets/images/liberty.png");
        engine.graphics.loadImage("rat", "assets/images/rat.png");
        engine.graphics.loadImage("tom", "assets/images/tom.png");
        engine.graphics.loadImage("cheese", "assets/images/cheese.png");
        engine.graphics.loadImage("spaceship", "assets/images/Spaceship.png");
        engine.graphics.loadImage("missile", "assets/images/Missile.png");
        engine.graphics.loadImage("enemy", "assets/images/EnemyShip.png");


        //engine.ECS.Create(Sprite("liberty", 0.5, 0, 0, 0, 1), Position());
        //engine.ECS.Create(Sprite("carrot", 0.5, 0, 0, 0, 0), Position({1,2}), Velocity());
        //engine.ECS.Create(Sprite("rat", 0.15, 0, 0, 0, 0), Position({ 1,2 }), Velocity(), Script({ "assets/scripts/rat.lua" }));
        //engine.ECS.Create(Sprite("cheese", 0.1, 0, .5, .5, 1), Position(), Script({ "assets/scripts/cheese.lua" }));
        //engine.ECS.Create(Sprite("tom", 0.15, 0, 0, 0, 0), Position({ 3,2 }), Script({ "assets/scripts/tom.lua" }));
        engine.ECS.Create(Sprite("spaceship", 0.1, 0, 0, 0, 0), Script({ "assets/scripts/spaceship.lua" }), Health(100));
        engine.ECS.Create(Sprite("enemy", 0.1, 180, 0, 0, 0), Script({ "assets/scripts/enemy.lua" }), Health(100));

        EntityID test = engine.ECS.Create(Sprite());
        engine.ECS.Destroy(test);

        //engine.script.LoadScript("lua", "assets/scripts/helloworld.lua");
        
        //if engine.ECS.GetAppropriateSparseSet<Velocity>().Has()
        //cout << engine.ECS.Get<Sprite>(1).name << endl;
        //engine.script.ScriptMap["lua"]("its raininig...");
        engine.ECS.Create(Script({ "assets/scripts/missiles.lua" }));
    };

    auto UpdateCallback = [](Engine& engine) {


        engine.graphics.Draw();
        engine.script.Update();

        //engine.script.ScriptMap["lua"]();

        //engine.script.lua.script_file("assets/scripts/helloworld.lua")(2);

        //cout << string('D', 1) << endl;

        engine.ECS.ForEach<Sprite, Health>([&](EntityID id) {


            auto& entity = engine.ECS.Get<Sprite>(id);

            if (entity.x > .9) entity.x = .9;
            if (entity.x < -.9) entity.x = -.9;
            if (entity.y > .9) entity.y = .9;
            if (entity.y < -.9) entity.y = -.9;



            if (entity.name == "enemy") {


                engine.ECS.ForEach<Sprite, Health>([&](EntityID id2) {

                    auto& entity2 = engine.ECS.Get<Sprite>(id2);

                    if (entity2.name == "missile" || entity2.name == "spaceship") {


                        bool collisionX = entity.x + entity.scale >= entity2.x - entity2.scale && entity2.x + entity2.scale >= entity.x - entity.scale;
                        bool collisionY = entity.y + entity.scale >= entity2.y - entity2.scale && entity2.y + entity2.scale >= entity.y - entity.scale;

                        if (collisionX && collisionY) {
                            
                            engine.ECS.Get<Health>(id).percent = 0;
                            engine.ECS.Get<Health>(id2).percent = 0;
                            
                        }


                    }

                    

                });
            }

        });

    };

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, SetupCallback, UpdateCallback);

    return 0;
}