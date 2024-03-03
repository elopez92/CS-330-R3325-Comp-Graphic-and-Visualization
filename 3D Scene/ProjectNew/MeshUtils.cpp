#include "MeshUtils.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using namespace std;

void UCreateSquareLight(GLMesh& mesh) {
    // Vertex data for the square representing the white light
    GLfloat lightVerts[] = {
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    // Indices for the square
    GLushort lightIndices[] = {
        0, 1, 2,
        0, 2, 3
    };

    const GLuint floatsPerVertex = 3;

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(2, mesh.vbos);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightVerts), lightVerts, GL_STATIC_DRAW);

    mesh.nIndices = sizeof(lightIndices) / sizeof(lightIndices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);
}

void UCreateTable(GLMesh& table) {
    const float REPEAT = 1;
    // Vertex data for the plane
    GLfloat tableVerts[] = {
        // Positions            // Normals           // Texture coordinates
       // Top surface of the table
       -5.0f, 0.0f, -4.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (bottom vertices)
        5.0f, 0.0f, -4.0f,     0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (bottom vertices)
       -5.0f, 0.0f,  4.0f,     0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (bottom vertices)
        5.0f, 0.0f,  4.0f,     0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (bottom vertices)
       -5.0f, 0.1f, -4.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (top vertices)
        5.0f, 0.1f, -4.0f,     0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (top vertices)
       -5.0f, 0.1f,  4.0f,     0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (top vertices)
        5.0f, 0.1f,  4.0f,     0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (top vertices)

        // Legs
        // Leg 1
        -4.75f, 0.0f, -3.75f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (bottom vertices)
        -4.75f, 0.0f, -3.25f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (bottom vertices)
        -4.25f, 0.0f, -3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (bottom vertices)
        -4.25f, 0.0f, -3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (bottom vertices)
        -4.75f, -5.f, -3.75f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (top vertices)
        -4.75f, -5.f, -3.25f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (top vertices)
        -4.25f, -5.f, -3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (top vertices)
        -4.25f, -5.f, -3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (top vertices)

        // Leg 2
         4.25f, 0.0f, -3.75f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (bottom vertices)
         4.25f, 0.0f, -3.25f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (bottom vertices)
         4.75f, 0.0f, -3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (bottom vertices)
         4.75f, 0.0f, -3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (bottom vertices)
         4.25f, -5.f, -3.75f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (top vertices)
         4.25f, -5.f, -3.25f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (top vertices)
         4.75f, -5.f, -3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (top vertices)
         4.75f, -5.f, -3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (top vertices)

         // Leg 3
         -4.75f, 0.0f,  3.25f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (bottom vertices)
         -4.75f, 0.0f,  3.75f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (bottom vertices)
         -4.25f, 0.0f,  3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (bottom vertices)
         -4.25f, 0.0f,  3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (bottom vertices)
         -4.75f, -5.f,  3.25f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (top vertices)
         -4.75f, -5.f,  3.75f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (top vertices)
         -4.25f, -5.f,  3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (top vertices)
         -4.25f, -5.f,  3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (top vertices)

         // Leg 4
          4.25f, 0.0f,  3.25f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (bottom vertices)
          4.25f, 0.0f,  3.75f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (bottom vertices)
          4.75f, 0.0f,  3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (bottom vertices)
          4.75f, 0.0f,  3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (bottom vertices)
          4.25f, -5.f,  3.25f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Dark brown color (top vertices)
          4.25f, -5.f,  3.75f,   0.0f, 1.0f, 0.0f,   0.0f, REPEAT, // Dark brown color (top vertices)
          4.75f, -5.f,  3.25f,   0.0f, 1.0f, 0.0f,   REPEAT, 0.0f, // Dark brown color (top vertices)
          4.75f, -5.f,  3.75f,   0.0f, 1.0f, 0.0f,   REPEAT, REPEAT, // Dark brown color (top vertices)
    };

    // Indices for the plane
    GLushort planeIndices[] = {
        // Indices for the top surface of the table
     0, 1, 2,
     1, 3, 2,
     // Indices for the bottom surface of the table
     4, 6, 5,
     5, 6, 7,
     // Indices for the vertical faces of the table
     0, 4, 1,
     1, 4, 5,
     2, 3, 6,
     3, 7, 6,
     // Indices for the legs (rectangular prisms)
     // Leg 1
     8, 9, 10,
     9, 11, 10,
     8, 10, 12,
     9, 13, 11,
     10, 11, 14,
     10, 14, 12,
     11, 13, 15,
     11, 15, 14,
     8, 12, 9,
     9, 12, 13,
     12, 14, 13,
     13, 14, 15,
     // Leg 2
     16, 17, 18,
     17, 19, 18,
     16, 18, 20,
     17, 21, 19,
     18, 19, 22,
     18, 22, 20,
     19, 21, 23,
     19, 23, 22,
     16, 20, 17,
     17, 20, 21,
     20, 22, 21,
     21, 22, 23,
     // Leg 3
     24, 25, 26,
     25, 27, 26,
     24, 26, 28,
     25, 29, 27,
     26, 27, 30,
     26, 30, 28,
     27, 29, 31,
     27, 31, 30,
     24, 28, 25,
     25, 28, 29,
     28, 30, 29,
     29, 30, 31,
     // Leg 4
     32, 33, 34,
     33, 35, 34,
     32, 34, 36,
     33, 37, 35,
     34, 35, 38,
     34, 38, 36,
     35, 37, 39,
     35, 39, 38,
     32, 36, 33,
     33, 36, 37,
     36, 38, 37,
     37, 38, 39
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerTexture = 2;

    glGenVertexArrays(1, &table.vao);
    glBindVertexArray(table.vao);

    glGenBuffers(2, table.vbos);

    glBindBuffer(GL_ARRAY_BUFFER, table.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tableVerts), tableVerts, GL_STATIC_DRAW);

    table.nIndices = sizeof(planeIndices) / sizeof(planeIndices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, table.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerTexture + floatsPerNormal);

    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerTexture, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

void UCreateCylinder(GLMesh& mesh, float radius, float height, int numSegments) {
    // Calculate the number of vertices and indices needed
    int numVertices = numSegments * 2 + 2; // Each segment requires 2 vertices + 2 for caps
    int numIndices = numSegments * 12;     // Each segment requires 6 indices (3 for each triangle) + 6 for caps

    // Resize the arrays to store vertex and index data
    std::vector<GLfloat> verts;
    verts.reserve(numVertices * 9); // 9 floats per vertex (3 for position, 4 for color, 2 for texture coordinates)

    std::vector<GLushort> indices;
    indices.reserve(numIndices);

    // Generate cylinder vertices
    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0f * glm::pi<float>() * static_cast<float>(i) / static_cast<float>(numSegments);
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        float u = static_cast<float>(i) / static_cast<float>(numSegments); // Calculate texture coordinate u
        float v = 0.5f;

        // Top vertex
        verts.push_back(x);
        verts.push_back(height * 0.5f);
        verts.push_back(z);
        verts.push_back(x);
        verts.push_back(0.0f);
        verts.push_back(z);
        verts.push_back(u);    // Texture coordinate u
        verts.push_back(v);    // Texture coordinate v (top of texture)

        // Bottom vertex
        verts.push_back(x);
        verts.push_back(-height * 0.5f);
        verts.push_back(z);
        verts.push_back(x);
        verts.push_back(0.0f);
        verts.push_back(z);
        verts.push_back(u);    // Texture coordinate u
        verts.push_back(v);    // Texture coordinate v (bottom of texture)
    }

    // Add top and bottom center vertices for caps
    verts.push_back(0.0f); // Top center x
    verts.push_back(height * 0.5f); // Top center y
    verts.push_back(0.0f); // Top center z
    verts.push_back(0.0f); // Top center normal x
    verts.push_back(1.0f); // Top center normal y
    verts.push_back(0.0f); // Top center normal z
    verts.push_back(0.5f); // Texture coordinate u (center of texture)
    verts.push_back(1.0f); // Texture coordinate v (top of texture)

    verts.push_back(0.0f); // Bottom center x
    verts.push_back(-height * 0.5f); // Bottom center y
    verts.push_back(0.0f); // Bottom center z
    verts.push_back(0.0f); // Bottom center normal x
    verts.push_back(-1.0f); // Bottom center normal y
    verts.push_back(0.0f); // Bottom center normal z
    verts.push_back(0.5f); // Texture coordinate u (center of texture)
    verts.push_back(0.0f); // Texture coordinate v (bottom of texture)

    // Generate cylinder indices
    for (int i = 0; i < numSegments; ++i)
    {
        // Indices for the sides of the cylinder
        int currentVertex = i * 2;
        int nextVertex = (i + 1) * 2;

        indices.push_back(currentVertex);
        indices.push_back(nextVertex);
        indices.push_back(nextVertex + 1);

        indices.push_back(currentVertex);
        indices.push_back(nextVertex + 1);
        indices.push_back(currentVertex + 1);
    }

    // Generate indices for the top and bottom caps
    int topCenterIndex = numVertices - 2;
    int bottomCenterIndex = numVertices - 1;
    for (int i = 0; i < numSegments; ++i)
    {
        int currentVertex = i * 2;
        int nextVertex = (i + 1) * 2;

        // Indices for the top cap
        indices.push_back(topCenterIndex);
        indices.push_back(nextVertex);
        indices.push_back(currentVertex);

        // Indices for the bottom cap
        indices.push_back(bottomCenterIndex);
        indices.push_back(currentVertex + 1);
        indices.push_back(nextVertex + 1);
    }

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerTexture = 2;

    // Set up the VAO and VBOs for the cylinder
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(2, mesh.vbos);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);


    // Specify the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


    // Unbind VAO
    glBindVertexArray(0);

    // Store the number of indices
    mesh.nIndices = numIndices;
}

void UCreateEggMesh(GLMesh& mesh) {
    // Vertex data for the egg
    GLfloat eggVerts[] = {
        // Position            // Color (white)      // Texture Coordinates // Normal
        // Top half of the egg
        0.0f, 0.5f, 0.0f,       1.0f, 1.0f, 1.0f,     0.5f, 1.0f,           0.0f, 0.7f, 0.0f, // Top point
        0.2f, 0.4f, 0.1f,       1.0f, 1.0f, 1.0f,     0.6f, 0.8f,           0.2f, 0.6f, 0.1f, // Upper right
        0.4f, 0.3f, 0.2f,       1.0f, 1.0f, 1.0f,     0.8f, 0.6f,           0.4f, 0.5f, 0.2f, // Upper right
        0.5f, 0.0f, 0.25f,      1.0f, 1.0f, 1.0f,     1.0f, 0.5f,           0.5f, 0.0f, 0.25f, // Right
        0.4f, -0.3f, 0.2f,      1.0f, 1.0f, 1.0f,     0.8f, 0.4f,           0.4f, -0.3f, 0.2f, // Lower right
        0.2f, -0.4f, 0.1f,      1.0f, 1.0f, 1.0f,     0.6f, 0.2f,           0.2f, -0.4f, 0.1f, // Lower right
        0.0f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,     0.5f, 0.0f,           0.0f, -0.5f, 0.0f, // Bottom point

        // Bottom half of the egg
        -0.2f, -0.4f, 0.1f,     1.0f, 1.0f, 1.0f,     0.4f, 0.2f,           -0.2f, -0.4f, 0.1f, // Lower left
        -0.4f, -0.3f, 0.2f,     1.0f, 1.0f, 1.0f,     0.2f, 0.4f,           -0.4f, -0.3f, 0.2f, // Lower left
        -0.5f, 0.0f, 0.25f,     1.0f, 1.0f, 1.0f,     0.0f, 0.5f,           -0.5f, 0.0f, 0.25f, // Left
        -0.4f, 0.3f, 0.2f,      1.0f, 1.0f, 1.0f,     0.2f, 0.6f,           -0.4f, 0.3f, 0.2f, // Upper left
        -0.2f, 0.4f, 0.1f,      1.0f, 1.0f, 1.0f,     0.4f, 0.8f,           -0.2f, 0.4f, 0.1f  // Upper left
    };

    GLushort eggIndices[] = {
        // Top half indices
        0, 1, 6,
        1, 2, 6,
        2, 3, 6,
        3, 4, 6,
        4, 5, 6,

        // Bottom half indices
        0, 7, 1,
        1, 7, 2,
        2, 7, 3,
        3, 7, 4,
        4, 7, 5,
        5, 7, 6,

        // Connect top and bottom
        0, 1, 7,
        1, 2, 7,
        2, 3, 7,
        3, 4, 7,
        4, 5, 7,
        5, 6, 7
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerColor = 3;
    const GLuint floatsPerTextureCoord = 2;
    const GLuint floatsPerNormal = 3;

    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(2, mesh.vbos);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(eggVerts), eggVerts, GL_STATIC_DRAW);

    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerColor + floatsPerTextureCoord);// The number of floats before each

    mesh.nIndices = sizeof(eggIndices) / sizeof(eggIndices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(eggIndices), eggIndices, GL_STATIC_DRAW);

    // Set up attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    // Unbind VAO
    glBindVertexArray(0);
}

void UCreateCube(GLMesh& mesh)
{
    GLfloat verts[] = {
        // Vertex Positions    // Normals            // Colors (r,g,b,a)
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    .96f, 0.88f, 0.71f, 1.0f, // Top Right Vertex 0
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    .96f, 0.88f, 0.71f, 1.0f, // Bottom Right Vertex 1
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    .96f, 0.88f, 0.71f, 1.0f, // Bottom Left Vertex 2
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    .96f, 0.88f, 0.71f, 1.0f, // Top Left Vertex 3

         0.5f, -0.5f, -1.0f,  0.0f, 0.0f, -1.0f,   .96f, 0.88f, 0.71f, 1.0f, // Bottom Right Vertex 4
         0.5f,  0.5f, -1.0f,  0.0f, 0.0f, -1.0f,   .96f, 0.88f, 0.71f, 1.0f, // Top Right Vertex 5
        -0.5f,  0.5f, -1.0f,  0.0f, 0.0f, -1.0f,   .96f, 0.88f, 0.71f, 1.0f, // Top Left Vertex 6
        -0.5f, -0.5f, -1.0f,  0.0f, 0.0f, -1.0f,   .96f, 0.88f, 0.71f, 1.0f  // Bottom Left Vertex 7
    };

    // Index data to share position data
GLushort indices[] = {
    0, 1, 3,  // Front Face Triangle 1
    1, 2, 3,  // Front Face Triangle 2
    0, 1, 4,  // Right Face Triangle 1
    0, 4, 5,  // Right Face Triangle 2
    0, 5, 3,  // Top Face Triangle 1
    5, 6, 3,  // Top Face Triangle 2
    4, 5, 6,  // Back Face Triangle 1
    4, 6, 7,  // Back Face Triangle 2
    1, 4, 7,  // Left Face Triangle 1
    1, 2, 7,  // Left Face Triangle 2
    2, 3, 6,  // Bottom Face Triangle 1
    2, 6, 7   // Bottom Face Triangle 2
};

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerColor = 4;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerColor);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(3, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(3);
    


}


// Implements the UCreateMesh function
void UCreateCubeWithoutIndices(GLMesh& mesh)
{
    // Position, Normal, and Color data
    GLfloat verts[] = {
        //Positions          //Normals           //Colors (r,g,b,a)
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Butter Color
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.99f, 0.91f, 0.71f, 1.0f,

       //Front Face         //Positive Z Normal  Butter Color
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
       0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.99f, 0.91f, 0.71f, 1.0f,

      //Left Face          //Negative X Normal  Butter Color
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,

     //Right Face         //Positive X Normal  Butter Color
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,

     //Bottom Face        //Negative Y Normal  Butter Color
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,

    //Top Face           //Positive Y Normal  Butter Color
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.99f, 0.91f, 0.71f, 1.0f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerColor = 4;

    mesh.nIndices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerColor));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, &mesh.vbos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 6 (x, y, z, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerColor);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(3, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(3);
}

