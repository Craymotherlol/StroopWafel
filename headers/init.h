#ifndef STROOPWAFEL_INITIALIZATION_H
#define STROOPWAFEL_INITIALIZATION_H

#include <toml++/toml.hpp>
#include <filesystem>
#include <string>
#include "window.h"

class StroopConfig {
    public:
        static toml::parse_result GetConfig();
        static void Setup();
        static void SetImGuiStyle(ImGuiStyle &style) noexcept;
};

#endif