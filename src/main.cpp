#include "main.h"
#include <iostream>
#include <fstream>
#include <vector>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

std::vector<Vertex> verts = {
    {{-0.5f,-0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
    {{ 0.5f,-0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}},
    {{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 0.2f}},
};

std::vector<unsigned int> indis = {
    0, 1, 3,
    1, 2, 3,
};

int main(void)
{
    StroopConfig::Setup();
    GLFWwindow *window;
    GLFWmonitor* monitor;
    WindowOptions options;
    GUIManager guimanager;

    NFD::Init();

    guimanager.AddLayout("menu", std::make_unique<MainMenuUI>(guimanager));
    guimanager.AddLayout("lvleditor", std::make_unique<LevelEditorUI>());

    auto cfg = StroopConfig::GetConfig();

    float WINDOW_WIDTH = cfg["WINDOW"]["WIDTH"].value_or<float>(1336);
    float WINDOW_HEIGHT = cfg["WINDOW"]["HEIGHT"].value_or<float>(768);
    int VSYNC = cfg["WINDOW"]["VSYNC"].value_or<int>(1);
    int DisplayWidth, DisplayHeight;

    options.WINDOWSIZE = {WINDOW_WIDTH, WINDOW_HEIGHT};
    options.WINDOWTITLE = "StroopWafel";

    
    if (!glfwInit()) return -1;

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* video = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

    window = glfwCreateWindow(static_cast<int>(options.WINDOWSIZE.x), static_cast<int>(options.WINDOWSIZE.y), options.WINDOWTITLE.c_str(), NULL, NULL);
    glfwSetWindowPos(window, static_cast<int>((video->width - options.WINDOWSIZE.x) / 2),static_cast<int>((video->height - options.WINDOWSIZE.y) / 2));

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);

    guimanager.SetLayout("menu");

    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, 0);
        //glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    }

    Shader shader{"default.vert", "default.frag"};
    Mesh mesh{verts, indis};

    glfwSwapInterval(VSYNC);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle &style = ImGui::GetStyle();
    StroopConfig::SetImGuiStyle(style);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, KeyboardCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.03f, 0.2f, 0.05f, 1.0f);
        
        guimanager.Update();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // RENDER START

        shader.Use();
        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        guimanager.Render();
        // RENDER END
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}