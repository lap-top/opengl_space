#ifndef GAME_H
#define GAME_H 
#include "Entity.hpp"
#include "Ship.hpp"
#include <vector>
#include "General.hpp"
class Output;
class Input;
// Main Game Class
class Game {
public:
	Game();
	Game(const Game* obj);
	// Wave Settings
	float nextWave = WAVE_INIT; 
	float nextWaveT;
	int nAsteroids = 1;


	/// GLUT CALLBACKS
	void onIdle();
	void updateGameState(float dt);
	void bindCallbacks();
	// Other
	std::vector<Entity*> ents;
	Ship* player;
	
	void static onIdleWrapper();
	void resetGameState();
	void collisions();
	float nextSpawn;
	float dt;
	bool arenaCheck(vec2d pos, float r, int rOffset);
	bool isDead = true;
private:
	Output* output;
	Input* input;
};

#define NUM_OBJECTS 50
#endif

