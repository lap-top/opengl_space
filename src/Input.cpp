#include "glut.h"
#include "Input.hpp"
#include "Game.hpp"
#include "General.hpp"
#include <iostream>
Input* inputInstance;
Input::Input() {
	game = nullptr;                                                                            
}
Input::Input(Game* gameInstance) {
	game = gameInstance;
	inputInstance = this;
}

void Input::onKeyPress(unsigned char key, int x, int y) {
	if (game->isDead) {
		game->isDead = false;
	}
	switch (key) {
	case ' ':
		shootFlag = true;
		break;
	case 'a':	
	case 'A':
		leftFlag = true;
		break;
	case 'd':
	case 'D':
		this->rightFlag = true;
		break;
	case 'w':
	case 'W':
		forwardFlag = true;
		break;
	case 's':
	case 'S':
		backwardsFlag = true;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void Input::onSpecialKeyPress(int key, int x, int y) {

}
void Input::onKeyRelease(unsigned char key, int x, int y) {
	switch (key)
	{
	case ' ':
		shootFlag = false;
		break;
	case 'd':
	case 'D':
		rightFlag = false;
		break;
	case 'a':
	case 'A':
		leftFlag = false;
		break;
	case 'w':
	case 'W':
		forwardFlag = false;
		break;
	case 's':
	case 'S':
		backwardsFlag = false;
		break;
	default:
		break;
	}
}
void Input::onSpecialKeyRelease(int key, int x, int y) {

}
void Input::onMouseButton(int btn, int state, int x, int y) {

}
void Input::onMouseMove(int x, int y) {

}
void Input::onMouseDrag(int x, int y) {

}

// WRAPPING CLASSES
void Input::onKeyPressWrapper(unsigned char key, int x, int y) {
	inputInstance->onKeyPress(key, x, y);
}
void Input::onSpecialKeyPressWrapper(int key, int x, int y) {
	inputInstance->onSpecialKeyPress(key, x, y);
}
void Input::onKeyReleaseWrapper(unsigned char key, int x, int y) {
	inputInstance->onKeyRelease(key, x, y);
}
void Input::onSpecialKeyReleaseWrapper(int key, int x, int y) {
	inputInstance->onSpecialKeyRelease(key, x, y);
}
void Input::onMouseButtonWrapper(int btn, int state, int x, int y) {
	inputInstance->onMouseButton(btn, state, x, y);
}
void Input::onMouseMoveWrapper(int x, int y) {
	inputInstance->onMouseMove(x, y);
}
void Input::onMouseDragWrapper(int x, int y) {
	inputInstance->onMouseDrag(x, y);
}
