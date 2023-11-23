#include "game.hpp"
#include "Output.hpp"
#include <stdio.h>
#include <iostream>
#include "glut.h"
#include "Entity.hpp"
#include "MathCore.hpp"
#include<string>  
Output* outputInstance;
Output::Output(Game* gameInstance) {
	scrW = 0;
	scrH = 0;
	game = gameInstance;
	outputInstance = this;
	float deltaa;
	trackTime = 0;
}


int getStringLength(std::string str) {
	int len = 0;
	for (int i = 0; i < str.length(); i++) {
		len += glutStrokeWidth(GLUT_STROKE_ROMAN, str[i]);
	}
	return len;
}

void drawString(std::string message, int xpos, int ypos, bool middle=false) {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(xpos, ypos, 0);
	glScalef(0.05, 0.05, 1);
	glColor3f(1, 1, 1);

	int messageLen = getStringLength(message);
	if (middle) {
		glTranslatef(-messageLen + messageLen / 2, 0, 0);
	}
	else {
		glTranslatef(-messageLen, 0, 0);
	}
	for (int i = 0; i < message.length(); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message[i]);
		messageLen -= glutStrokeWidth(GLUT_STROKE_ROMAN, message[i]);
	}
	glPopMatrix();
}
void Output::drawHud() {
	// SET PROJECTION TO THE SCREEN INSTEAD OF WORLD
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, GLUT_SCREEN_WIDTH, 0, GLUT_SCREEN_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	

	glColor3f(1, 1, 1);
	glLineWidth(1);
	// DRAW SCORE
	drawString(std::to_string(game->player->score), 10, GLUT_SCREEN_HEIGHT - 10, false);

	// DRAWING TIMER
	int secs = glutGet(GLUT_ELAPSED_TIME) - trackTime;
	secs = (secs / 1000) % 60;
	int mins = (secs % 3600) / 60;
	std::string time = std::to_string(mins) + ":" + std::to_string(secs);
	drawString(time, GLUT_SCREEN_WIDTH - 10, 10, false);

	// DEATH SCREEN
	if (game->isDead) {
		drawString("YOU GOT OWNED! LOL!", GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2 + 20, true);
		drawString("PRESS ANY KEY TO CONTINUE", GLUT_SCREEN_WIDTH / 2, GLUT_SCREEN_HEIGHT / 2 - 10, true);
	}
	// POP THE PROJECTION WE JUST PUSHED ON THE STACK
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}
void Output::onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* Put drawing code here */
	
	//render_frame(entities);
	renderFrame();
	drawHud();
	
	glFlush();
	/* Always check for errors! */
	int err;
	while ((err = glGetError()) != GL_NO_ERROR)
		printf("display: %s\n", gluErrorString(err));

	glutSwapBuffers();
}

void Output::onReshape(int width, int height) {
	float worldx = ARENA_W, worldy = ARENA_H;
	float aspect = (float) width / height;
	float ratio = (worldx) / (worldy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float delta;
	if (ratio < aspect)
	{
		delta = (worldy * aspect - worldx) / 2;
		
		glOrtho(-delta, worldx+ delta, 0, worldy, -50.0, 5.0);
	}
	else
	{
		delta = (worldx / aspect - worldy) / 2;
		glOrtho(0, worldx,  -delta, worldy + delta, -50.0, 5.0);
	}
	glViewport(0,0, width, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void Output::renderFrame() {

	glLineWidth(1);
	for (Entity* ent : game->ents) {
		ent->draw();
	}
	arenaBorder = { 0, 0.7, 0.1 };
	if (!mc::areaCheck(game->player->pos, game->player->r + 5, ARENA_W, ARENA_H)) {
		arenaBorder = { 0.5, 0.0, 0 };
	}


	glPushMatrix();
	glLineWidth(2);
	glColor3f(arenaBorder.r, arenaBorder.g, arenaBorder.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0, ARENA_H);
	glVertex2f(0, 0);
	glVertex2f(ARENA_W, 0);
	glVertex2f(ARENA_W, ARENA_H);
	glEnd();
	glPopMatrix();
}

// GLUT WRAPPERS
void Output::onDisplayWrapper() {
	outputInstance->onDisplay();
}
void Output::onReshapeWrapper(int w, int h) {
	outputInstance->onReshape(w, h);
}