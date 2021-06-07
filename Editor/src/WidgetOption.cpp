#include "WidgetOption.hpp"
#include "ECS/Coordinator.hpp"
#include "ECS/Systems/RenderSystem.hpp"
#include "ResourceManager/ResourceManager.hpp"


#include "imgui_stdlib.h"

using namespace BwatEngine;

WidgetOption::WidgetOption(EditorInterface* editor) : Widget(editor)
{
    title = "Options";
    SetVisible(false);
}

void WidgetOption::TickVisible()
{

    if (ImGui::CollapsingHeader("CubeMap"))
        CubeMapEditing();

    if (ImGui::CollapsingHeader("Shadow"))
        ShadowEditing();

    if (ImGui::CollapsingHeader("Style UI"))
        ImGui::ShowStyleEditor();
}

void CreateSelectedBox(std::string& component, std::string nameCategory, bool reset = false)
{
    std::string name;

    name = component;

    if (ImGui::BeginCombo(nameCategory.c_str(), name.c_str()))
    {
        auto textList = ResourceManager::Instance()->GetTextList();

        for (auto& text : textList)
        {
            std::string path = text.string();
            bool selected = (name == path);

            if (ImGui::Selectable(path.c_str(), selected))
                component = path;

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (reset)
        name = "";
}

void WidgetOption::CubeMapEditing()
{
    auto& coordinator = Coordinator::GetInstance();
    auto rendersystem = coordinator.GetSystem<RenderSystem>();
    auto resrc = ResourceManager::Instance();
    static bool update = false;

    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[0])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[0], "left");

    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[1])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[1], "right");
    
    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[2])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[2], "up");
    
    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[3])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[3], "down");
    
    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[4])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[4], "front");
    
    ImGui::Image(reinterpret_cast<ImTextureID>(resrc->GetOrLoadTexture(rendersystem->cubeMap.faces[5])->id), ImVec2(50, 50));
    ImGui::SameLine();
    CreateSelectedBox(rendersystem->cubeMap.faces[5], "back");


    if (ImGui::Button("Reload CubeMap"))
        rendersystem->cubeMap.LoadCubeMap();
   
}

void WidgetOption::ShadowEditing()
{
    auto& coordinator = Coordinator::GetInstance();
    auto rendersystem = coordinator.GetSystem<RenderSystem>();

    ImGui::DragFloat("Intensity", &rendersystem->shadowValues.intensity);
}