#include "globals.h"
#include "main.h"
#include <iostream>
#include <fstream>

const bool DEBUG = true;
int CURRENT_FRAME = 0;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};


#define glCheckError() glCheckError_(__FILE__, __LINE__)

int main(void)
{

    StroopConfig::Setup();
    GLFWwindow *window;
    WindowOptions options;

    auto cfg = StroopConfig::GetConfig();

    float WINDOW_WIDTH = cfg["WINDOW"]["WIDTH"].value_or<float>(1336);
    float WINDOW_HEIGHT = cfg["WINDOW"]["HEIGHT"].value_or<float>(768);
    int VSYNC = cfg["WINDOW"]["VSYNC"].value_or<int>(1);

    options.WINDOWSIZE = {WINDOW_WIDTH, WINDOW_HEIGHT};
    options.WINDOWTITLE = "StroopWafel";

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, DEBUG);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    window = glfwCreateWindow(options.WINDOWSIZE.x, options.WINDOWSIZE.y, options.WINDOWTITLE.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);

    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, 0);
        //glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }

    glfwSwapInterval(VSYNC);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle &style = ImGui::GetStyle();
    StroopConfig::SetImGuiStyle(style);

    GLObject rectangle{
        "RECTANGLETEST",
        Shader("default.vert", "default.frag"),
        Mesh(vertices, sizeof(vertices), indices, sizeof(indices))};
    // Vertexes
    rectangle.mesh.vao.LinkVBO(rectangle.mesh.vbo, 0, 0);
    // Color
    rectangle.mesh.vao.LinkVBO(rectangle.mesh.vbo, 1, 3 * sizeof(float));

    rectangle.UnbindAll();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.03f, 0.2f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // RENDER START
        FramesGUI::MainMenu(window);

        rectangle.shaders.Activate();
        rectangle.mesh.vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // RENDER END
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    rectangle.mesh.vao.Delete();
    rectangle.mesh.vbo.Delete();
    rectangle.mesh.ebo.Delete();
    rectangle.shaders.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}