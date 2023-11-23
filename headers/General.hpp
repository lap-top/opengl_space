#ifndef TYPES_H
#define TYPES_H

typedef struct {
	float r, g, b;
} colour;

typedef struct {
	float x, y; // pos -> dir 
} vec2d;

#define M_PI           3.14159265358979323846 
#define HALF_C M_PI/180

//////////////////
//     CONFIG	//
//////////////////


// DEBUG
#define DEBUG FALSE
// ARENA SETTINGS
#define ARENA_W 300
#define ARENA_H 200


// ASTEROID SETTINGS 
#define A_VELOCITY_MIN 30
#define A_VELOCITY_MAX 50

#define A_RADIUS_MIN 5
#define A_RADIUS_MAX 8

// SHIP SETTINGS
// player colour
#define S_R 0.7
#define S_G 0
#define S_B 0.3

// BULLET colour
#define S_B_R 0
#define S_B_G 0.7
#define S_B_B 0

#define SENSITIVITY 5.0
#define S_VELOCITY 65

// Wave
// Difficulty increases after currentWaveTime*WAVE_MULTI
#define WAVE_MULTI 1.5 //
#define WAVE_INIT 10 // Initial wave time,
#endif