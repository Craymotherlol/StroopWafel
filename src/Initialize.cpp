#include "Init.h"
#include <iostream>
#include <filesystem>
#include "StroopConfig.h"

const std::string RESOURCES_PATH = "res/";
const std::string SHADERS_PATH = RESOURCES_PATH + "/shaders";
const std::string FONTS_PATH = RESOURCES_PATH + "/fonts";

// Default parameters
ImVec2 WindowOptions::windowSize = ImVec2(1440,900);

std::string programName = "StroopWafel ";
std::string WindowOptions::windowTitle = programName + STROOPWAFEL_VERSION;

int WindowOptions::vSync = 1;


extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


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
        WIDTH = 1440
        HEIGHT = 900
        VSYNC = 1
    )";

    toml::table tbl = toml::parse(source);

	// bllah blah
    if (configExists("config.toml"))
    {
		toml::parse_result cfg;

		try {
        	cfg = GetConfig();

			if (cfg.contains("WINDOW")) {
				std::cout << "\033[35m" << "[SUCCESS] "  << "\033[0m" << "Config: Parsed file" << "\n";
			} else {
				throw 001;
			}
		} catch (int error) {
			std::cout << "\033[31m" << "[ERROR]" << error << "\033[0m" << "Config: Failed to parse file" << "\n";
		}

        if (cfg.contains("[WINDOW]"))
        {
            tbl = *cfg["WINDOW"].as_table();

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

	StroopConfig s;

	s.SetVariables();
}

void StroopConfig::SetVariables() noexcept
 {
	auto cfg = GetConfig();

	// I love 3:2 :))
	WindowOptions::windowSize = ImVec2(cfg["WINDOW"]["WIDTH"].value_or<float>(1440), cfg["WINDOW"]["HEIGHT"].value_or<float>(900));
	WindowOptions::vSync = cfg["WINDOW"]["VSYNC"].value_or<int>(1);
}

void StroopConfig::SetImGuiStyle(ImGuiStyle &style) noexcept
{
	auto cfg = GetConfig();
	if (!cfg.contains("STYLING"))
	{	
		toml::table TABLE;
		toml::table styletbl{
									 /* R     G    B    Alpha */  
		{"text", 				toml::array{255, 255, 255, 255}},
		{"textDisabled",		toml::array{150, 150, 150, 255}},
		{"windowBg", 			toml::array{116, 36,   8,  	87}},
	    {"windowBorder", 		toml::array{141, 99,  58,   86}},
	    {"TitleBg", 			toml::array{196, 90,  29,  180}},
	    {"TitleActiveBg",		toml::array{220, 109, 12,  210}},
	    {"TitleCollapsedBg",	toml::array{204, 137, 36,  170}},
		{"framebg", 			toml::array{145, 56,  21,  160}},
		{"framebgHovered", 		toml::array{160, 71,  36,  210}},
		{"framebgActive", 		toml::array{221, 87,  35,  230}},
		{"button", 				toml::array{178, 135, 71,  210}},
		{"buttonActive", 		toml::array{158, 115, 51,  243}},
		{"buttonHovered", 		toml::array{245, 189, 93,  190}},
		{"Tab", 				toml::array{178, 135, 71,  	60}},
		{"TabActive", 			toml::array{225, 167, 87,  180}},
		{"TabHovered", 			toml::array{245, 189, 93,  190}},
	    {"TabUnfocused", 		toml::array{255, 171, 51,  190}},
		{"TabUnfocusedActive", 	toml::array{255, 171, 51,  190}},
		{"Header", 				toml::array{255, 171, 51,  150}},
		{"HeaderActive", 		toml::array{255, 178, 71,  175}},
		{"HeaderHovered", 		toml::array{245, 189, 93,  190}},
		{"Checkmark", 			toml::array{255, 255, 255, 255}},
		{"CheckmarkSelected", 	toml::array{240, 133, 52,  144}},
		{"ScrollbarGrabActive", toml::array{224, 137, 40,  255}},
		{"Slidebar", 			toml::array{224, 137, 40,  255}},
		{"SlidebarActive", 		toml::array{234, 157, 50,  255}},
		{"MenuBarBg", 			toml::array{72, 29,  14,  255}},
	
	};
		
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

	style.WindowRounding = 3;
	style.GrabRounding = 1;
	style.GrabMinSize = 20;
	style.FrameRounding = 3;
	style.DockingSeparatorSize = 1;
	
	// Font
	//ImColor(tbl["text"][0].value_or(255), tbl["text"][1].value_or(255), tbl["text"][2].value_or(255), tbl["text"][3].value_or(0.0));
	style.Colors[ImGuiCol_Text] = ImColor(tbl["text"][0].value_or(255), tbl["text"][1].value_or(255), tbl["text"][2].value_or(255), tbl["text"][3].value_or(255));
	style.Colors[ImGuiCol_TextDisabled] = ImColor(tbl["textDisabled"][0].value_or(150), tbl["textDisabled"][1].value_or(150), tbl["textDisabled"][2].value_or(150), tbl["textDisabled"][3].value_or(255));
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 1.00f, 1.00f, 0.22f);

	// Tabs
	style.Colors[ImGuiCol_Tab] = ImColor(tbl["Tab"][0].value_or(178), tbl["Tab"][1].value_or(135), tbl["Tab"][2].value_or(71), tbl["Tab"][3].value_or(60));
	style.Colors[ImGuiCol_TabActive] = ImColor(tbl["TabActive"][0].value_or(225), tbl["TabActive"][1].value_or(167), tbl["TabActive"][2].value_or(87), tbl["TabActive"][3].value_or(180));
	style.Colors[ImGuiCol_TabHovered] = ImColor(tbl["TabHovered"][0].value_or(245), tbl["TabHovered"][1].value_or(189), tbl["TabHovered"][2].value_or(93), tbl["TabHovered"][3].value_or(190));
	style.Colors[ImGuiCol_TabUnfocused] = ImColor(tbl["TabUnfocused"][0].value_or(255), tbl["TabUnfocused"][1].value_or(171), tbl["TabUnfocused"][2].value_or(51), tbl["TabUnfocused"][3].value_or(190));
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImColor(tbl["TabUnfocusedActive"][0].value_or(255), tbl["TabUnfocusedActive"][1].value_or(171), tbl["TabUnfocusedActive"][2].value_or(51), tbl["TabUnfocusedActive"][3].value_or(190));

	// Window Frame
	style.Colors[ImGuiCol_WindowBg] = ImColor(tbl["windowBg"][0].value_or(212), tbl["windowBg"][1].value_or(105), tbl["windowBg"][2].value_or(37), tbl["windowBg"][3].value_or(200));
	style.Colors[ImGuiCol_Border] = ImColor(tbl["windowBorder"][0].value_or(186), tbl["windowBorder"][1].value_or(138), tbl["windowBorder"][2].value_or(108), tbl["windowBorder"][3].value_or(200));
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	
	style.Colors[ImGuiCol_FrameBg] = ImColor(tbl["framebg"][0].value_or(145), tbl["framebg"][1].value_or(56), tbl["framebg"][2].value_or(21), tbl["framebg"][3].value_or(160));	
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(tbl["framebgHovered"][0].value_or(160), tbl["framebgHovered"][1].value_or(71), tbl["framebgHovered"][2].value_or(36), tbl["framebgHovered"][3].value_or(210));
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(tbl["framebgActive"][0].value_or(221), tbl["framebgActive"][1].value_or(87), tbl["framebgActive"][2].value_or(35), tbl["framebgActive"][3].value_or(230));

	style.Colors[ImGuiCol_TitleBg] = ImColor(tbl["TitleBg"][0].value_or(234), tbl["TitleBg"][1].value_or(157), tbl["TitleBg"][2].value_or(50), tbl["TitleBg"][3].value_or(180));
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(tbl["TitleCollapsedBg"][0].value_or(204), tbl["TitleCollapsedBg"][1].value_or(137), tbl["TitleCollapsedBg"][2].value_or(36), tbl["TitleCollapsedBg"][3].value_or(170));
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(tbl["TitleActiveBg"][0].value_or(244), tbl["TitleActiveBg"][1].value_or(167), tbl["TitleActiveBg"][2].value_or(60), tbl["TitleActiveBg"][3].value_or(210));

	style.Colors[ImGuiCol_MenuBarBg] = ImColor(tbl["MenuBarBg"][0].value_or(212), tbl["MenuBarBg"][1].value_or(105), tbl["MenuBarBg"][2].value_or(37), tbl["MenuBarBg"][3].value_or(255));

	//style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.22f, 0.29f, 0.30f, 0.71f);
	//style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 1.00f, 0.44f);
	//style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);

	style.Colors[ImGuiCol_CheckMark] = 	ImColor(tbl["Checkmark"][0].value_or(255), tbl["Checkmark"][1].value_or(255), tbl["Checkmark"][2].value_or(255), tbl["Checkmark"][3].value_or(255));
	style.Colors[ImGuiCol_CheckboxSelectedBg] = ImColor(tbl["CheckmarkSelected"][0].value_or(240), tbl["CheckmarkSelected"][1].value_or(133), tbl["CheckmarkSelected"][2].value_or(52), tbl["CheckmarkSelected"][3].value_or(144));

	style.Colors[ImGuiCol_ScrollbarGrabActive] =  ImColor(tbl["ScrollbarGrabActive"][0].value_or(224), tbl["ScrollbarGrabActive"][1].value_or(137), tbl["ScrollbarGrabActive"][2].value_or(40), tbl["ScrollbarGrabActive"][3].value_or(255));
	style.Colors[ImGuiCol_SliderGrab] = ImColor(tbl["Slidebar"][0].value_or(224), tbl["Slidebar"][1].value_or(137), tbl["Slidebar"][2].value_or(40), tbl["Slidebar"][3].value_or(255));
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(tbl["SlidebarActive"][0].value_or(234), tbl["SlidebarActive"][1].value_or(157), tbl["SlidebarActive"][2].value_or(50), tbl["SlidebarActive"][3].value_or(255));

	// Buttons
	style.Colors[ImGuiCol_Button] = ImColor(tbl["button"][0].value_or(243), tbl["button"][1].value_or(193), tbl["button"][2].value_or(96), tbl["button"][3].value_or(180));
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(tbl["buttonHovered"][0].value_or(204), tbl["buttonHovered"][1].value_or(169), tbl["buttonHovered"][2].value_or(80), tbl["buttonHovered"][3].value_or(190));
	style.Colors[ImGuiCol_ButtonActive] = ImColor(tbl["buttonActive"][0].value_or(242), tbl["buttonActive"][1].value_or(200), tbl["buttonActive"][2].value_or(98), tbl["buttonActive"][3].value_or(100));

	style.Colors[ImGuiCol_Header] = ImColor(tbl["Header"][0].value_or(255), tbl["Header"][1].value_or(171), tbl["Header"][2].value_or(51), tbl["Header"][3].value_or(150));
	style.Colors[ImGuiCol_HeaderHovered] = 	ImColor(tbl["HeaderActive"][0].value_or(255), tbl["HeaderActive"][1].value_or(178), tbl["HeaderActive"][2].value_or(71), tbl["HeaderActive"][3].value_or(175));
	style.Colors[ImGuiCol_HeaderActive] = ImColor(tbl["HeaderHovered"][0].value_or(245), tbl["HeaderHovered"][1].value_or(189), tbl["HeaderHovered"][2].value_or(93), tbl["HeaderHovered"][3].value_or(190));

	//style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.54f);
	//style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.74f);
	//style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);

	//style.Colors[ImGuiCol_PlotLines] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	//style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	//style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	//style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
};