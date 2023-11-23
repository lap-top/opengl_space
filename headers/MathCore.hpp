#ifndef MATHCORE_H
#define MATHCORE_H
#include "General.hpp"
#include <cmath>
namespace mc {
	// extern:
	extern vec2d rotateVec(vec2d v, float angle);
	extern float vecTo360Angle(vec2d v);
	extern vec2d norm(vec2d vector_a);
	extern vec2d nextPos(vec2d position, vec2d direction, float velocity, float deltatime);
	extern void drawCircle(float r, int n);
	extern vec2d parametricEquation(vec2d rs, float angle);
	extern bool intersect(vec2d entA, vec2d entB, float r1, float r2);
	extern int randNum(int min, int max);
	extern bool pointInCircle(vec2d pos, float r, vec2d p);
	extern bool areaCheck(vec2d pos, float r, float w, float h);

}

#endif