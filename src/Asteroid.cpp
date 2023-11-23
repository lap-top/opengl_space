#include "Entity.hpp"
#include "glut.h"
#include <iostream>
#include "Mathcore.hpp"
#include "Asteroid.hpp"


Asteroid::Asteroid(vec2d plyPos) {
	vec2d screen = { ARENA_W, ARENA_H };
	entityClass = "asteroid";
	v = mc::randNum(A_VELOCITY_MIN, A_VELOCITY_MAX);
	r = mc::randNum(A_RADIUS_MIN, A_RADIUS_MAX);
	hp = r*0.8;
	inArena = false;
	col = { 0.4,0.4,0.4 };
	vec2d p = mc::parametricEquation(screen, mc::randNum(0, 360));
	pos = { screen.x/2 + p.x, screen.y/2 + p.y};
	vec2d newDir = {-(plyPos.x-pos.x), (plyPos.y - pos.y)};
	newDir = mc::norm(newDir);

	dir = newDir;
	for (int i = 0; i < 12; i++) {
		aOffsets[i] = r+mc::randNum(-3, 3);
	}
}

void Asteroid::drawIrregular(float r, int n) {
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++) {

		float angle = (2.0f * M_PI * float(i) ) / float(n);
		glVertex2f((aOffsets[i] * std::cosf(angle)), (aOffsets[i] * std::sinf(angle)));
	}
	glEnd();
}
void Asteroid::update(float dt) {
	pos = mc::nextPos(pos, dir, v, dt);
}

void Asteroid::draw() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(mc::vecTo360Angle(dir), 0, 0, 1);

	glColor3f(col.r, col.g, col.b);
	drawIrregular(r, 12);
	glColor3f(1, 1, 0);
	if (DEBUG == true) {
		mc::drawCircle(r, 12);
	}
	glPopMatrix();

}


