#pragma once

#include "SoundManager.h"

using namespace std;

namespace engine {

	SoundManager::SoundManager(void) {

	}

	void SoundManager::Startup(void) {
		this->soloud.init();

	}

	void SoundManager::Shutdown(void) {
		this->soloud.deinit();
	}

	void SoundManager::LoadSound(const string& name, const string& path) {

		this->soundMap[name].load(path.c_str());
	}

	void SoundManager::PlaySound(const string& name) {
		this->soloud.play(this->soundMap[name]);
	}
}