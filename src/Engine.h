#pragma once

#include <string>

#include "GraphicsManager.h"

using namespace std;

namespace engine {

	class GraphicsManager;

	class Engine {

		public:
			string name;
			GraphicsManager graphics;
			Engine();

			void Start(int GameParameters, void (*SetupCallback)(), void (*UpdateCallback)());

		private:
			void Startup(void);
			void Shutdown(void);
		
	};

}