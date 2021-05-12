#include "WidgetPostProcess.hpp"
#include "EditorInterface.hpp"
#include "Engine.hpp"
#include "ECS/Systems/PostProcessSystem.hpp"

WidgetPostProcess::WidgetPostProcess(EditorInterface* editor) : Widget(editor)
{
    title = "PostProcess";
}

void WidgetPostProcess::TickVisible()
{
    bool update = false;
    std::shared_ptr<BwatEngine::PostProcessSystem> system = editor->engine->GetScene().postProcessSystem;
    bool isPostProcess = system->isPostProcess;
    bool isBloom = system->bloom.IsEnabled();

    update |= ImGui::Checkbox("Active Post Process", &isPostProcess);
    
    if (ImGui::CollapsingHeader("Bloom", ImGuiTreeNodeFlags_DefaultOpen))
    {
        update |= ImGui::Checkbox("Active Bloom", &isBloom);
    }

    if (ImGui::CollapsingHeader("Gamma Corection", ImGuiTreeNodeFlags_DefaultOpen))
    {

    }

    if (ImGui::CollapsingHeader("Inversion", ImGuiTreeNodeFlags_DefaultOpen))
    {

    }

    if (ImGui::CollapsingHeader("Blur", ImGuiTreeNodeFlags_DefaultOpen))
    {

    }

    if (update)
    {
        system->isPostProcess = isPostProcess;
        system->bloom.SetEnabled(isBloom);
    }
}
