#pragma once

#include <thread>
#include <chrono>

#include "Engine.h"

using namespace std;

namespace engine {

	Engine::Engine(void) {

	}

	void Engine::Start(int GameParameters, void (*SetupCallback)(), void (*UpdateCallback)()) {
		
		const auto one_tenth_of_a_second = chrono::duration<double>(1. / 10.);

		this->Startup(); // Engine::Startup() will work as well
		SetupCallback();

		/*
		 while( true ){

			UpdateCallback();

			this->graphics.Draw();
			this_thread::sleep_for(one_tenth_of_a_second);
		 }
		*/
	}

	void Engine::Startup(void) {
		this->graphics.Startup();
	}

	void Engine::Shutdown(void) {
		this->graphics.Shutdown();
	}
}