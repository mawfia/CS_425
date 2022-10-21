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

		lua.open_libraries(lib::base, lib::math, lib::table);
		lua.script("math.randomseed(0)");
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

		lua["GetSprite"] = [&](EntityID e) -> Sprite& { return engine->ECS.Get<Sprite>(e); };
		lua["Keys"] = &engine->input.keys;
		lua["PlaySound"] = [&](string name) -> void { engine->sound.PlaySound(name); };

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