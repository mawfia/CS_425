#pragma once

#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <vector>

#include "Engine.h"


using namespace std;

namespace engine {


	Engine::Engine(void) {

		//this->graphics = *(new GraphicsManager(this));
		//this->script = *(new ScriptManager(this));
		//this->physics = *(new PhysicsManager(this));
		this->graphics.engine = this;
		this->physics.engine = this;

		this->script.engine = this;

	}


	void Engine::Start(int GameParameters, const function<void(Engine& e)>& SetupCallback, const function<void(Engine& e)>& UpdateCallback) {
		
		const auto dt = chrono::duration<double>(1. / 60.);
		

		//cout << thread::hardware_concurrency() << endl;

		this->Startup(); // Engine::Startup() will work as well
		
		

		SetupCallback(*this);

		bool pressed_new = false;
		bool pressed_old = false;

		 while (true) {
			auto currentTime = chrono::steady_clock::now();

			pressed_old = pressed_new;

			this->input.Update();
			pressed_new = this->input.GetKeyPressed(this->graphics.window);

			
			if (!pressed_new && pressed_old) {
				//this->sound.PlaySound("blurp");

				/*for (auto [key, value] : this->input.keys) {
					cout << value << ' ';
				}

				cout << endl;*/
				this->input.keys.clear();
			}
			
			if (this->input.WindowShouldClose(this->graphics.window) == 1) {
				this->Shutdown();
				return;
			}

			UpdateCallback(*this);

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
		this->script.Startup();
		this->path.initializePlane();
	}

	void Engine::Shutdown(void) {
		this->graphics.Shutdown();
		this->sound.Shutdown();
	}
}