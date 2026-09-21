#define STB_IMAGE_IMPLEMENTATION
#include "Helpers/LoadTexture.h"

using std::ios;

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromMemory(const void *data, size_t data_size, GLuint *out_texture, int *out_width, int *out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char *image_data = stbi_load_from_memory((const unsigned char *)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool LoadTextureFromFile(const char *file_name, GLuint *out_texture, int *out_width, int *out_height)
{
    std::fstream f;
    f.open(file_name, ios::binary | ios::in);

    if (!f.is_open())
    {
        std::cout << R"(Failed to open:" )" << file_name << R"( ")" << "\n";
        return false;
    };

    f.seekg(0, ios::end);
    std::streampos end = f.tellg();

    if (end == std::streampos(-1))
    {
        f.close();
        return false;
    }

    size_t file_size = static_cast<size_t>(end);
    f.seekg(0, ios::beg);

    void *file_data = IM_ALLOC(file_size);

    if (!file_data)
    {
        std::cout << R"(Texture has no raw data:" )" << file_name << R"( ")" << "\n";
        f.close();
        return false;
    }

    f.read(static_cast<char *>(file_data), static_cast<std::streamsize>(file_size));

    f.close();
    bool ret = LoadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}

ImVec2 ImageKeepRatio(GLuint* imagedata, int width, int height) {

    int texW, texH;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texW);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texH);

	float ratio = std::min(static_cast<float>(width) / texW, static_cast<float>(height) / texH);

	int display_w = texW * ratio;
	int display_h = texH * ratio;

    return ImVec2(display_w, display_h);
}