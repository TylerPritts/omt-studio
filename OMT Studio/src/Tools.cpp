#include "dependencies.h"

namespace ImField
{
    static void CustomButton(const char* name, float spacing, float window_visible_x2);
    static void ShowToolWindow(bool* p_open = NULL)
    {
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!");


        // Demonstrate the various window flags. Typically you would just use the default!
        static bool no_titlebar = false;
        static bool no_scrollbar = false;
        static bool no_menu = true;
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = false;
        static bool no_close = false;
        static bool no_nav = false;
        static bool no_background = false;
        static bool no_bring_to_front = false;
        static bool no_docking = false;
        static bool unsaved_document = false;

        ImGuiWindowFlags window_flags = 0;
        if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
        if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
        if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

        // We specify a default position/size in case there's no data in the .ini file.
        // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

        // Main body of the Demo window starts here.
        ImGui::Begin("Tool", p_open, window_flags);


        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

        CustomButton("Box1", spacing, window_visible_x2);
        CustomButton("Box2", spacing, window_visible_x2);
        CustomButton("Box3", spacing, window_visible_x2);
        CustomButton("Box4", spacing, window_visible_x2);
        CustomButton("Box5", spacing, window_visible_x2);
        CustomButton("Box6", spacing, window_visible_x2);
        CustomButton("Box7", spacing, window_visible_x2);
        CustomButton("Box8", spacing, window_visible_x2);
        CustomButton("Box9", spacing, window_visible_x2);
        CustomButton("Box10", spacing, window_visible_x2);
        CustomButton("Box11", spacing, window_visible_x2);
        CustomButton("Box12", spacing, window_visible_x2);
        
            

        

        ImGui::End();
    }
    static void CustomButton(const char* name, float spacing, float window_visible_x2)
    {
        ImGui::Button(name, ImVec2(40, 40));
        float last_button_x2 = ImGui::GetItemRectMax().x;
        float next_button_x2 = last_button_x2 + spacing + ImVec2(40, 40).x; // Expected position if next button was on same line
        if (next_button_x2 < window_visible_x2) {
            ImGui::SameLine();
        }
    }
}
