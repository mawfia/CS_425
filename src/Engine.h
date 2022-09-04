#pragma once

#include <string>
#include <functional>

#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"

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
			Engine();

			void Start(int GameParameters, void (*SetupCallback)(), const function<void(char)>& UpdateCallback);

		private:
			void Startup(void);
			void Shutdown(void);
		
	};

}