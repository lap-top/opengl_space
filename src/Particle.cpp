#include "Particle.hpp"
#include "glut.h"
#include <iostream>
Particle::Particle(vec2d pos) {
	this->pos = pos;
	this->decay = glutGet(GLUT_ELAPSED_TIME)+this->decay;
}

void  Particle::draw() {
	if (size > 0) {
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		glColor3f(0.5, 0.5, 0.5);
		glPointSize(size);
		glBegin(GL_POINTS);
		glVertex2f(0, 0);
		glEnd();
		glPopMatrix();
	}
}

void Particle::update(float dt) {
	if (glutGet(GLUT_ELAPSED_TIME) > decay) {
		decay = glutGet(GLUT_ELAPSED_TIME) + 5;
		this->size = size- 0.2f;

	}
}