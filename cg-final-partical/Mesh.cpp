#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, glm::vec3 color)
	: vertices(vertices), indices(indices), textures(textures), type(MESH_TEXTURE)
{
	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	colors.push_back(color);
	setupMesh();
}

Mesh::Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, vector<glm::vec3> &colors)
	: vertices(vertices), indices(indices), colors(colors), type(MESH_GROUND)
{
	// now that we have all the required data, set the vertex buffers and its attribute pointers.
	setupMesh();
}

void Mesh::Draw(Light light, Camera camera, Shader shader)
{
	if (colors.size() == 1) {
		shader.SetVector3f("color", colors[0]);
	}
	shader.SetVector3f("lightColor", light.Color);
	shader.SetVector3f("lightPos", light.Position);
	shader.SetVector3f("lightBias", light.LightBias);
	shader.SetVector3f("viewPos", camera.Position);
	//glUniform3f(glGetUniformLocation(shader.ID, "diffuseColor"), material.diffuse.r, material.diffuse.g, material.diffuse.b);
	// bind appropriate textures
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
										  // retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular") {
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		}
		else if (name == "texture_normal") {
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		}
		else if (name == "texture_height") {
			number = std::to_string(heightNr++); // transfer unsigned int to stream
		}
		// now set the sampler to the correct texture unit
		//glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
		shader.SetInteger((name + number).c_str(), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::offset(glm::vec3 ofs)
{
	for (Vertex ver : vertices)
	{
		ver.Position += ofs;
	}
}

void Mesh::setupMesh()
{
	// create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	/*if (type = MESH_GROUND) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	}
	else {*/
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));


	glBindVertexArray(0);
}