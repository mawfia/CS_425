#pragma once

#include <string>

using namespace std;

namespace engine {

	class GraphicsManager {

		public:
			GraphicsManager();
			void Startup(void);
			void Shutdown(void);
			void Draw(void);
		};

}