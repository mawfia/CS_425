#pragma once

#include <string>
#include <functional>

#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "EntityComponentSystem.h"


using namespace std;

namespace engine {

	class GraphicsManager;
	class InputManager;
	class SoundManager;

	class Engine {

		public:
			GraphicsManager graphics;
			InputManager input;
			SoundManager sound;
			EntityComponentSystem ECS;
			Engine();
			void Start(int GameParameters, const function<void(Engine&)>&, const function<void(Engine&)>& );

		private:
			void Startup(void);
			void Shutdown(void);
		
	};

}