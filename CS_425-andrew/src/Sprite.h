#pragma once

#include <string>

using namespace std;

namespace engine{

	struct Sprite {
		string name;
		float x, y, z, scale, rotate;

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
		}


		Sprite(const string& n, float s, float r) {
			name = n;
			x = 0, y = 0, z = 0;
			scale = s;
			rotate = r;
		}

		Sprite(const string& n, float s, float r, float x_, float y_, float z_) {
			name = n;
			x = x_;
			y = y_;
			z = z_;
			scale = s;
			rotate = r;
		}

	};
}