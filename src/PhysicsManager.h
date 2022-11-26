#pragma once

#include "Component.h"

using namespace std;

namespace engine {

	class Engine;

	class PhysicsManager {


	public:

		Engine* engine = nullptr;

		void CheckBoundaries();
		void Update();

		float CheckDistance(Sprite&, Sprite&);

	};



}