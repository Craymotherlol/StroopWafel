#ifndef STROOPWAFEL_OPENGL_OBJECTS_H
#define STROOPWAFEL_OPENGL_OBJECTS_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Objects/Mesh.h>
#include <Objects/Shader.h>

struct GLObject
{
public:
    std::string id;
    Shader shaders;
    Mesh mesh;
};

#endif