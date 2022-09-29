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
        engine.graphics.loadImage("carrot", "assets/images/carrot.jpg");
        engine.graphics.loadImage("liberty", "assets/images/liberty.jpg");

        engine.ECS.Create(Sprite("liberty", 0.5, 0, 0, 0, 1), Position());
        engine.ECS.Create(Sprite("carrot", 0.5, 0, 0, 0, 0), Position({1,2}), Velocity());

        
        cout << engine.ECS.entity << endl;
        
        
    };

    auto UpdateCallback = [&](Engine& engine) {


        engine.graphics.Draw();

        engine.ECS.ForEach<Sprite, Position>([&](EntityID entity) {


            engine.ECS.Get<Sprite>(entity).rotate -= 0.2;


            });

    };

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, SetupCallback, UpdateCallback);

    
    return 0;
}