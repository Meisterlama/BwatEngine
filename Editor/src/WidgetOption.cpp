#include "WidgetOption.hpp"

using namespace BwatEngine;

WidgetOption::WidgetOption(EditorInterface* editor) : Widget(editor)
{
    title = "Options";
    SetVisible(false);
}

void WidgetOption::TickVisible()
{
    static bool update = false;

    Math::Vec4f textColor = cText;
    //Math::Vec4f interColor = cInteractive;
    //Math::Vec4f ihColor = cIH;
    //Math::Vec4f backColor = cBackground;
    //Math::Vec4f BCColor = cBC;
    //Math::Vec4f shadowColor = cShadow;
    float round = roundness;
    float other = jsp;

    update |= ImGui::ColorEdit4("Text Color", textColor.values, ImGuiColorEditFlags_Float);
    update |= ImGui::DragFloat("roundnes", &round);
    update |= ImGui::DragFloat("???", &other);


    //update |= ImGui::ColorEdit4("Interractive Color", interColor.values, ImGuiColorEditFlags_Float);
    //update |= ImGui::ColorEdit4("Interactive hiden Color", ihColor.values, ImGuiColorEditFlags_Float);
    //update |= ImGui::ColorEdit4("background Color", backColor.values, ImGuiColorEditFlags_Float);
    //update |= ImGui::ColorEdit4("BC Color", BCColor.values, ImGuiColorEditFlags_Float);
    //update |= ImGui::ColorEdit4("Shadow Color", shadowColor.values, ImGuiColorEditFlags_Float);

    if (update)
    {
        cText = textColor;
        roundness = round;
        jsp = other;
    //    cInteractive = interColor;
    //    cIH = ihColor;
    //    cBackground = backColor;
    //    cBC = BCColor;
    //    cShadow = shadowColor;
    }

    if (ImGui::Button("Reaload Style"))
    {
        ApplyStyle();
    }
}

void WidgetOption::ApplyStyle()
{
    // Color settings
    const auto color_text = ImVec4(cText.X , cText.Y , cText.Z , cText.W );
    //const auto color_text_disabled = ImVec4(color_text.x, color_text.y, color_text.z, 0.5f);
    //const auto color_interactive = ImVec4( cInteractive.X, cInteractive.Y , cInteractive.Z , cInteractive.W);
    //const auto color_interactive_hovered = ImVec4(cIH.X , cIH.Y , cIH.Z , cIH.W);
    //const auto color_background = ImVec4(cBackground.X , cBackground.Y , cBackground.Z , cBackground.W);
    //const auto color_background_content = ImVec4(cBC.X , cBC.Y , cBC.Z , 1.f);
    //const auto color_shadow = ImVec4(cShadow.X , cShadow.Y, cShadow.Z, cShadow.W);

    // Colors
    //ImVec4* colors = ImGui::GetStyle().Colors;
    //colors[ImGuiCol_Text] = color_text;
    ////colors[ImGuiCol_TextDisabled] = color_text_disabled;
    ////colors[ImGuiCol_WindowBg] = color_background;             // Background of normal windows
    //colors[ImGuiCol_ChildBg] = color_background;             // Background of child windows
    //colors[ImGuiCol_PopupBg] = color_background;             // Background of popups, menus, tooltips windows
    //colors[ImGuiCol_Border] = color_interactive;
    ////colors[ImGuiCol_BorderShadow] = color_shadow;
    //colors[ImGuiCol_FrameBg] = color_background_content;     // Background of checkbox, radio button, plot, slider, text input
    //colors[ImGuiCol_FrameBgHovered] = color_interactive;
    //colors[ImGuiCol_FrameBgActive] = color_interactive_hovered;
    //colors[ImGuiCol_TitleBg] = color_background_content;
    //colors[ImGuiCol_TitleBgActive] = color_shadow;
    //colors[ImGuiCol_TitleBgCollapsed] = color_background;
    //colors[ImGuiCol_MenuBarBg] = color_background_content;
    //colors[ImGuiCol_ScrollbarBg] = color_background_content;
    //colors[ImGuiCol_ScrollbarGrab] = color_interactive;
    //colors[ImGuiCol_ScrollbarGrabHovered] = color_interactive_hovered;
    //colors[ImGuiCol_ScrollbarGrabActive] = color_interactive_hovered;
    //colors[ImGuiCol_CheckMark] = color_text;
    //colors[ImGuiCol_SliderGrab] = color_interactive;
    //colors[ImGuiCol_SliderGrabActive] = color_interactive_hovered;
    //colors[ImGuiCol_Button] = color_interactive;
    //colors[ImGuiCol_ButtonHovered] = color_interactive_hovered;
    //colors[ImGuiCol_ButtonActive] = color_interactive_hovered;
    //colors[ImGuiCol_Header] = color_interactive;            // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
    //colors[ImGuiCol_HeaderHovered] = color_interactive_hovered;
    //colors[ImGuiCol_HeaderActive] = color_text;
    //colors[ImGuiCol_Separator] = color_interactive;
    //colors[ImGuiCol_SeparatorHovered] = color_interactive_hovered;
    //colors[ImGuiCol_SeparatorActive] = color_text;
    //colors[ImGuiCol_ResizeGrip] = color_interactive;
    //colors[ImGuiCol_ResizeGripHovered] = color_interactive_hovered;
    //colors[ImGuiCol_ResizeGripActive] = color_interactive_hovered;
    //colors[ImGuiCol_Tab] = color_text;
    ////colors[ImGuiCol_TabHovered] = color_interactive_hovered;
    ////colors[ImGuiCol_TabActive] = color_text;
    //colors[ImGuiCol_TabUnfocused] = color_text;
    //colors[ImGuiCol_TabUnfocusedActive] = color_text;            // Might be called active, but it's active only because it's it's the only tab available, the user didn't really activate it
    //colors[ImGuiCol_DockingPreview] = color_interactive_hovered;    // Preview overlay color when about to docking something
    //colors[ImGuiCol_DockingEmptyBg] = color_interactive;            // Background color for empty node (e.g. CentralNode with no window docked into it)
    //colors[ImGuiCol_PlotLines] = color_interactive;
    //colors[ImGuiCol_PlotLinesHovered] = color_interactive_hovered;
    //colors[ImGuiCol_PlotHistogram] = color_interactive;
    //colors[ImGuiCol_PlotHistogramHovered] = color_interactive_hovered;
    //colors[ImGuiCol_TextSelectedBg] = color_background;
    //colors[ImGuiCol_DragDropTarget] = color_interactive_hovered;    // Color when hovering over target
    //colors[ImGuiCol_NavHighlight] = color_background;             // Gamepad/keyboard: current highlighted item
    //colors[ImGuiCol_NavWindowingHighlight] = color_background;             // Highlight window when using CTRL+TAB
    //colors[ImGuiCol_NavWindowingDimBg] = color_background;             // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    //colors[ImGuiCol_ModalWindowDimBg] = color_background;             // Darken/colorize entire screen behind a modal window, when one is active
    //
    // Spatial settings
    const auto font_size = 24.0f;
    const auto font_scale = 0.8f;
    //
    //// Spatial
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0;
    style.ScrollbarSize = 20.0f;
    style.FramePadding = ImVec2(5, 5);
    style.ItemSpacing = ImVec2(6, 5);
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.WindowRounding = roundness;
    style.FrameRounding = roundness;
    style.PopupRounding = roundness;
    style.GrabRounding = roundness;
    style.ScrollbarRounding = roundness;
    style.Alpha = 1.0f;
}