#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

#include "GLFW/glfw3.h"

using namespace std;

namespace engine {

	class InputManager {

		public:
			InputManager();
			void Startup(void);
			void Shutdown(void);
			int WindowShouldClose(GLFWwindow* window);
			void Update(void);
			unordered_map<int, string> keys;
			bool GetKeyPressed(GLFWwindow* window);
			unordered_map<int, string> keyMap{ {262,"right"}, {263,"left"},{264,"down"},{265,"up"},{32,"space"} };
			
			/*unordered_map<int, char> keyMap{
				{65,'a'},
				{66,'b'},
				{67,'c'},
				{68,'d'},
				{69,'e'},
				{70,'f'},
				{71,'g'},
				{72,'h'},
				{73,'i'},
				{74,'j'},
				{75,'k'},
				{76,'l'},
				{77,'m'},
				{78,'n'},
				{79,'o'},
				{80,'p'},
				{81,'q'},
				{82,'r'},
				{83,'s'},
				{84,'t'},
				{85,'u'},
				{86,'v'},
				{87,'w'},
				{88,'x'},
				{89,'y'},
				{90,'z'}
			};*/
	};
}