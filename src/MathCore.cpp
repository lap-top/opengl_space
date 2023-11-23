#include "MathCore.hpp"
#include <iostream>
#include "glut.h"
#include <stdlib.h>  
#include <time.h>
namespace mc {
	vec2d rotateVec(vec2d v, float angle) {
		angle = HALF_C * angle;
		vec2d rv = { v.x * std::cos(angle) + v.y * std::sin(angle), -v.x * std::sin(angle) + v.y * std::cos(angle) };
		return rv;
	}
	float vecTo360Angle(vec2d v) {
		float radians = std::atan2(v.x, v.y);
		float degrees = radians * 180 / M_PI;
		if (radians < 0) { degrees += 360; }
		return degrees;
	}

	vec2d nextPos(vec2d pos, vec2d dir, float v, float dt) {
		return { pos.x += v * -dir.x * dt, pos.y + v * dir.y * dt };
	}

	vec2d norm(vec2d a) {
		float mag = sqrt((a.x * a.x) + (a.y * a.y));
		a = { a.x / mag, a.y / mag };
		return a;
	}

	vec2d parametricEquation(vec2d rs, float angle) {
		float t = std::tanf(angle++ / float(360) * M_PI);
		vec2d xy = { rs.x * (1 - std::pow(t, 2)) / (1 + std::pow(t, 2)), rs.y * 2 * t / (1 + std::pow(t, 2)) };
		return xy;
	}

	void drawCircle(float r, int n) {
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < n; i++) {
			float angle = 2.0f * M_PI * float(i) / float(n);
			glVertex2f((r * std::cosf(angle)),  (r * std::sinf(angle)));
		}
		glEnd();
	}
	bool intersect(vec2d entA, vec2d entB, float r1, float r2) {
		float distance = sqrt(((entA.x - entB.x) * (entA.x - entB.x)) + ((entA.y - entB.y) * (entA.y - entB.y)));
		return (distance < (r1 + r2));
	}	

	bool pointInCircle(vec2d pos, float r, vec2d p) {
		return sqrt((p.x - pos.x) * (p.x - pos.x) + (p.y - pos.y) * (p.y - pos.y)) < r;
	}

	int randNum(int min, int max) {
		return (min + (rand() % max));
	}


	bool  areaCheck(vec2d pos, float r, float w, float h) {
		if (pos.x + r < w && pos.x - r > 0 && pos.y + r < h && pos.y - r > 0) {
			return true;
		}
		return false;
	}
}