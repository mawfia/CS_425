#pragma once

#include <string>
#include <functional>

#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "ScriptManager.h"
#include "PhysicsManager.h"
#include "EntityComponentSystem.h"


using namespace std;

namespace engine {

	class GraphicsManager;
	class InputManager;
	class SoundManager;
	class ScriptManager;
	class PhysicsManager;

	class Engine {

		public:
			GraphicsManager graphics;
			InputManager input;
			SoundManager sound;
			ScriptManager script;
			PhysicsManager physics;
			EntityComponentSystem ECS;

			Engine();
			void Start(int GameParameters, const function<void(Engine&)>&, const function<void(Engine&)>& );

		private:
			void Startup(void);
			void Shutdown(void);
		
	};

}