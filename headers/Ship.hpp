#include "Entity.hpp"
#include "Bullet.hpp"
#include "Particle.hpp"
#include <deque>
class Ship : public Entity {
public:
	Ship();
	void draw() override;
	void shoot(float dt);	
	int score = 0;
	std::deque<Bullet> bullets;
	std::deque<Particle*> particles;
	float nextBullet;
	void fart();
};