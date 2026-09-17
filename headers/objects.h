#ifndef STROOPWAFEL_OPENGL_OBJECTS_H
#define STROOPWAFEL_OPENGL_OBJECTS_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


// NOTES
// Just to note that the VAO will automatically bind when you call the constructor!!
//

class VBO
{

public:
    unsigned int ID;

    VBO(float *vertices, GLsizeiptr vertsize);

    void Bind();
    void Unbind();
    void Delete();
};

class VAO
{

public:
    unsigned int ID;

    VAO();

    void Bind();
    void Unbind();
    void Delete();
    void LinkVBO(VBO &vbo, unsigned int layout, int pointerSize);
};

class EBO
{

public:
    unsigned int ID;

    EBO(unsigned int *indices, GLsizeiptr indisize);

    void Bind();
    void Unbind();
    void Delete();
};

class Shader
{
public:
    unsigned int  ID;

    Shader(const char *vertexShaderFile, const char *fragmentShaderFile);

    void Activate();

    void Delete();
};

struct Mesh
{
    VAO vao;
    VBO vbo;
    EBO ebo;

    Mesh(float *vertices, GLsizeiptr vertsize, unsigned int *indices, GLsizeiptr indisize) : vao(), vbo(vertices, vertsize), ebo(indices, indisize) {}
};

struct GLObject
{
public:
    std::string id;
    Shader shaders;
    Mesh mesh;

    void UnbindAll();
    void DeleteAll();
};

#endif