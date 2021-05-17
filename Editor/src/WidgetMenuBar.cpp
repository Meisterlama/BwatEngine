#include "WidgetMenuBar.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "Serialization/Serialization.hpp"
#include "ResourceManager/ResourceManager.hpp"

WidgetMenuBar::WidgetMenuBar(EditorInterface *editor) : Widget(editor)
{
    title = "MenuBar";
    isWindow = false;
}

void WidgetMenuBar::TickAlways()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            MenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows"))
        {
            MenuWindow();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Options"))
        {
            MenuOption();
            ImGui::EndMenu();
        }
        if (ImGui::MenuItem("Save Scene"))
        {
            BwatEngine::Serializer::SaveScene(editor->engine->GetScene(), "test.txt");
        }
        if (ImGui::MenuItem("Load Scene"))
        {
            BwatEngine::Serializer::LoadScene(editor->engine->GetScene(), "test.txt");
        }
        ImGui::EndMainMenuBar();
    }
}

void WidgetMenuBar::MenuWindow()
{
    auto& widgetList = editor->GetWidgetList();

    for(auto& widget  : widgetList)
    {
        if (widget->GetTitle() != "MenuBar")
        {
            if(ImGui::MenuItem(widget->GetTitle().c_str()))
            {
                widget->SetVisible(true);
            }
        }
    }
}

void WidgetMenuBar::MenuFile()
{
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                MenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}

    ImGui::Separator();

    if (ImGui::MenuItem("Checked", NULL, true)) {}
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

void WidgetMenuBar::MenuOption()
{
    if (ImGui::BeginMenu("Themes"))
    {
        if (ImGui::MenuItem("Dark"))
        {
            ImGui::StyleColorsDark();
        }
        if (ImGui::MenuItem("Light"))
        {
            ImGui::StyleColorsLight();
        }
        if (ImGui::MenuItem("Classic"))
        {
            ImGui::StyleColorsClassic();
        }
        ImGui::EndMenu();
    }
}

