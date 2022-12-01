#pragma once

#include <iostream>
#include <algorithm>

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define STB_IMAGE_IMPLEMENTATION


#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsManager.h"
#include <assert.h>
#include "Engine.h"


using namespace std;
using namespace glm;

namespace {
	struct Uniforms {
		mat4 projection;
		mat4 transform;
	};
}

namespace engine {


	GraphicsManager::GraphicsManager() {

	}

	void GraphicsManager::Startup() {

		int  window_width = 1000, window_height = 1000;
		const char window_name[] = "Galaga Plus";
		bool window_fullscreen = false;		

		glfwInit();
		
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		this->window = glfwCreateWindow(window_width, window_height, window_name, window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, window_width, window_height);
		if (!window)
		{
			std::cerr << "Failed to create a window." << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		sg_setup(sg_desc{});

		// A vertex buffer containing a textured square.
		const float vertices[] = {
			// positions      // texcoords
			-1.0f,  -1.0f,    0.0f,  1.0f,
			-1.0f,  1.0f,    0.0f,  0.0f,
			1.0f,  -1.0f,    1.0f,  1.0f,
			1.0f,  1.0f,    1.0f,  0.0f,
		};

		sg_buffer_desc buffer_desc{};
		buffer_desc.data = SG_RANGE(vertices);

		

		sg_buffer vertex_buffer = sg_make_buffer(buffer_desc);
		//this->vertex_buffer = sg_make_buffer(buffer_desc);
		sg_pipeline_desc pipeline_desc{};

		pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;

		pipeline_desc.colors[0].blend.enabled = true;
		pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
		pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;

		pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
		pipeline_desc.depth.write_enabled = true;

		pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
		pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

		// Setup Vertex Shader

		sg_shader_desc shader_desc{};

		shader_desc.vs.source = R"(
			#version 330
			uniform mat4 projection;
			uniform mat4 transform;
			layout(location=0) in vec2 position;
			layout(location=1) in vec2 texcoords0;
			out vec2 texcoords;
			void main() {
				gl_Position = projection*transform*vec4( position.x, position.y, 0.0, 1.0 );
				texcoords = texcoords0;
			})";

		shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
		// The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
		shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
		shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
		shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
		shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

		// Setup Fragment Shader

		shader_desc.fs.source = R"(
			#version 330
			uniform sampler2D tex;
			in vec2 texcoords;
			out vec4 frag_color;
			void main() {
				frag_color = texture( tex, texcoords );
				// If we're not drawing back to front, discard very transparent pixels so we
				// don't write to the depth buffer and prevent farther sprites from drawing.
				if( frag_color.a < 0.1 ) discard;
			}
		)";
		shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
		shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

		pipeline_desc.shader = sg_make_shader(shader_desc);
		//sg_pipeline pipeline = sg_make_pipeline(pipeline_desc);
		this->pipeline = sg_make_pipeline(pipeline_desc);

		//sg_pass_action pass_action{};
		this->pass_action.colors[0].action = SG_ACTION_CLEAR;
		this->pass_action.colors[0].value = { 0.0f, 0.0f, 0.0f, 1.0f };

		//sg_bindings bindings{};
		this->bindings.vertex_buffers[0] = vertex_buffer;
	}

	void GraphicsManager::Shutdown(void) {
		sg_shutdown();
		cout << "Graphics Manager shutting down." << '\n';
	}

	bool GraphicsManager::loadImages(const string& name, const vector<string>& paths) {

		for (const auto& path : paths) {
			int width, height, channels;
			unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

			if (!data) return false;
			else cout << path + " loaded successfully" << endl;

			sg_image_desc image_desc{};

			image_desc.width = width;
			image_desc.height = height;
			image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
			image_desc.min_filter = SG_FILTER_LINEAR;
			image_desc.mag_filter = SG_FILTER_LINEAR;
			image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
			image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
			image_desc.data.subimage[0][0].ptr = data;
			image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);

			this->image_desc_Map2[name].push_back(image_desc);
			this->image_Map2[name].push_back(sg_make_image(this->image_desc_Map2[name].back()));

			stbi_image_free(data);
		}

		return true;
	}

	bool GraphicsManager::loadImage(const string& name, const string& path) {

		int width, height, channels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		

		if (!data) return false;
		else cout << "image loaded successfully" << endl;
		//sg_image_desc image_desc{};

		this->image_desc_Map[name].width = width;
		this->image_desc_Map[name].height = height;
		this->image_desc_Map[name].pixel_format = SG_PIXELFORMAT_RGBA8;
		this->image_desc_Map[name].min_filter = SG_FILTER_LINEAR;
		this->image_desc_Map[name].mag_filter = SG_FILTER_LINEAR;
		this->image_desc_Map[name].wrap_u = SG_WRAP_CLAMP_TO_EDGE;
		this->image_desc_Map[name].wrap_v = SG_WRAP_CLAMP_TO_EDGE;
		this->image_desc_Map[name].data.subimage[0][0].ptr = data;
		this->image_desc_Map[name].data.subimage[0][0].size = (size_t)(width * height * 4);

		this->image_Map[name] = sg_make_image(this->image_desc_Map[name]);

		//sg_make_image(this->imageMap[name]);

		//this->bindings.fs_images[0] = image;

		//cout << this->bindings.fs_images[0].id << endl;
		//sg_apply_bindings(this->bindings);

		stbi_image_free(data);

		return true;
	}

	void GraphicsManager::Draw() {
	
		//unordered_map<EntityID, Sprite> sprites = ;
		//sort(sprites.begin(), sprites.end(), [](const auto& lhs, const auto& rhs) { return lhs.second.z < rhs.second.z; });
		//sort(sprites.begin(), sprites.end(), [](const auto& lhs, const auto& rhs) { return; });


		int height, image_height;
		int width, image_width;
		float scale, rotate, x, y, z;
		Uniforms uniforms;

		glfwGetFramebufferSize(this->window, &width, &height);

		sg_begin_default_pass(this->pass_action, width, height);

		sg_apply_pipeline(this->pipeline);


		//this->bindings.fs_images[0] = this->imageMap[sprites[0].name];
		//float g = this->pass_action.colors[0].value.g + 0.01f;
		//this->pass_action.colors[0].value.g = (g > 1.0f) ? 0.0f : g;
		
		
		// Start with an identity matrix.
		uniforms.projection = mat4{ 1 };
		// Scale x and y by 1/100.
		uniforms.projection[0][0] = uniforms.projection[1][1] = 1.0f;
		// Scale the long edge by an additional 1/(long/short) = short/long.
		if ( width < height) {
			uniforms.projection[1][1] *= width;
			uniforms.projection[1][1] /= height;
		}
		else {
			uniforms.projection[0][0] *= height;
			uniforms.projection[0][0] /= width;
		}

		

		for (const auto& [entityID, sprite] : engine->ECS.GetAppropriateSparseSet<Sprite>()) {


			
			//sg_image image = sg_make_image(this->imageMap[sprite.name]);
			//sg_image image = this->bindings.fs_images[0];

			
			//if (this->bindings.fs_images[0].id != this->image_Map[sprite.name].id)
			//{
			this->bindings.fs_images[0] = this->image_Map2[sprite.name].at(sprite.index);
			sg_apply_bindings(this->bindings);
			image_width = this->image_desc_Map2[sprite.name].at(sprite.index).width;
			image_height = this->image_desc_Map2[sprite.name].at(sprite.index).height;
			scale = sprite.scale;
			rotate = sprite.rotate;
			x = sprite.x;
			y = sprite.y;
			z = sprite.z;
			//}
			

			uniforms.transform = glm::translate(mat4{ 1.0f }, vec3(x, y, z)) * glm::scale(mat4{ 1.0f }, vec3(scale, scale, scale)) * glm::rotate(mat4{ 1.0f }, glm::radians(rotate), vec3(0.0, 0.0, 1.0));


			if (width < height) {
				uniforms.transform = uniforms.transform * glm::scale(mat4{ 1 }, vec3(double(image_width) / image_height, 1.0, 1.0));
			}
			else {
				uniforms.transform = uniforms.transform * glm::scale(mat4{ 1 }, vec3(1.0, double(image_height) / image_width, 1.0));
			}

			sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));
		
			sg_draw(0, 4, 1);
		
		}

		sg_end_pass();
		sg_commit();
		glfwSwapBuffers(this->window);

	}
}