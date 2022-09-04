#pragma once

#include <iostream>
#include <vector>

#include "InputManager.h"
#include "GLFW/glfw3.h"

using namespace std;

namespace engine {

	InputManager::InputManager(void) {

	}

	void InputManager::Startup(void) {

		glfwInit();
	
	}

	void InputManager::Shutdown(void) {
		cout << "Input Manager shutting down." << '\n';
	}

	void InputManager::Update(void) {
		glfwPollEvents();
	}

	bool InputManager::GetKeyPressed(GLFWwindow* window, const function<void(char)>& UpdateCallback) {
		
		bool pressed = false;

		for (auto key : this->keyMap)
			if (glfwGetKey(window, key.first) == 1) {
				UpdateCallback(key.second);
				pressed = true;
			}
		if (pressed) cout << '\n';
	
		return pressed;
	}

	int InputManager::WindowShouldClose(GLFWwindow* window) {
		return glfwWindowShouldClose(window);
	}

}