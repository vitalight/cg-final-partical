#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>

#include <GL/glew.h>
#include "includes/stb_image.h"

#include "Shader.h"
#include "Model.h"
#include "Mesh.h"

/***************************************************************
* [ResourceManager]
*
*	A static singleton ResourceManager class that hosts several
*	functions to load Textures and Shaders. Each loaded texture
*	and/or shader is also stored for future reference by string
*	handles. All functions and resources are static and no
*	public constructor is defined.
****************************************************************/

class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Model*> Models;

	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	static Shader LoadShader(const GLchar *shaderName);
	static Shader GetShader(std::string name);

	static Model *LoadModel(std::string path, std::string name, std::string shaderName, glm::vec3 offset, bool gamma = false);
	static Model *LoadModel(std::string name, std::string shaderName, glm::vec3 offset);
	static Model *LoadFireModel(std::string shaderName, std::string texturePath);
	static Model *LoadPlanetModel(std::string name, std::string shaderName, glm::vec3 offset);
	static Model *GetModel(std::string name);

	static void Clear();
private:
	// singleton constructor
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
};