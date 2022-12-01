#pragma once

#include "Component.h"
//#include "Pvector.h"


using namespace std;

namespace engine {

	class Engine;

	class PhysicsManager {


	public:

		Engine* engine = nullptr;
		float maxSpeed = 0.5;
		float maxForce = 0.5;
		float desiredSeparation = .5;
		float neighbordist = 50;

		Pvector separation, alignment, cohesion;
		int separation_count = 0;
		int alignment_count = 0;
		int cohesion_count = 0;

		bool CheckCollisions(EntityID, EntityID);
		void Update();
		void Separation(EntityID, EntityID);
		void Alignment(EntityID, EntityID);
		void Cohesion(EntityID, EntityID);


	private:

		Pvector Seek(EntityID);
		float Angle(const Pvector&);

	};



}