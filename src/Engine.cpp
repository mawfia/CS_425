#pragma once

#include <thread>
#include <chrono>
#include <iostream>

#include "Engine.h"

using namespace std;

namespace engine {

	Engine::Engine(void) {

	}

	void Engine::Start(int GameParameters, void (*SetupCallback)(), void (*UpdateCallback)()) {
		
		const auto dt = chrono::duration<double>(1. / 60.);
		

		this->Startup(); // Engine::Startup() will work as well
		SetupCallback();
		
		int x = 0;
		
		 while( true ){
			 auto currentTime = chrono::steady_clock::now();
			//UpdateCallback();

			//this->graphics.Draw();

			 auto newTime = chrono::steady_clock::now();
			 auto loopTime = newTime - currentTime;
			 auto delta = dt - loopTime;
			
			 if (delta.count() > 0) this_thread::sleep_for(delta);
		 }
		
	}

	void Engine::Startup(void) {
		this->graphics.Startup();
	}

	void Engine::Shutdown(void) {
		this->graphics.Shutdown();
	}
}