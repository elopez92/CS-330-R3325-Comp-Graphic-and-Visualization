#include "RenderUtils.h"

void RenderLight(GLuint programId, GLuint vao, GLuint nIndices, GLuint viewLoc, GLuint projLoc, GLuint modelLoc, glm::mat4& view, glm::mat4& projection, glm::mat4 model)
{
    glUseProgram(programId);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void RenderCubeLight(GLuint programId, GLuint vao, GLuint nIndices, GLuint viewLoc, GLuint projLoc, GLuint modelLoc, glm::mat4& view, glm::mat4& projection, glm::mat4 model)
{
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void RenderMesh(GLuint vao, GLuint nIndices, GLuint modelLoc, glm::mat4 model, GLuint texture)
{
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(vao);
    // bind textures on corresponding texture units
    if (texture != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_SHORT, nullptr);

    glBindVertexArray(0);
}

void RenderMeshTriangles(GLuint vao, GLuint nIndices, GLuint modelLoc, glm::mat4 model, GLuint texture)
{
    glBindVertexArray(vao);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    // bind textures on corresponding texture units
    if (texture != 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    glDrawArrays(GL_TRIANGLES, 0, nIndices);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

