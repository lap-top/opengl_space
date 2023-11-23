#ifndef ENTITY_H
#define ENTITY_H
#include "General.hpp"
#include "math.h"
#include <string>
class Entity {
private:

public:
	Entity();
	Entity(vec2d pos);
	~Entity();
	float v = 5;
	float r = 5;
	colour col= { 1,  1, 1 };
	vec2d pos = { 0, 0 };
	vec2d dir = { 0, 1 };
	virtual void draw(); 
	std::string entityClass;
	virtual void update(float dt);
	int hp = 15;
	bool inArena = true;
};

#endif