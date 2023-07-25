#include "Dependencies.h"




namespace ImField 
{
    static void ShowFieldWindow(bool* p_open = NULL)
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
        ImGui::Begin("Field Plotter", p_open, window_flags);


        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

        
        ImGui::BulletText("Below we are displaying the font texture, which is the only texture we have\naccess to in this demo.");
        ImGui::BulletText("Use the 'ImTextureID' type as storage to pass pointers or identifiers to your\nown texture data.");
        ImGui::BulletText("See ImGui Wiki page 'Image Loading and Displaying Examples'.");
        static ImVec2 bmin(0, 0);
        static ImVec2 bmax(1, 1);
        static ImVec2 uv0(0, 0);
        static ImVec2 uv1(1, 1);
        static ImVec4 tint(1, 1, 1, 1);
        ImGui::SliderFloat2("Min", &bmin.x, -2, 2, "%.1f");
        ImGui::SliderFloat2("Max", &bmax.x, -2, 2, "%.1f");
        ImGui::SliderFloat2("UV0", &uv0.x, -2, 2, "%.1f");
        ImGui::SliderFloat2("UV1", &uv1.x, -2, 2, "%.1f");
        ImGui::ColorEdit4("Tint", &tint.x);
        if (ImPlot::BeginPlot("##image")) {
            ImPlot::PlotImage("my image", ImGui::GetIO().Fonts->TexID, bmin, bmax, uv0, uv1, tint);
            ImPlot::EndPlot();
        }

        static float mk_size = ImPlot::GetStyle().MarkerSize;
        static float mk_weight = ImPlot::GetStyle().MarkerWeight;
        ImGui::DragFloat("Marker Size", &mk_size, 0.1f, 2.0f, 10.0f, "%.2f px");
        ImGui::DragFloat("Marker Weight", &mk_weight, 0.05f, 0.5f, 3.0f, "%.2f px");

        if (ImPlot::BeginPlot("##MarkerStyles", ImVec2(-1, 0), ImPlotFlags_CanvasOnly)) {

            ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
            ImPlot::SetupAxesLimits(0, 10, 0, 12);

            ImS8 xs[2] = { 1,4 };
            ImS8 ys[2] = { 10,11 };

            // filled markers
            for (int m = 0; m < ImPlotMarker_COUNT; ++m) {
                ImGui::PushID(m);
                ImPlot::SetNextMarkerStyle(m, mk_size, IMPLOT_AUTO_COL, mk_weight);
                ImPlot::PlotLine("##Filled", xs, ys, 2);
                ImGui::PopID();
                ys[0]--; ys[1]--;
            }
            xs[0] = 6; xs[1] = 9; ys[0] = 10; ys[1] = 11;
            // open markers
            for (int m = 0; m < ImPlotMarker_COUNT; ++m) {
                ImGui::PushID(m);
                ImPlot::SetNextMarkerStyle(m, mk_size, ImVec4(0, 0, 0, 0), mk_weight);
                ImPlot::PlotLine("##Open", xs, ys, 2);
                ImGui::PopID();
                ys[0]--; ys[1]--;
            }

            ImPlot::PlotText("Filled Markers", 2.5f, 6.0f);
            ImPlot::PlotText("Open Markers", 7.5f, 6.0f);

            ImPlot::PushStyleColor(ImPlotCol_InlayText, ImVec4(1, 0, 1, 1));
            ImPlot::PlotText("Vertical Text", 5.0f, 6.0f, ImVec2(0, 0), ImPlotTextFlags_Vertical);
            ImPlot::PopStyleColor();

            ImPlot::EndPlot();
        }

        ImGui::BulletText("Equal constraint applies to axis pairs (e.g ImAxis_X1/Y1, ImAxis_X2/Y2)");
        
        ImPlotAxisFlags ax_flags = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoTickMarks;

        float xs2[] = { -1,0,1,0,-1 };
        float ys2[] = { 0,1,0,-1,0 };


        int yticks[46];
        for (int dist = 0; dist <= 44; dist++) {

            yticks[dist] = { -88 + (dist * 1) };
        }
        double yticks2[46];


        for (int conv = 0; conv <= 44; conv++) {
            yticks2[conv] = yticks[conv];
        }


        static float constraints[4] = { 88,46,16,176 };




        if (ImPlot::BeginPlot("##EqualAxes", ImVec2(-1, 0), (ImPlotFlags_Equal,ImPlotFlags_CanvasOnly) )) {
            ImPlot::SetupAxes(nullptr, nullptr, ax_flags, ax_flags);
            
            //ImPlot::SetupAxisScale(ImAxis_X1,0,0,0);

            ImPlot::SetupAxesLimits(-88, 88, -46, 46);

            // Max Grid Size
            ImPlot::SetupAxisLimitsConstraints(ImAxis_X1, -(constraints[0]), constraints[0]);
            ImPlot::SetupAxisLimitsConstraints(ImAxis_Y1, -(constraints[1]), constraints[1]);

            // Max Zoom
            ImPlot::SetupAxisZoomConstraints(ImAxis_X1, 17.6, 176);
            ImPlot::SetupAxisZoomConstraints(ImAxis_Y1, 9.2, 92);

            ImPlot::SetupAxisTicks(ImAxis_X1, yticks2, 44);
            ImPlot::SetupAxisTicks(ImAxis_Y1, yticks2, 44);
            

            ImPlot::PlotLine("Diamond", xs2, ys2, 5);
            ImPlot::EndPlot();
        }
        
        ImGui::BulletText("Click and drag each point.");
        static ImPlotDragToolFlags flags = ImPlotDragToolFlags_None;
        ImGui::CheckboxFlags("NoCursors", (unsigned int*)&flags, ImPlotDragToolFlags_NoCursors); ImGui::SameLine();
        ImGui::CheckboxFlags("NoFit", (unsigned int*)&flags, ImPlotDragToolFlags_NoFit); ImGui::SameLine();
        ImGui::CheckboxFlags("NoInput", (unsigned int*)&flags, ImPlotDragToolFlags_NoInputs);

        


        if (ImPlot::BeginPlot("##Bezier", ImVec2(-1, 0), ImPlotFlags_CanvasOnly)) {
            ImPlot::SetupAxes(nullptr, nullptr, ax_flags, ax_flags);
            ImPlot::SetupAxesLimits(0, 1, 0, 1);
            static ImPlotPoint P[] = { ImPlotPoint(.05f,.05f), ImPlotPoint(0.2,0.4),  ImPlotPoint(0.8,0.6),  ImPlotPoint(.95f,.95f) };

            ImPlot::DragPoint(0, &P[0].x, &P[0].y, ImVec4(0, 0.9f, 0, 1), 4, flags);
            ImPlot::DragPoint(1, &P[1].x, &P[1].y, ImVec4(1, 0.5f, 1, 1), 4, flags);
            ImPlot::DragPoint(2, &P[2].x, &P[2].y, ImVec4(0, 0.5f, 1, 1), 4, flags);
            ImPlot::DragPoint(3, &P[3].x, &P[3].y, ImVec4(0, 0.9f, 0, 1), 4, flags);

            static ImPlotPoint B[100];
            for (int i = 0; i < 100; ++i) {
                double t = i / 99.0;
                double u = 1 - t;
                double w1 = u * u * u;
                double w2 = 3 * u * u * t;
                double w3 = 3 * u * t * t;
                double w4 = t * t * t;
                B[i] = ImPlotPoint(w1 * P[0].x + w2 * P[1].x + w3 * P[2].x + w4 * P[3].x, w1 * P[0].y + w2 * P[1].y + w3 * P[2].y + w4 * P[3].y);
            }


            ImPlot::SetNextLineStyle(ImVec4(1, 0.5f, 1, 1));
            ImPlot::PlotLine("##h1", &P[0].x, &P[0].y, 2, 0, 0, sizeof(ImPlotPoint));
            ImPlot::SetNextLineStyle(ImVec4(0, 0.5f, 1, 1));
            ImPlot::PlotLine("##h2", &P[2].x, &P[2].y, 2, 0, 0, sizeof(ImPlotPoint));
            ImPlot::SetNextLineStyle(ImVec4(0, 0.9f, 0, 1), 2);
            ImPlot::PlotLine("##bez", &B[0].x, &B[0].y, 100, 0, 0, sizeof(ImPlotPoint));
            
            ImPlot::EndPlot();
        }
        
        


        ImGui::End();
    };
}

