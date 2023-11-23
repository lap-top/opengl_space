#ifndef ASTEROID_H
#define ASTEROID_H
#include "Entity.hpp"
class Asteroid : public Entity {
public:
	Asteroid(vec2d randCord);
	void draw() override;
	void update(float dt) override;
	void drawIrregular(float r, int n);
	int aOffsets[12];
};

#endif