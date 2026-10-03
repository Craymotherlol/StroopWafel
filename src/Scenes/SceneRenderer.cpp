#include "Scenes/SceneRenderer.h"
#include "main.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ developer puts static variables inside classes the old fashioned way
WafelFrame sceneFrameRenderer::Renderer;

void sceneFrameRenderer::Begin()
{
    FrameBufferShader.Use();
    FrameBufferShader.setInt("screenTexture", 0);

    float quadVertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    glGenVertexArrays(1, &screenVAO);
    glGenBuffers(1, &screenVBO);
    glBindVertexArray(screenVAO);
    glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    Renderer.createFrameBuffer();
}

void sceneFrameRenderer::End()
{
    CryingMoon.reset();
}

void sceneFrameRenderer::Update()
{
}

void sceneFrameRenderer::Render()
{

    glBindFramebuffer(GL_FRAMEBUFFER, Renderer.FBO);
    glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    CryingMoon->transform = glm::rotate(CryingMoon->transform, DeltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

    CryingMoon->GetShader()->Use();
    CryingMoon->GetShader()->setMatrix4("model", glm::value_ptr(CryingMoon->transform));

    CryingMoon->Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    FrameBufferShader.Use();
    glBindVertexArray(screenVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, Renderer.TEXTURE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glBindVertexArray(0);
    //glUseProgram(0);


}