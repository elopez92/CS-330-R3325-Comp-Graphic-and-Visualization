#include <iostream>         // cout, cerr
#include <cstdlib>          // EXIT_FAILURE
#include <GL/glew.h>        // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "../Project/Linking/stb/stb_image.h"

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include "MeshUtils.h"
#include "RenderUtils.h"

using namespace std; // Standard namespace


// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "Project"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;


    // Main GLFW window
    GLFWwindow* gWindow = nullptr;
    // Add a new struct to store data for the square light
    GLMesh lightSquare;
    // Plane mesh data
    GLMesh gTableMesh;
    // Triangle mesh data
    GLMesh gMesh;
    GLMesh gEggMesh;
    GLMesh gButterMesh;
    GLMesh gCubeMesh;
    // Shader program
    GLuint gProgramId;

    GLuint gLightProgramId;
    glm::vec2 gUVScale(5.0f, 5.0f);

    // Texture id
    GLuint gTextureIdLightWood;
    GLuint gTextureIdDarkWood;
    GLuint gTextureIdEgg;
    GLuint gTextureIdButter;

    glm::vec3 cameraPosition = glm::vec3(0.0f, 2.0f, 20.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    GLfloat cameraSpeed = 0.1f;
    GLfloat zoomSpeed = 2.0f;
    GLfloat cameraRotationSpeed = 0.5f;
    bool firstMouse = true;
    GLfloat lastX = WINDOW_WIDTH / 2.0f;
    GLfloat lastY = WINDOW_HEIGHT / 2.0f;
    GLfloat yaw = -90.0f;
    GLfloat pitch = 0.0f;
    GLfloat zoom = 50.0f;

    bool isOrthoView = false;


    glm::vec3 gObjectColor(1.f, 0.2f, 0.0f);
    glm::vec3 gLightColor(1.0f, 0.96f, 0.87f);

    // Light position and scale
    glm::vec3 gLightPosition(0.0f, 10.0f, 3.0f);
    glm::vec3 gLightScale(0.3f);
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void UProcessInput(GLFWwindow* window);
void ProcessMouseScroll(float yoffset);
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
bool CreateTexture(const char* filename, GLuint& textureId);
void DestroyTexture(GLuint textureId);
void UDestroyMesh(GLMesh& mesh);
void URender();
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId);
void UDestroyShaderProgram(GLuint programId);



// Images are loaded with Y axis going down, but OpenGL's Y axis goes up
void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
    for (int j = 0; j < height / 2; ++j)
    {
        int index1 = j * width * channels;
        int index2 = (height - 1 - j) * width * channels;

        for (int i = width * channels; i > 0; --i)
        {
            unsigned char tmp = image[index1];
            image[index1] = image[index2];
            image[index2] = tmp;
            ++index1;
            ++index2;
        }
    }
}

std::string loadShaderFromFile(const char* filename)
{
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &gWindow))
        return EXIT_FAILURE;

    UCreateSquareLight(lightSquare);
    UCreateTable(gTableMesh);

    // Create the mesh
    UCreateCylinder(gMesh, 1.0f, 5.0f, 10.0f); // Calls the function to create the Vertex Buffer Object
    UCreateEggMesh(gEggMesh);
    UCreateCubeWithoutIndices(gButterMesh);
    UCreateCube(gCubeMesh);

    // load textures
    const char* lightWoodFile = "resources/textures/lightwood_texture.jpg";
    if (!CreateTexture(lightWoodFile, gTextureIdLightWood))
    {
        cout << "Failed to load texture " << lightWoodFile << endl;
        return EXIT_FAILURE;
    }

    // load textures
    const char* darkWoodFile = "resources/textures/darkwood_texture.jpg";
    if (!CreateTexture(darkWoodFile, gTextureIdDarkWood))
    {
        cout << "Failed to load texture " << darkWoodFile << endl;
        return EXIT_FAILURE;
    }

    // load textures
    const char* eggFile = "resources/textures/egg-shell.png";
    if (!CreateTexture(eggFile, gTextureIdEgg))
    {
        cout << "Failed to load texture " << eggFile << endl;
        return EXIT_FAILURE;
    }


    // tell opengl fo reach sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(gProgramId);
    // se set the texture as texture unit 0
    glUniform1i(glGetUniformLocation(gProgramId, "uTexture"), 0);

    string vtxShaderSource = loadShaderFromFile("vertex_shader.glsl");
    string fragShaderSource = loadShaderFromFile("fragment_shader.glsl");

    // Create the shader program
    if (!UCreateShaderProgram(vtxShaderSource.c_str(), fragShaderSource.c_str(), gProgramId))
        return EXIT_FAILURE;



    string lightVtxShaderSource = loadShaderFromFile("light_vertex_shader.glsl");
    string lightFragShaderSource = loadShaderFromFile("light_fragment_shader.glsl");
    // Create the shader program
    if (!UCreateShaderProgram(lightVtxShaderSource.c_str(), lightFragShaderSource.c_str(), gLightProgramId))
        return EXIT_FAILURE;

    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.678f, 0.639f, 0.58f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // input
        // -----
        UProcessInput(gWindow);

        // Render this frame
        URender();

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(gMesh);
    UDestroyMesh(gTableMesh);
    UDestroyMesh(gButterMesh);

    // Release shader program
    UDestroyShaderProgram(gProgramId);

    exit(EXIT_SUCCESS); // Terminates the program successfully
}


// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);
    glfwSetKeyCallback(*window, key_callback);
    glfwSetScrollCallback(*window, MouseScrollCallback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}

void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        // Toggle between orthographic and perspective views
        isOrthoView = !isOrthoView;
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;//gCamera.ProcessKeyboard(LEFT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;// gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPosition.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPosition.y -= cameraSpeed;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw whenever the mouse moves, this callback is called
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const GLfloat sensitivity = .2f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

bool CreateTexture(const char* filename, GLuint& textureId)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        flipImageVertically(image, width, height, channels);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            cout << "OpenGL error after glTexImage2D: " << error << endl;
        }

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture flitering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        if (channels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                cout << "OpenGL error after glTexImage2D: " << error << endl;
            }
        }
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            stbi_image_free(image);
            glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture

        return true;
    }

    // error loading the image
    return false;
}

void DestroyTexture(GLuint textureId)
{
    glGenTextures(1, &textureId);
}


// Functioned called to render a frame
void URender()
{
    // Enable z-depth
    glEnable(GL_DEPTH_TEST);

    // Clear the frame and z buffers
    glClearColor(0.231f, 0.227f, 0.22f, 1.0f);
    //glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // 1. Scales the object by 1.5
    glm::mat4 planeScale = glm::scale(glm::vec3(1.5f, 1.5f, 1.5f));
    // 2. Rotates shape by 15 degrees in the x axis
    glm::mat4 planeRotation = glm::rotate(glm::radians(-1.0f), glm::vec3(1.0, 0.0f, 0.0f));
    // 3. Place object at the origin
    glm::mat4 planeTranslation = glm::translate(glm::vec3(0.0f, -0.25f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 planeModel = planeTranslation * planeRotation * planeScale;

    // 1. Scales the object by .5
    glm::mat4 scale = glm::scale(glm::vec3(.50f, .5f, .5f));
    // 2. Rotates shape by 15 degrees in the x axis
    glm::mat4 rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0, 0.0f, 1.0f));
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.40f, 0.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * scale;


    // 1. Rotates the second cylinder to lie flat along the x-axis
    glm::mat4 rotation2 = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // 2. Scales the second cylinder
    glm::mat4 scale2 = glm::scale(glm::vec3(0.1f, 0.2f, 0.1f));
    // 3. Place the second cylinder next to the first one
    glm::mat4 translation2 = glm::translate(glm::vec3(1.5f, 0.40f, 0.0f)); // Adjust the position as needed
    // Model matrix for the second cylinder
    glm::mat4 model2 = translation2 * rotation2 * scale2;


    // 1. Rotates the second cylinder to lie flat along the x-axis
    glm::mat4 rotation3 = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // 2. Scales the second cylinder
    glm::mat4 scale3 = glm::scale(glm::vec3(0.1f, 0.2f, 0.1f));
    // 3. Place the second cylinder next to the first one
    glm::mat4 translation3 = glm::translate(glm::vec3(-1.5f, 0.40f, 0.0f)); // Adjust the position as needed
    // Model matrix for the second cylinder
    glm::mat4 model3 = translation3 * rotation3 * scale3;

    // 1. Rotates the second cylinder to lie flat along the x-axis
    glm::mat4 butterRot = glm::rotate(glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // 2. Scales the second cylinder
    glm::mat4 butterScale = glm::scale(glm::vec3(.25f, .25f, 1.f));
    // 3. Place the second cylinder next to the first one
    glm::mat4 butterTrans = glm::translate(glm::vec3(-1.5f, 0.05f, 2.0f)); // Adjust the position as needed
    // Model matrix for the second cylinder
    glm::mat4 butterModel = butterTrans * butterRot * butterScale;


    // Transforms the camera: move the camera back (z axis)
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    // Creates a perspective projection
    glm::mat4 projection;
    if (isOrthoView)
        projection = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);
    else
        projection = glm::perspective(glm::radians(zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);


  

    glUseProgram(gLightProgramId);
    // Retrieves and passes transform matrices to the Shader program
    GLint lightModelLoc = glGetUniformLocation(gLightProgramId, "model");
    GLint lightViewLoc = glGetUniformLocation(gLightProgramId, "view");
    GLint lightProjLoc = glGetUniformLocation(gLightProgramId, "projection");

    // 1. Scales the object by 1.5
    glm::mat4 lightScale = glm::scale(glm::vec3(1.f, 1.f, 1.f));
    // 2. Rotates shape by 15 degrees in the x axis
    glm::mat4 lightRotation = glm::rotate(glm::radians(70.0f), glm::vec3(1.0, 1.0f, 0.0f));
    // 3. Place object at the origin
    glm::mat4 lightTranslation = glm::translate(gLightPosition);
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 lightModel = lightTranslation * lightScale * lightRotation;

    RenderCubeLight(gLightProgramId, gCubeMesh.vao, gCubeMesh.nIndices, lightViewLoc, lightProjLoc, lightModelLoc, view, projection, lightModel);



    // Set the shader to be used
    glUseProgram(gProgramId);


    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(gProgramId, "model");
    GLint viewLoc = glGetUniformLocation(gProgramId, "view");
    GLint projLoc = glGetUniformLocation(gProgramId, "projection");

    // Reference matrix uniforms from the Cube Shader program for the cub color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(gProgramId, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(gProgramId, "lightColor");
    GLint lightPosLoc = glGetUniformLocation(gProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(gProgramId, "viewPosition");


    // Pass color, light, and camera data to the Cube Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPosLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLint UVScaleLoc = glGetUniformLocation(gProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(gUVScale));

    RenderMeshTriangles(gButterMesh.vao, gButterMesh.nIndices, modelLoc, butterModel, 0);
    RenderMesh(gTableMesh.vao, gTableMesh.nIndices, modelLoc, planeModel, gTextureIdDarkWood);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTextureIdLightWood);

    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, NULL); // Draws the triangle

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
    // Draws the triangles for the second cylinder
    glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, NULL);


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
    // Draws the triangles for the second cylinder
    glDrawElements(GL_TRIANGLES, gMesh.nIndices, GL_UNSIGNED_SHORT, NULL);


    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(eggModel));
    //// Draws the triangles for the second cylinder
    //glDrawElements(GL_TRIANGLES, gEggMesh.nIndices, GL_UNSIGNED_SHORT, NULL);


    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(gWindow);    // Flips the the back buffer with the front buffer every frame.
}



void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}


// Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{
    // Compilation and linkage error reporting
    int success = 0;
    char infoLog[512];

    // Create a Shader program object.
    programId = glCreateProgram();

    // Create the vertex and fragment shader objects
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Retrive the shader source
    glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
    glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

    // Compile the vertex shader, and print compilation errors (if any)
    glCompileShader(vertexShaderId); // compile the vertex shader
    // check for shader compile errors
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glCompileShader(fragmentShaderId); // compile the fragment shader
    // check for shader compile errors
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return false;
    }

    // Attached compiled shaders to the shader program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);

    glLinkProgram(programId);   // links the shader program
    // check for linking errors
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return false;
    }

    glUseProgram(programId);    // Uses the shader program

    return true;
}


void UDestroyShaderProgram(GLuint programId)
{
    glDeleteProgram(programId);
}

void ProcessMouseScroll(float yoffset)
{
    zoom -= (float)yoffset * zoomSpeed;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

