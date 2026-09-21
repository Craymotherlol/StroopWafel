#ifndef STROOP_GL_VERTEXDATA_H
#define STROOP_GL_VERTEXDATA_H
#include "Window.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    //glm::vec2 TexCoords;
};

#endif