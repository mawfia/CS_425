#pragma once

#include <iostream>

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

	}

	bool ScriptManager::LoadScript(const string& name, const string& path) {


		//load_result fx = lua.load_file(path);

		ScriptMap[name] = lua.load_file(path);
		

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

	void ScriptManager::Update() {
		for (const auto& [entityID, script] : engine->ECS.GetAppropriateSparseSet<Script>()) {


			ScriptMap[script.name](entityID);

		}
	}

}