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
		//SetupCallback();
		
		 while (true) {
			 auto currentTime = chrono::steady_clock::now();

			this->input.Update();
			this->input.GetKeyPressed(this->graphics.window, UpdateCallback);
			if (this->input.WindowShouldClose(this->graphics.window) == 1) return;

			auto newTime = chrono::steady_clock::now();
			auto loopTime = newTime - currentTime;
			auto delta = dt - loopTime;
			
			if (delta.count() > 0) this_thread::sleep_for(delta);
		 }
		
	}

	void Engine::Startup(void) {
		this->graphics.Startup();
		this->input.Startup();
	}

	void Engine::Shutdown(void) {
		this->graphics.Shutdown();
	}
}