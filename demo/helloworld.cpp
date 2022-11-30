#include <iostream>
#include "Engine.h"
#include "Component.h"
#include "EntityComponentSystem.h"


using namespace std;


int main( int argc, const char* argv[] ) {

    using namespace engine;

    auto SetupCallback = [](Engine& engine) { 
       
        engine.sound.LoadSound("blurp", "assets/sounds/blurp.wav");
        engine.sound.LoadSound("win", "assets/sounds/win.mp3");
        engine.sound.LoadSound("missile", "assets/sounds/missile.mp3");
        engine.sound.LoadSound("missile2", "assets/sounds/missile2.mp3");
        engine.sound.LoadSound("explosion1", "assets/sounds/explosion1.wav");
        engine.sound.LoadSound("explosion2", "assets/sounds/explosion2.wav");
        engine.sound.LoadSound("small_explosion", "assets/sounds/small_explosion.mp3");

        vector<string> explosions;
        explosions.push_back("assets/images/Spaceship.png");
        for (int i = 1; i < 32; i++) {
            explosions.push_back("assets/images/explosion" + to_string(i) + ".png");
        }

        engine.graphics.loadImages("spaceship", explosions);
        engine.graphics.loadImages("missile", vector<string>{"assets/images/Missile.png"});
        engine.graphics.loadImages("space", vector<string>{"assets/images/space1.jpg"});
        engine.graphics.loadImages("rock", vector<string>{"assets/images/rock.png"});
        engine.graphics.loadImages("missile2", vector<string>{"assets/images/Missile2_1.png", "assets/images/Missile2_2.png", "assets/images/Missile2_3.png"});

        explosions.at(0) = "assets/images/EnemyShip.png";
        engine.graphics.loadImages("enemy", explosions);

        engine.ECS.Create(Sprite("space", 1, 0, 0, 0, 1));
        engine.ECS.Create(Sprite("rock", 0.3, 0, -0.5, -0.5, 0));
        engine.ECS.Create(Sprite("spaceship", 0.1, 0, 0, 0, 0), Script("assets/scripts/spaceship.lua" ), Health(100));
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