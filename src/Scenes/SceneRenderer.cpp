#include "Scenes/SceneRenderer.h"

Camera* sceneFrameRenderer::camptr;
WafelFrame* sceneFrameRenderer::rendererptr;

void sceneFrameRenderer::Begin()
{
    camptr = &camera;
    rendererptr = &Renderer;

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
    camptr = nullptr;
    rendererptr = nullptr;
    CryingMoon.reset();
}

void sceneFrameRenderer::Update()
{
    ProcessInput(glfwGetCurrentContext());
    projection = glm::perspective(glm::radians(70.0f), WindowOptions::windowSize.x / WindowOptions::windowSize.y, 0.1f, 100.0f);
    view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
}

void sceneFrameRenderer::Render()
{

    glBindFramebuffer(GL_FRAMEBUFFER, Renderer.FBO);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    CryingMoon->transform = glm::rotate(CryingMoon->transform, DeltaTime, glm::vec3(0.5f, 0.5f, 0.0f));

    CryingMoon->GetShader()->Use();
    CryingMoon->GetShader()->setMatrix4("model", glm::value_ptr(CryingMoon->transform));
    CryingMoon->GetShader()->setMatrix4("view", glm::value_ptr(view));
    CryingMoon->GetShader()->setMatrix4("projection", glm::value_ptr(projection));

    CryingMoon->Draw();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    FrameBufferShader.Use();
    glBindVertexArray(screenVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, Renderer.TEXTURE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
};

void sceneFrameRenderer::ProcessInput(GLFWwindow *window)
{

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
    {

        if (firstMouse)
        {
            lastX = MousePosX;
            lastY = MousePosY;
            firstMouse = false;
        }

        float xoffset = MousePosX - lastX;
        float yoffset = lastY - MousePosY;

        lastX = MousePosX;
        lastY = MousePosY;

        camera.ProcessMouseMovement(xoffset, yoffset);

        // glfwSetCursor(window, GLFW_POINTING_HAND_CURSOR);
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, DeltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, DeltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, DeltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, DeltaTime);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
        // Prevent snapping for the camera
        firstMouse = true;
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
};