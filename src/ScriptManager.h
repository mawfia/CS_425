#pragma once

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <unordered_map>


using namespace std;

namespace engine {

	class Engine;

	class ScriptManager {


		public:

			sol::state lua;
			Engine* engine = nullptr;
			unordered_map<string, sol::load_result> ScriptMap;
			//unordered_map<string, string> ScriptPathMap;

			ScriptManager(void);
			void Startup(void);
			bool LoadScript(const string& name, const string& path);
			void Update(void);
	};



}