#include "init.h"
#include <iostream>
#include <filesystem>

bool configExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

toml::parse_result StroopConfig::GetConfig() {
	return toml::parse_file("config.toml");
}


void StroopConfig::Setup()
{
    // Don't think this is the best way to do it but /shrug
    std::fstream fs;

    constexpr auto source = R"(
        WIDTH = 1336
        HEIGHT = 768
        VSYNC = 1
    )";

	std::cout << "CURRENT DEBUGGING PATH: " << std::filesystem::current_path() << "\n";

    toml::table tbl = toml::parse(source);

    if (configExists("config.toml"))
    {
		toml::parse_result cfg;

		try {
        	cfg = GetConfig();

			if (cfg.contains("WINDOW")) {
				std::cout << "\033[35m" << "[SUCCESS] "  << "\033[0m" << "Config: Parsed file" << "\n";
			} else {
				throw 1;
			}
		} catch (int error) {
			std::cout << "\033[31m" << "[ERROR] "  << "\033[0m" << "Config: Failed to parse file" << "\n";
		}

        if (cfg.contains("[WINDOW]"))
        {
            toml::table tbl = *cfg["WINDOW"].as_table();

            if (tbl.empty())
            {
                cfg.insert_or_assign("WINDOW", tbl);
                return;
            }
        } 
        else {
            cfg.insert_or_assign("WINDOW", tbl);
        }

        return;
    }

    fs.open("config.toml", std::ios::out);
    fs.close();

    auto cfg = GetConfig();
    cfg.insert("WINDOW", tbl);

    fs.open("config.toml", std::ios::in | std::ios::out);
    fs << cfg << "\n\n";
    fs.close();
}

void StroopConfig::SetImGuiStyle(ImGuiStyle &style) noexcept
{
	auto cfg = GetConfig();
	if (!cfg.contains("STYLING"))
	{	
		toml::table TABLE;
		toml::table styletbl{
									 /* R     G    B    Alpha */  
		{"text", 			toml::array{255, 255, 255, 255}},
		{"textDisabled",	toml::array{150, 150, 150, 255}},
		{"windowBg", 		toml::array{212, 105, 37,  	90}},
	    {"windowBorder", 	toml::array{186, 138, 108, 200}},
	    {"windowTitlebar", 	toml::array{234, 157, 50,  180}},
		{"framebg", 		toml::array{145, 56,  21,  160}},
		{"framebgHovered", 	toml::array{160, 71,  36,  210}},
		{"framebgActive", 	toml::array{221, 87,  35,  230}},
		{"button", 			toml::array{255, 158, 52,  180}},
		{"buttonActive", 	toml::array{204, 136, 40,  140}},
		{"buttonHovered", 	toml::array{255, 171, 51,  190}}};
		
		TABLE.insert("STYLING", styletbl);
		
		std::fstream fs;
		
		fs.open("config.toml", std::ios::app);

		fs << TABLE << "\n\n";
		fs.close();

		cfg.clear();

		// Re-get it again to prevent any exceptions.
		cfg = GetConfig();
	}

	toml::table tbl = *cfg["STYLING"].as_table();

	
	// Super bloated as shit.
	// add also fallbacks if there's no color set in the config file or cannot be read.

	style.WindowRounding = 1.5;
	style.GrabRounding = 1;
	style.GrabMinSize = 20;
	style.FrameRounding = 3;

	// Font
	//ImColor(tbl["text"][0].value_or(255), tbl["text"][1].value_or(255), tbl["text"][2].value_or(255), tbl["text"][3].value_or(0.0));
	style.Colors[ImGuiCol_Text] = ImColor(tbl["text"][0].value_or(255), tbl["text"][1].value_or(255), tbl["text"][2].value_or(255), tbl["text"][3].value_or(255));
	style.Colors[ImGuiCol_TextDisabled] = ImColor(tbl["textDisabled"][0].value_or(150), tbl["textDisabled"][1].value_or(150), tbl["textDisabled"][2].value_or(150), tbl["textDisabled"][3].value_or(255));
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);

	// Window Frame
	style.Colors[ImGuiCol_WindowBg] = ImColor(tbl["windowBg"][0].value_or(212), tbl["windowBg"][1].value_or(105), tbl["windowBg"][2].value_or(37), tbl["windowBg"][3].value_or(200));
	style.Colors[ImGuiCol_Border] = ImColor(tbl["windowBorder"][0].value_or(186), tbl["windowBorder"][1].value_or(138), tbl["windowBorder"][2].value_or(108), tbl["windowBorder"][3].value_or(200));
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	
	style.Colors[ImGuiCol_FrameBg] = ImColor(tbl["framebg"][0].value_or(145), tbl["framebg"][1].value_or(56), tbl["framebg"][2].value_or(21), tbl["framebg"][3].value_or(160));	
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(tbl["framebgHovered"][0].value_or(160), tbl["framebgHovered"][1].value_or(71), tbl["framebgHovered"][2].value_or(36), tbl["framebgHovered"][3].value_or(210));
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(tbl["framebgActive"][0].value_or(221), tbl["framebgActive"][1].value_or(87), tbl["framebgActive"][2].value_or(35), tbl["framebgActive"][3].value_or(230));

	style.Colors[ImGuiCol_TitleBg] = ImColor(tbl["windowTitlebar"][0].value_or(234), tbl["windowTitlebar"][1].value_or(157), tbl["windowTitlebar"][2].value_or(50), tbl["windowTitlebar"][3].value_or(180));
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.27f);

	style.Colors[ImGuiCol_MenuBarBg] = ImColor(tbl["windowBg"][0].value_or(212), tbl["windowBg"][1].value_or(105), tbl["windowBg"][2].value_or(37), tbl["windowBg"][3].value_or(255));

	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);

	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 0.68f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.36f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);

	// Buttons
	style.Colors[ImGuiCol_Button] = ImColor(tbl["button"][0].value_or(243), tbl["button"][1].value_or(193), tbl["button"][2].value_or(96), tbl["button"][3].value_or(180));
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(tbl["buttonHovered"][0].value_or(204), tbl["buttonHovered"][1].value_or(169), tbl["buttonHovered"][2].value_or(80), tbl["buttonHovered"][3].value_or(190));
	style.Colors[ImGuiCol_ButtonActive] = ImColor(tbl["buttonActive"][0].value_or(242), tbl["buttonActive"][1].value_or(200), tbl["buttonActive"][2].value_or(98), tbl["buttonActive"][3].value_or(100));

	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.33f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.42f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);

	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);

	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
};