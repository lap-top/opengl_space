#ifndef INPUT_H
#define INPUT_H
class Game;
//#include "Game.hpp"
class Input {
public:
		// FLAGS
	bool forwardFlag = false;
	bool backwardsFlag = false;
	bool rightFlag = false;
	bool leftFlag = false;
	bool shootFlag = false;
	Game* game;
	Input(Game* gameInstance);
	Input();
	int keyPressed = 0;
	void onKeyPress(unsigned char key, int x, int y);
	void onSpecialKeyPress(int key, int x, int y);
	void onKeyRelease(unsigned char key, int x, int y);
	void onSpecialKeyRelease(int key, int x, int y);
	void onMouseButton(int btn, int state, int x, int y);
	void onMouseMove(int x, int y);
	void onMouseDrag(int x, int y);

	// WRAPPER
	void static onKeyPressWrapper(unsigned char key, int x, int y);
	void static onSpecialKeyPressWrapper(int key, int x, int y);
	void static onKeyReleaseWrapper(unsigned char key, int x, int y);
	void static onSpecialKeyReleaseWrapper(int key, int x, int y);
	void static onMouseButtonWrapper(int btn, int state, int x, int y);
	void static onMouseMoveWrapper(int x, int y);
	void static onMouseDragWrapper(int x, int y);


};


#endif