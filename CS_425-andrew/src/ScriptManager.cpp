#pragma once

#include <iostream>
#include <unordered_map>

#include "ScriptManager.h"
#include "Engine.h"


using namespace std;

namespace engine {

	using namespace sol;

	ScriptManager::ScriptManager(){ }

	void ScriptManager::Startup() {

		lua.open_libraries(lib::base, lib::math, lib::table, lib::os);
		lua.script("math.randomseed(os.time())");
		//lua.script("print('bark bark bark')");
		
		//lua["GetSprite"] = [&](EntityID e) { return engine->ECS.Get<Sprite>(e); };
		//lua["myfunc"] = []() { cout << "Hello Lua World" << endl; };

		
		sol::usertype<Sprite> sprite_type = lua.new_usertype<Sprite>("Sprite",

			sol::constructors<Sprite(), Sprite(const string&), Sprite(const string&, float), Sprite(const string&, float, float), Sprite(const string&, float, float, float, float, float)>()

			);

		sprite_type["name"] = &Sprite::name;
		sprite_type["scale"] = &Sprite::scale;
		sprite_type["rotate"] = &Sprite::rotate;
		sprite_type["x"] = &Sprite::x;
		sprite_type["y"] = &Sprite::y;
		sprite_type["z"] = &Sprite::z;
		sprite_type["index"] = &Sprite::index;


		sol::usertype<Script> script_type = lua.new_usertype<Script>("Script",

			sol::constructors< Script(), Script(const string&) >()

			);

		script_type["name"] = &Script::name;

		sol::usertype<Position> position_type = lua.new_usertype<Position>("Position",

			sol::constructors< Position(), Position(float, float)>()

			);

		position_type["x"] = &Position::x;
		position_type["y"] = &Position::y;

		sol::usertype<SpritePos> spritePos_type = lua.new_usertype<SpritePos>("SpritePos", sol::constructors<SpritePos()>(), "x", &SpritePos::x, "y", &SpritePos::y);
		spritePos_type["x"] = &SpritePos::x;
		spritePos_type["y"] = &SpritePos::y;




		sol::usertype<Health> health_type = lua.new_usertype<Health>("Health",

				sol::constructors< Health(), Health(double) >()

			);

		health_type["percent"] = &Health::percent;

		sol::usertype<Velocity> velocity_type = lua.new_usertype<Velocity>("Velocity",

			sol::constructors< Velocity(), Velocity(float, float)>()

			);

		velocity_type["x"] = &Velocity::x;
		velocity_type["y"] = &Velocity::y;

		sol::usertype<Acceleration> acceleration_type = lua.new_usertype<Acceleration>("Acceleration",

			sol::constructors< Acceleration(), Acceleration(float, float)>()

			);

		acceleration_type["x"] = &Acceleration::x;
		acceleration_type["y"] = &Acceleration::y;

		lua["GetSprite"] = [&](EntityID e) -> Sprite& { return engine->ECS.Get<Sprite>(e); };
		lua["GetScript"] = [&](EntityID e) -> Script& { return engine->ECS.Get<Script>(e); };
		lua["GetVelocity"] = [&](EntityID e) -> Velocity& { return engine->ECS.Get<Velocity>(e); };
		lua["GetAcceleration"] = [&](EntityID e) -> Acceleration& { return engine->ECS.Get<Acceleration>(e); };
		lua["GetHealth"] = [&](EntityID e) -> Health& { return engine->ECS.Get<Health>(e); };
		lua["Keys"] = &engine->input.keys;
		lua["PlaySound"] = [&](string name) -> void { engine->sound.PlaySound(name); };
		//lua["spawn"] = true;
		lua.set("spawn", 0);
		lua.set("rate1", 0);
		lua.set("rate2", 0);
		
		lua["maxSpeed"] = 0.5;
		lua["maxForce"] = 0.5;
		lua["desiredSeparation"] = 0.1;
		lua["neighbordist"] = 50;
		lua.set("max_enemy", 3);
		lua["CreateSprite"] = [&](Sprite& sprite) -> EntityID { return engine->ECS.Create<Sprite>(sprite); };
		lua["DestroyEntity"] = [&](EntityID e) -> void { engine->ECS.Destroy(e); };
		lua["PathFind"] = [&](Sprite& seekerSprite, SpritePos goal, SpritePos seeker) -> void { engine->path.findPath(seekerSprite, goal, seeker, engine->ECS); };

	}

	bool ScriptManager::LoadScript(const string& name, const string& path) {


		//load_result fx = lua.load_file(path);

		ScriptMap[path] = lua.load_file(path);
		//ScriptMap[name] = path;

		//fx("Hello apple world!");

		/*
		if (!ScriptMap[name].valid()) {
			sol::error err = ScriptMap[name];
			cerr << "Failed to load script: " + name + " into the program." << endl;
			return false;
		}*/

		//ScriptMap[name] = fx;

		return true;
	}

	void ScriptManager::Update(void) {
		
		
		for (const auto& [entityID, script] : engine->ECS.GetAppropriateSparseSet<Script>()) {

			LoadScript(script.name, script.name);
			//load_result fx = lua.load_file()
			
			//load_result fx = lua.load_file(ScriptMap[script.name]);
			//fx();

			ScriptMap[script.name](entityID);

		}
	}

}