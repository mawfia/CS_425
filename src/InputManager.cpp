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

	bool InputManager::GetKeyPressed(GLFWwindow* window) {
		
		bool pressed = false;

		for (auto [key, value] : this->keyMap)
			if (glfwGetKey(window, key) == 1) {
				//UpdateCallback(key.second);
				cout << value << ' ';
				
				pressed = true;
			}
		if (pressed) cout << '\n';
	
		return pressed;
	}

	int InputManager::WindowShouldClose(GLFWwindow* window) {
		return glfwWindowShouldClose(window);
	}

}