#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void RenderLight(GLuint programId, GLuint vao, GLuint nIndices, GLuint viewLoc, GLuint projLoc, GLuint modelLoc, glm::mat4& view, glm::mat4& projection, glm::mat4 model);
void RenderCubeLight(GLuint programId, GLuint vao, GLuint nIndices, GLuint viewLoc, GLuint projLoc, GLuint modelLoc, glm::mat4& view, glm::mat4& projection, glm::mat4 model);

void RenderMesh(GLuint vao, GLuint nIndices, GLuint modelLoc, glm::mat4 model, GLuint texture);

void RenderMeshTriangles(GLuint vao, GLuint nIndices, GLuint modelLoc, glm::mat4 model, GLuint texture);

