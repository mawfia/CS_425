#include <iostream>
#include "Engine.h"
#include "Component.h"
#include "EntityComponentSystem.h"


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

        vector<string> explosions;
        explosions.push_back("assets/images/Spaceship.png");
        for (int i = 1; i < 32; i++) {
            explosions.push_back("assets/images/explosion" + to_string(i) + ".png");
        }

        engine.graphics.loadImages("spaceship", explosions);
        engine.graphics.loadImages("missile", vector<string>{"assets/images/Missile.png"});
        engine.graphics.loadImages("missile2", vector<string>{"assets/images/Missile2.png"});

        explosions.at(0) = "assets/images/EnemyShip.png";
        engine.graphics.loadImages("enemy", explosions);

        //engine.ECS.Create(Sprite("liberty", 0.5, 0, 0, 0, 1), Position());
        //engine.ECS.Create(Sprite("carrot", 0.5, 0, 0, 0, 0), Position({1,2}), Velocity());
        //engine.ECS.Create(Sprite("rat", 0.15, 0, 0, 0, 0), Position({ 1,2 }), Velocity(), Script({ "assets/scripts/rat.lua" }));
        //engine.ECS.Create(Sprite("cheese", 0.1, 0, .5, .5, 1), Position(), Script({ "assets/scripts/cheese.lua" }));
        //engine.ECS.Create(Sprite("tom", 0.15, 0, 0, 0, 0), Position({ 3,2 }), Script({ "assets/scripts/tom.lua" }));
        engine.ECS.Create(Sprite("spaceship", 0.1, 0, 0, 0, 0), Script("assets/scripts/spaceship.lua" ), Health(100));
        //engine.ECS.Create(Sprite("enemy", 0.1, 180, 0, 0, 0), Script( "assets/scripts/enemy.lua"), Health(100), Velocity(-0.005, 0.005));

        //engine.ECS.Create(Sprite("missile2", 0.1, 0, 0, 0, 0), Script("assets/scripts/missile2.lua"));

        //engine.script.LoadScript("lua", "assets/scripts/helloworld.lua");
        
        //if engine.ECS.GetAppropriateSparseSet<Velocity>().Has()
        //cout << engine.ECS.Get<Sprite>(1).name << endl;
        //engine.script.ScriptMap["lua"]("its raininig...");
        engine.ECS.Create(Script("assets/scripts/enemy_manager.lua"));

        engine.ECS.Create(Script("assets/scripts/missiles.lua"));
    };

    auto UpdateCallback = [](Engine& engine) {

        engine.graphics.Draw();
        engine.script.Update();
        engine.physics.Update();

    };

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, SetupCallback, UpdateCallback);

    return 0;
}