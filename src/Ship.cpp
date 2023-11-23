#include "Ship.hpp" 
#include <iostream>
#include "glut.h"
#include "General.hpp"
#include "MathCore.hpp"
#include "Particle.hpp"
#include<string>  

Ship::Ship() {
	entityClass = "ship";
	v = S_VELOCITY;
	col = { S_R,  S_G, S_B };
	pos = { (float)r+1, (float)r+1 };
	dir = { -1, 1 };
	r = 5.0f;
	this->nextBullet = glutGet(GLUT_ELAPSED_TIME)+500;
}
bool togggtest = false;




void Ship::draw() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(mc::vecTo360Angle(dir), 0, 0, 1);

	glColor3f(col.r, col.g, col.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, 4);
	glVertex2f(4, -4);
	glVertex2f(0, -1);
	glVertex2f(-4, -4);
	glVertex2f(0, 4);
	glVertex2f(0, -1);
	glEnd();
	glColor3f(0.7, 0.0, 0.2);

	if (DEBUG == true) {
		glColor3f(1, 1, 0);
		mc::drawCircle(r, 12);
		glBegin(GL_POINTS);
		glVertex2f(0, 0);
		glEnd();
		glPointSize(3);
	}
	glPopMatrix();



	for (std::deque<Particle*>::iterator particle = particles.begin(); particle != particles.end(); ++particle) {
		(*particle)->draw();
	}
	for (std::deque<Bullet>::iterator bullet = bullets.begin(); bullet != bullets.end(); ++bullet) {
		bullet->draw();
	}
}
void Ship::fart() {
	Particle* particle = new Particle(pos);
	particles.push_back(particle);
}


void Ship::shoot(float dt) {
	Bullet bullet(this->pos, this->dir, dt);
	bullets.push_back(bullet);
}
