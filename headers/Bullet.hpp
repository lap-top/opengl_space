#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"
class Bullet : public Entity {
public:
	Bullet(vec2d pos, vec2d direction, float t);
	void draw() override;
	void update(float dt) override;
	float ttl = 0;
};

#endif