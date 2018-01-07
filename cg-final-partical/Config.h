#pragma once

/****************************************
 * Main
 ****************************************/
// screen width
#define NV_SCR_WIDTH 1000
// screen height
#define NV_SCR_HEIGHT 600
// ascii number for keyboard-exit
#define NV_EXIT_ASCII 27

/****************************************
 * Light
 ****************************************/
// light source position
#define NV_LIGHT_POS (glm::vec3(0, 0, 0))
// light source color
#define NV_LIGHT_COL (glm::vec3(1.0f, 0.8f, 1.0f))
// light source bias against (ambient, diffuse, specular)
#define NV_LIGHT_BIAS (glm::vec3(0.3f, 0.8f, 0.5f))

/****************************************
 * Planet
 ****************************************/
// weight for planet rotation speed
#define NV_ROTATE_WEIGHT 0.2
// initial elapse time for entities // change to 3500
#define NV_ENTITY_INITIAL_FRAME 0

/****************************************
 * Asteroids
 ****************************************/
// numbers of asteroids flying everywhere
#define NV_FLYING_NUM 200
// numbers of asteroids that circle around sun
#define NV_CIRCLING_NUM 2000

// radius of circle around sun
#define NV_ROCK_RADIUS 1200
// random position generation offset
#define NV_ROCK_OFFSET 15.0f

// cycle for partical generation (unit: second)
#define NV_GENERATE_CYCLE 0.5
// cycle for partical cleanup (unit: second)
#define NV_CLEANUP_CYCLE 5

// range of destination position for flying asteroids
#define NV_CENTER_RANGE 1200
// range of generation position for flying asteroids
#define NV_FULL_RANGE 2000

// initial elapse time for flying asteroids
#define NV_INITIAL_FRAME 120.0f
// speed of flying asteroids
#define NV_PARTICAL_SPEED 10.0f
// rotate speed of asteroids 
#define NV_ROTATE_SPEED 0.8f
// revolute speed of circling asteroids
#define NV_ANGLE_SPEED 0.02f

