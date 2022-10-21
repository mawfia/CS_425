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
        engine.graphics.loadImage("liberty", "assets/images/liberty.jpg");
        engine.graphics.loadImage("rat", "assets/images/rat.jpg");
        engine.graphics.loadImage("cheese", "assets/images/cheese.jpg");

        //engine.ECS.Create(Sprite("liberty", 0.5, 0, 0, 0, 1), Position());
        //engine.ECS.Create(Sprite("carrot", 0.5, 0, 0, 0, 0), Position({1,2}), Velocity());
        engine.ECS.Create(Sprite("rat", 0.15, 0, 0, 0, 0), Position({ 1,2 }), Velocity(), Script({ "assets/scripts/rat.lua" }));
        engine.ECS.Create(Sprite("cheese", 0.1, 0, .5, .5, 1), Position(), Script({ "assets/scripts/cheese.lua" }));

        //engine.script.LoadScript("lua", "assets/scripts/helloworld.lua");
        
        //if engine.ECS.GetAppropriateSparseSet<Velocity>().Has()
        //cout << engine.ECS.Get<Sprite>(1).name << endl;
        //engine.script.ScriptMap["lua"]("its raininig...");
        //engine.ECS.Create(Script({ "assets/scripts/helloworld.lua" }));
    };

    auto UpdateCallback = [](Engine& engine) {


        engine.graphics.Draw();
        engine.script.Update();

        //engine.script.ScriptMap["lua"]();

        //engine.script.lua.script_file("assets/scripts/helloworld.lua")(2);

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