#include "Game.hpp"
#include "Glut.h"
#include "Input.hpp"
#include "Output.hpp"
#include <iostream>
#include <math.h>
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "MathCore.hpp"

Game* gameInstance;
Game::Game() {
	srand((unsigned)time(0));
	input = new Input(this);
	output = new Output(this);
	gameInstance = this;
	bindCallbacks();

	player = new Ship();
	ents.push_back(player);
	nextSpawn = 0;
	nextWaveT = glutGet(GLUT_ELAPSED_TIME) + (nextWave * 1000);
}

// Collision Code
Game::Game(const Game* obj) {
	this->output = obj->output;
	this->input = obj->input;
	this->ents = obj->ents;
}

bool  Game::arenaCheck(vec2d pos, float r, int rOffset) {
	if (pos.x+r < ARENA_W && pos.x-r > 0 && pos.y+r < ARENA_H && pos.y-r > 0 ) {
		return true;
	}
	return false;
}
void Game::collisions() {
	// Entity Collision
	for (Entity* ent : ents) {
		for (Entity* entB : ents) {
			if (ent != entB) {
				if (mc::intersect(ent->pos, entB->pos, ent->r, entB->r)) {
			
					if (ent->entityClass == "ship" && entB->entityClass == "asteroid") {
						resetGameState();
						return;
					}
					if (ent->entityClass == "asteroid" && entB->entityClass == "asteroid") {
						ent->dir = mc::rotateVec(ent->dir, -180);
						entB->dir = mc::rotateVec(ent->dir, -180);
					
					}
				}
			}
		}
		if (!arenaCheck(ent->pos, ent->r, 0) && ent->inArena) {
			ent->dir = mc::rotateVec(ent->dir, -90);

		}
		else if (arenaCheck(ent->pos, ent->r, 0) && !ent->inArena) {
			ent->inArena = true;
		}
	}
	

	// Bullet Collision

	for (std::deque<Bullet>::iterator bullet = player->bullets.begin(); bullet != player->bullets.end(); ++bullet) {
		bullet->update(dt);
		int i = 0;
		if (!arenaCheck(bullet->pos, 1, 0) ) {
			bullet->pos.x = 1000;
		}
		if (ents.empty() == false) {
			for (int i = ents.size() - 1; i >= 0; i--) {
				if (ents.at(i)->entityClass == "asteroid") {
					if (mc::pointInCircle(ents.at(i)->pos, ents.at(i)->r, bullet->pos)) {
						ents.at(i)->hp-=2;
						bullet->pos.x = 10000;
						if (ents.at(i)->hp < 0) {
							this->player->score++;
							Entity* tEnt = ents.at(i);
							ents.erase(ents.begin() + i);
							delete tEnt;
						}
					}
				}
			}
		}
}

	while (player->bullets.size() != 0 && glutGet(GLUT_ELAPSED_TIME) > player->bullets.front().ttl) {
		player->bullets.pop_front();
	}
}

void Game::resetGameState() {
	nextSpawn = 0;
	ents.clear();
	player = new Ship();
	ents.push_back(player);
	nextSpawn = 0;
	nextWave = 5;
	nAsteroids = 0;
	nextWaveT = glutGet(GLUT_ELAPSED_TIME) + (nextWave * 1000);
	output->trackTime = glutGet(GLUT_ELAPSED_TIME);
	isDead = true;
}

void Game::updateGameState(float dt) {
	float time = (float)glutGet(GLUT_ELAPSED_TIME);
	// INPUT FLAGS
	if (isDead) {
		output->trackTime = time;
		return;
	}
	
	if (input->forwardFlag) {
		player->fart(); 
		player->pos = mc::nextPos(player->pos, player->dir, player->v, dt);
	};

	if (input->leftFlag) player->dir = mc::rotateVec(player->dir, SENSITIVITY);

	if (input->rightFlag) player->dir = mc::rotateVec(player->dir, -SENSITIVITY);

	if (input->shootFlag) {
		if (time > player->nextBullet) {
			player->shoot(time);
			player->nextBullet = glutGet(GLUT_ELAPSED_TIME) + 100;
		}

	}

	if (player->pos.x + player->r >= ARENA_W) {
		player->dir = mc::rotateVec(player->dir, -90);
	}

	if (time > nextWaveT) {
		nextWave *= WAVE_MULTI;
		nextWaveT = glutGet(GLUT_ELAPSED_TIME) + (nextWave * 1000);
		nAsteroids++;
	}
	// NEXT SPAWN
	if (time > nextSpawn) {
		nextSpawn = time + mc::randNum(1500, 4000); // random int
		for (int i = 0; i < nAsteroids; i++) {
			ents.push_back(new Asteroid(player->pos));
		}
	}

	for (Entity* ent : ents) {
		ent->update(dt);
	}

	for (Particle* particle : player->particles) {
		particle->update(dt);
	}

	while (player->particles.size() != 0 && player->particles.front()->size < 0) {
		player->particles.pop_front();
	}

	// Check collosions
	collisions();
	glutPostRedisplay();

}

void Game::onIdle(void) { 
	float t, dt;
	static float last_t = 0.0;
	t = (float) glutGet(GLUT_ELAPSED_TIME);
	t = t / 1000.0f;
	dt = t - last_t;
	last_t = t;
	updateGameState(dt);
	this->dt = dt;
}

// GLUT Callbacks
void Game::onIdleWrapper() {
	gameInstance->onIdle();
}

void Game::bindCallbacks() {
	glutDisplayFunc(output->onDisplayWrapper);
	glutReshapeFunc(output->onReshapeWrapper);
	// INPUT //
	// KEYBOARD
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(input->onKeyPressWrapper);
	glutSpecialFunc(input->onSpecialKeyPressWrapper);
	glutKeyboardUpFunc(input->onKeyReleaseWrapper);
	glutSpecialUpFunc(input->onSpecialKeyReleaseWrapper);
	// MOUSE
	glutMouseFunc(input->onMouseButtonWrapper);
	glutPassiveMotionFunc(input->onMouseMoveWrapper);
	glutMotionFunc(input->onMouseMoveWrapper);
	// Game Binds
	glutIdleFunc(gameInstance->onIdleWrapper);
}
