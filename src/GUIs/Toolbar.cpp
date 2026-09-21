#include "GUIs/Toolbar.h"

void ShowToolbar() {
    bool exit_modal = false;
	
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File")) {
		
		if (ImGui::MenuItem("New Level File..")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem("Open Level File..")) {
			nfdu8char_t *outPath;
			nfdopendialogu8args_t args = {0};
			nfdu8filteritem_t filters[2] = { { "Wafel Resource Data", "wrd" }, { "CettaLyke Level Layout", "cll" } };
			args.filterList = filters;
			args.filterCount = 2;
			
			nfdresult_t RESULT_FILE_NFD = NFD_OpenDialogU8_With(&outPath, &args);
		}
		
		if (ImGui::MenuItem("Save")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem("Save to..")) {
			exit_modal = true;
		}
		
		if (ImGui::MenuItem("Exit")) {
			exit_modal = true;
		}
			
		ImGui::EndMenu();
	}
	
	if (ImGui::BeginMenu("Run")) {
		
		if (ImGui::MenuItem("Playtest")) {
			exit_modal = true;
		}
		
			
		ImGui::EndMenu();
	}
	
	if (ImGui::BeginMenu("View")) {
		ImGui::PopStyleColor();
		
		if (ImGui::MenuItem("Style Editor")) {
			std::cout << "hi";
		}
		
			
		ImGui::EndMenu();
	}
	
	ImGui::EndMainMenuBar();
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