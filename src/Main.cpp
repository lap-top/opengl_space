	#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "glut.h"
#include "Game.hpp"
#include "MathCore.hpp"
#include "General.hpp"

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/4, glutGet(GLUT_SCREEN_HEIGHT) / 4 );

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("S3716716 Asteroids :)");
	// CREATES A NEW GAME OBJECT
	Game game = new Game();

	glutMainLoop();

	return EXIT_SUCCESS;
}
