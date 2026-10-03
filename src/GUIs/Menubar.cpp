#include "GUIs/Menubar.h"

void MenuBarUI() {
    bool exit_modal = false;
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::BeginMainMenuBar();
	//ImGui::PushFont(fontIcons);
	if (ImGui::BeginMenu("File")) {

		if (ImGui::MenuItem(ICON_FA_FILE " New Level File..", "Ctrl+N")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open Level File..", R"(Ctrl+O)")) {
			nfdu8char_t *outPath;
			nfdopendialogu8args_t args = {0};
			nfdu8filteritem_t filters[2] = { { "Wafel Resource Data", "wrd" }, { "CettaLyke Level Layout", "cll" } };
			args.filterList = filters;
			args.filterCount = 2;
			
			nfdresult_t RESULT_FILE_NFD = NFD_OpenDialogU8_With(&outPath, &args);
		}
		
		if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save", "Ctrl+S")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem("Save to..", "Ctrl+Alt+S")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem("Exit", "Alt+F4")) {
			exit_modal = true;
		}
		ImGui::EndMenu();
	}
	
	if (ImGui::BeginMenu("Play")) {
		
		if (ImGui::MenuItem(ICON_FA_PLAY " Run", "F5")) {
			exit_modal = true;
		}
		
			
		ImGui::EndMenu();
	}
	
	if (ImGui::BeginMenu("View")) {
		
		if (ImGui::MenuItem("Style Editor")) {
			ImGui::ShowStyleEditor();
		}
		
		ImGui::EndMenu();
	}

	//ImGui::PopFont();
	ImGui::EndMainMenuBar();
	ImGui::PopStyleVar();
};

	
	// var viewport = ImGui.GetMainViewport();
	// var toolbarSize = 36;
	// frameHeight = ImGui.GetFrameHeight() + toolbarSize;
	// ImGui.PushStyleColor(ImGuiCol.WindowBg, #3B2E18, 1);
	
	// ImGui.SetNextWindowPos(0, 0 + ImGui.GetFrameHeight());
	// ImGui.SetNextWindowSize(window_get_width(), toolbarSize);
	// //ImGui.SetNextWindowViewport();

	
	// function seperateVertical() {
	// 	ImGui.SameLine();
	// 	var list = ImGui.GetWindowDrawList();
		
	// 	var _x = ImGui.GetCursorPosX()
	
	// 	var y1 = ImGui.GetFrameHeight() + 5
	// 	var y2 = ImGui.GetFrameHeight() + 32
		
	// 	ImGui.DrawListAddLine(list, _x, y1, _x, y2, #888888);
	// 	ImGui.Dummy(2, ImGui.GetFrameHeight());
	// }
	
	// var toolflag = 
	// 	ImGuiWindowFlags.NoDocking 
	// 	| ImGuiWindowFlags.NoTitleBar 
	// 	| ImGuiWindowFlags.NoResize 
	// 	| ImGuiWindowFlags.NoMove 
	// 	| ImGuiWindowFlags.NoScrollbar 
	// 	| ImGuiWindowFlags.NoSavedSettings
	// 	;
		
		
	// ImGui.PushStyleVar(ImGuiStyleVar.WindowBorderSize, 0);
	// ImGui.Begin("TOOLBAR", undefined, toolflag);
	// ImGui.PopStyleVar();
	// ImGui.PopStyleColor();
		 
	// var toolbarHeight = ImGui.GetWindowHeight();
	// ImGui.SetCursorPosY(3)
	
	// ImGui.PushStyleVar(ImGuiStyleVar.FrameRounding, 3);
	// ImGui.PushStyleColor(ImGuiCol.Button,#a16540, 0.9)
	// ImGui.PushStyleColor(ImGuiCol.ButtonHovered,#b27651, 0.9)
	// ImGui.PushStyleColor(ImGuiCol.ButtonActive,#7F432A, 0.9)
	
	// #region SELECT
	// if (CURRENT_MODE = MODES.SELECT) { ImGui.PushStyleColor(ImGuiCol.Button,#c3966e, 1)}
		
	// if (ImGui.ImageButton("T_Select",t_icos,0,c_white,1,c_white,0,25, 25)) {
	// 	audio_play_sound(uiSelect, 0, false);
	// 	CURRENT_MODE = MODES.SELECT
	// }
	
	// if (CURRENT_MODE = MODES.SELECT) {ImGui.PopStyleColor(1);}
	// #endregion
	
	// ImGui.SameLine();
	
	// #region DRAW
	// if (CURRENT_MODE = MODES.DRAW) {ImGui.PushStyleColor(ImGuiCol.Button,#c3966e, 1)}
	
	// if (ImGui.ImageButton("T_Draw",t_icos,1,c_white,1,c_white,0,25, 25)) {
	// 	audio_play_sound(uiSelect, 0, false);
	// 	CURRENT_MODE = MODES.DRAW
	// }
	
	// if (CURRENT_MODE = MODES.DRAW) {ImGui.PopStyleColor(1);}
	
	// #endregion
	
	// ImGui.SameLine();
	
	// #region ERASE
	
	// if (CURRENT_MODE = MODES.ERASE) {ImGui.PushStyleColor(ImGuiCol.Button,#c3966e, 1)}
	
	// if (ImGui.ImageButton("T_Eraser",t_icos,2,c_white,1,c_white,0,25, 25)) {
	// 	audio_play_sound(uiSelect, 0, false);
	// 	CURRENT_MODE = MODES.ERASE
	// }
	
	// if (CURRENT_MODE = MODES.ERASE) {ImGui.PopStyleColor(1);}
	// #endregion
	
	// seperateVertical();
	
	// ImGui.PopStyleVar();
	// ImGui.PopStyleColor();
	
	// ImGui.End();