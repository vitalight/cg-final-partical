#pragma once

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"

#include "Model.h"
#include "Light.h"
#include "ResourceManager.h"
#include "Config.h"
#include "Camera.h"

/***********************************************************
* [Entity]
*
*	This class is used to store the physical information
*   and handle the movement of an item in the 3D world.
************************************************************/
class Entity
{
public:
	glm::vec3 position, axis, scale;
	glm::vec3 offset;
	float angle;

	Entity(Model *model,
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 scale = glm::vec3(1, 1, 1),
		float angle = 0.0f,
		glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));

	Entity(Model *model,
		glm::vec3 position = glm::vec3(0, 0, 0),
		float scale = 1.0f,
		float angle = 0.0f,
		glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));

	Entity(string modelName,
		glm::vec3 position = glm::vec3(0, 0, 0),
		float scale = 1.0f,
		float angle = 0.0f,
		glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f));

	void configPlanet(float rotate_velocity, float radius = 0, float angular_velocity = 0);
	void configMoon(Entity *parent, float rotate_velocity, float radius = 0, float angular_velocity = 0);
	void configShuttle(Camera &camera);

	void Draw(Light light, Camera camera, float time);
	
	void switchShader();
	
	glm::vec3 getTail();

private:
	float mytime = NV_ENTITY_INITIAL_FRAME;

	enum Entity_type { ENTITY_NORMAL, ENTITY_PLANET, ENTITY_MOON, ENTITY_SHUTTLE } type;
	float radius, angular_velocity, rotate_velocity;
	Entity *parent;

	Model *model;

	void update(float time);
};

