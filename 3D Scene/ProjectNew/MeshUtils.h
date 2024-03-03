#ifndef MESH_UTILS_H
#define MESH_UTILS_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

struct GLMesh {
    GLuint vao;
    GLuint vbos[2]; // Assuming each mesh has two VBOs
    GLsizei nIndices;
};

void UCreateSquareLight(GLMesh& mesh);
void UCreateTable(GLMesh& table);
void UCreateCylinder(GLMesh& mesh, float radius, float height, int numSegments);
void UCreateEggMesh(GLMesh& mesh);
void UCreateCube(GLMesh& mesh);
void UCreateCubeWithoutIndices(GLMesh& mesh);

#endif // MESH_UTILS_H
