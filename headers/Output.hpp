#ifndef OUTPUT_H
#define OUTPUT_H
class Game;

// GLUT OUTPUT WRAPPER
class Output {
private:
	Game* game;
public:
	int scrW, scrH;
	Output(Game* gameInstance);
	Output();
	colour arenaBorder = { 0, 0.7, 0.1 };
	void onDisplay();
	void onReshape(int w, int h);
	void renderFrame();
	void drawHud();
	int trackTime;
	float deltaV;
	
	// WRAPPER
	void static onDisplayWrapper();
	void static onReshapeWrapper(int w, int h);
};
#endif