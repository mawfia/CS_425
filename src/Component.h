#pragma once

#include <string>
#include <unordered_map>

using namespace std;

namespace engine {

	typedef long EntityID;
	typedef int ComponentIndex;

	struct Sprite {
		string name;
		float x, y, z, scale, rotate;

		Sprite() {
		}

		Sprite(const string& n) {
			name = n;
			x = 0, y = 0, z = 0;
			scale = 1.0;
			rotate = 0.0;
		}

		Sprite(const string& n, float s) {
			name = n;
			x = 0, y = 0, z = 0;
			scale = s;
			rotate = 0.0;
		}


		Sprite(const string& n, float s, float r) {
			name = n;
			scale = s;
			rotate = r;
			x = 0, y = 0, z = 0;
		}

		Sprite(const string& n, float s, float r, float x_, float y_, float z_) {
			name = n;
			scale = s;
			rotate = r;
			x = x_;
			y = y_;
			z = z_;
		}

	};

	struct Script {
		string name;

		Script(){}

		Script(const string& n) {
			name = n;
		}
	};

	struct Position {
		//double x, y;
		string name;

		Position(){}

		Position(const string& n) {
			name = n;
		}

	};

	struct Velocity {
		double x, y;

		Velocity(double x_, double y_) {
			x = x_;
			y = y_;
		}
	};

	struct Gravity {
		double meters_per_second;
	};

	struct Health {
		double percent;

		Health() {}

		Health(double p) {
			percent = p;
		}
	};

	class SparseSetHolder {
		public:
			// A virtual destructor, since we store pointers to this superclass yet have subclasses with destructors that need to run.
			virtual ~SparseSetHolder() = default;
			virtual bool Has(EntityID) const = 0;
			virtual void Drop(EntityID) = 0;
	};

	// Subclasses are templated on the component type they hold.
	template< typename T > 
	class SparseSet : public SparseSetHolder {
		public:
			unordered_map< EntityID, T > data;
			bool Has(EntityID e) const override { return data.count(e) > 0; };
			void Drop(EntityID e) override { data.erase(e); };
	};
}