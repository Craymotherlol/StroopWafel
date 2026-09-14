#include "globals.h"
#include "main.h"
#include <iostream>
#include <fstream>

int CURRENT_FRAME = 0;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


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

    window = glfwCreateWindow(options.WINDOWSIZE.x, options.WINDOWSIZE.y, options.WINDOWTITLE.c_str(), NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSYNC);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGuiStyle &style = ImGui::GetStyle();
    StroopConfig::SetImGuiStyle(style);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // RENDER START
        FramesGUI::MainMenu(window);

        // RENDER END
        ImGui::Render();

        glClearColor(0.03f, 0.2f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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