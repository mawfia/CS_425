#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <functional>

#include "Engine.h"

using namespace std;

namespace engine {

	Engine::Engine(void) {

	}

	void Engine::Start(int GameParameters, void (*SetupCallback)(), const function<void(char)>& UpdateCallback) {
		
		const auto dt = chrono::duration<double>(1. / 60.);
		

		this->Startup(); // Engine::Startup() will work as well
		
		this->sound.LoadSound("blurp", "assets/sounds/blurp.wav");

		//SetupCallback();
		bool pressed_new = false;
		bool pressed_old = false;

		 while (true) {
			auto currentTime = chrono::steady_clock::now();

			pressed_old = pressed_new;

			this->input.Update();
			pressed_new = this->input.GetKeyPressed(this->graphics.window, UpdateCallback);
			
			if (!pressed_new && pressed_old) {
				this->sound.PlaySound("blurp");
			}
			
			if (this->input.WindowShouldClose(this->graphics.window) == 1) {
				this->Shutdown();
				return;
			}

			auto newTime = chrono::steady_clock::now();
			auto loopTime = newTime - currentTime;
			auto delta = dt - loopTime;
			
			if (delta.count() > 0) this_thread::sleep_for(delta);
		 }
		
	}

	void Engine::Startup(void) {
		this->graphics.Startup();
		this->input.Startup();
		this->sound.Startup();
	}

	void Engine::Shutdown(void) {
		this->graphics.Shutdown();
		this->sound.Shutdown();
	}
}