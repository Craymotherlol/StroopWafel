#include "lib/stb_image.h"
#include "Window.h"
#include <fstream>
#include <filesystem>

bool LoadTextureFromMemory(const void *data, size_t data_size, GLuint *out_texture, int *out_width, int *out_height);

bool LoadTextureFromFile(const char *file_name, GLuint *out_texture, int *out_width, int *out_height);

GLuint SetTextureFromFile(std::string file_name);

ImVec2 ImageKeepRatio(GLuint* imagedata, int width, int height);