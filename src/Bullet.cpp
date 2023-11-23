#include "glut.h"
#include "General.hpp"
#include <iostream>
#include "Bullet.hpp"
#include "MathCore.hpp"
Bullet::Bullet(vec2d pos, vec2d direction, float t) {
		v = 120;
		ttl = t + 4500;
		dir = direction;
		col = { 1,0,0 };
		this->pos = pos;
	}
void Bullet::update(float dt) {
	pos = mc::nextPos(pos, dir, v, dt);
}

void Bullet::draw() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glColor3f( S_B_R, S_B_G, S_B_B);
	glBegin(GL_POINTS);
		glVertex2f(0, 0);
	glEnd();
	glPointSize(3);
	glPopMatrix();

}