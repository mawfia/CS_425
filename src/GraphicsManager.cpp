#pragma once

#include <iostream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GraphicsManager.h"

using namespace std;

namespace engine {

	GraphicsManager::GraphicsManager(void) {

	}

	void GraphicsManager::Startup(void) {

		int  window_width = 1000, window_height = 1000;
		const char window_name[] = "test";
		bool window_fullscreen = false;

		glfwInit();
		// We'll use sokol_gfx's OpenGL backend
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name, window_fullscreen ? glfwGetPrimaryMonitor() : 0, 0);
		glfwSetWindowAspectRatio(window, window_width, window_height);
		if (!window)
		{
			std::cerr << "Failed to create a window." << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
	}

	void GraphicsManager::Shutdown(void) {
		cout << "Graphics Manager shutting down." << '\n';
	}

	void GraphicsManager::Draw(void) {
		cout << "Drawing" << '\n';
	}

}