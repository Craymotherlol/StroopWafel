#include "main.h"
#include "Debug.h"

GLfloat DeltaTime = 0.0f;
GLuint FallbackTexture;
ImFont* fontIcons = nullptr;

GUIManager guimanager;
SceneManager scenemanager;

extern "C" 
{
  __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplayFramebufferScale = ImVec2(1.0f,1.0f);
    io.DisplaySize = ImVec2(width,height);
}


int main(void)
{
    StroopConfig::Setup();
    GLFWwindow *window;
    GLFWmonitor* monitor;
    WindowOptions options;

    NFD::Init();

    guimanager.Add("menu", std::make_unique<MainMenuUI>());
    guimanager.Add("lvleditor", std::make_unique<LevelEditorUI>());

    auto cfg = StroopConfig::GetConfig();

    float WINDOW_WIDTH = cfg["WINDOW"]["WIDTH"].value_or<float>(1336);
    float WINDOW_HEIGHT = cfg["WINDOW"]["HEIGHT"].value_or<float>(768);
    int VSYNC = cfg["WINDOW"]["VSYNC"].value_or<int>(1);

    options.WINDOWSIZE = {WINDOW_WIDTH, WINDOW_HEIGHT};
    options.WINDOWTITLE = "StroopWafel";

    
    if (!glfwInit()) return -1;

    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* video = glfwGetVideoMode(monitor);

    #if(DEBUG)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    #else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    #endif


    window = glfwCreateWindow(static_cast<int>(options.WINDOWSIZE.x), static_cast<int>(options.WINDOWSIZE.y), options.WINDOWTITLE.c_str(), nullptr, nullptr);
    glfwSetWindowPos(window, static_cast<int>((video->width - options.WINDOWSIZE.x) / 2),static_cast<int>((video->height - options.WINDOWSIZE.y) / 2));

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);

    createFallbackTexture();

    scenemanager.Add("menu", std::make_unique<MainMenuScene>());
    scenemanager.Add("scenerenderer", std::make_unique<sceneFrameRenderer>());

    #if(DEBUG)
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(glDebugOutput, 0);
            glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
        }
    #endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 

    ImGuiStyle &style = ImGui::GetStyle();
    StroopConfig::SetImGuiStyle(style);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    
    //io.Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", 13.0f);

    ImFontConfig font_config;
    font_config.SizePixels = 13.0f;

    io.Fonts->AddFontDefaultVector(&font_config);
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;


    icons_config.GlyphOffset.y = 1.5f; 
    static const ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    io.Fonts->AddFontFromFileTTF("res/fonts/fa-solid-900.ttf", 13.0f, &icons_config, icon_ranges);

    scenemanager.Set("menu");
    guimanager.Set("menu");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, KeyboardCallback);
    glfwSwapInterval(VSYNC);

    double lastFrame = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        double currentFrame = glfwGetTime();
        DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        guimanager.Update();
        scenemanager.Update();

        glClearColor(0.03f, 0.2f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // RENDER START vv

        guimanager.Render();
        scenemanager.Render();

        
        ImGui::Render();
        // RENDER END ^^

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}