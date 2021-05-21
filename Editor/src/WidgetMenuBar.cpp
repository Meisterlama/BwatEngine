#include "WidgetMenuBar.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "Serialization/Serialization.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include "Time.hpp"
#include "ECS/Coordinator.hpp"

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
        if (ImGui::BeginMenu("Options"))
        {
            MenuOption();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void WidgetMenuBar::MenuWindow()
{
    auto& widgetList = editor->GetWidgetList();

    for(auto& widget  : widgetList)
    {
        if (widget->GetTitle() != "MenuBar" || widget->GetTitle() != "Save Picker")
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
    if (ImGui::MenuItem("New Scene"))
    {
        BwatEngine::Coordinator::GetInstance().DestroyAllEntities();
        editor->currentScene = nullptr;
    }
    if (editor->currentScene != nullptr)
        enabled = true;
    if (ImGui::MenuItem("Save Scene", 0, false, enabled))
    {
        BwatEngine::Serializer::SaveScene(editor->currentScene);
    }
    if (ImGui::MenuItem("Save as..."))
    {
        editor->GetWidgetList().at(7)->SetVisible(true);
    }
    if (ImGui::MenuItem("Load Scene"))
    {
        editor->GetWidgetList().at(8)->SetVisible(true);
    }

    ImGui::Separator();

    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

void WidgetMenuBar::MenuOption()
{
    ImGui::Text("FPS: %.0f", (BwatEngine::Time::deltaTime != 0) ? 1.f / BwatEngine::Time::deltaTime : 0);
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
        if (ImGui::MenuItem("Bwat"))
        {
            editor->ApplyStyle();
        }
        ImGui::EndMenu();
    }
}

