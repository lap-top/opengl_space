#ifndef PARTICLE_H
#define PARTICLE_H
#include "General.hpp"
class Particle {
public:
	Particle(vec2d pos);
	void draw() ;
	void update(float dt);
	float decay = 15;
	float size = 0.8;
	colour col;
	vec2d pos;
	vec2d dir;
};
#endif