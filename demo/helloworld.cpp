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

        engine.script.LoadScript("lua", "assets/scripts/helloworld.lua");
        
        //if engine.ECS.GetAppropriateSparseSet<Velocity>().Has()
        //cout << engine.ECS.Get<Sprite>(1).name << endl;
        //engine.script.ScriptMap["lua"]("its raininig...");
        engine.ECS.Create(Script({ "lua" }));
    };

    auto UpdateCallback = [](Engine& engine) {


        engine.graphics.Draw();
        //engine.script.Update();

        //cout << string('D', 1) << endl;

        /*engine.ECS.ForEach<Sprite, Position, Velocity>([&](EntityID entity) {


            engine.ECS.Get<Sprite>(entity).rotate -= 0.2;


            });*/

    };

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, SetupCallback, UpdateCallback);

    return 0;
}