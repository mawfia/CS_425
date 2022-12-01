#pragma once
#include <unordered_map>

#include "sokol_gfx.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

using namespace std;



namespace engine {

	class Engine;
	//class EntityComponentSystem;


	class GraphicsManager {

		public:

			Engine* engine = nullptr;

			GraphicsManager();
			void Startup();
			void Shutdown(void);
			void Draw(void);
			bool loadImage(const string& name, const string& path);

			GLFWwindow* window;
			//sg_pipeline_desc pipeline_desc{};
			//sg_buffer vertex_buffer;
			sg_pipeline pipeline;
			sg_bindings bindings{};
			sg_pass_action pass_action{};

			unordered_map<string, sg_image_desc> image_desc_Map;
			unordered_map<string, sg_image> image_Map;
			//sg_image_desc image_desc{};
			
		};

}