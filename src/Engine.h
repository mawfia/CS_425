#pragma once

#include <string>
#include <functional>

#include "GraphicsManager.h"
#include "InputManager.h"

using namespace std;

namespace engine {

	class GraphicsManager;
	class InputManager;

	class Engine {

		public:
			string name;
			GraphicsManager graphics;
			InputManager input;
			Engine();

			void Start(int GameParameters, void (*SetupCallback)(), const function<void(char)>& UpdateCallback);

		private:
			void Startup(void);
			void Shutdown(void);
		
	};

}