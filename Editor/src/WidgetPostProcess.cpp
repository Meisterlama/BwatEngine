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
    bool isGamma = system->gammaCor.IsEnabled();
    bool isInversion = system->inversion.IsEnabled();
    bool isBlur = system->blur.IsEnabled();

    float exposure = system->bloom.exposure;
    
    if (ImGui::CollapsingHeader("Bloom", ImGuiTreeNodeFlags_DefaultOpen))
    {
        update |= ImGui::Checkbox("Active Bloom", &isBloom);

        update |= ImGui::DragFloat("Exposure", &exposure, 0.01f, 0.0f, 10.f);
    }

    if (ImGui::CollapsingHeader("Gamma Corection", ImGuiTreeNodeFlags_DefaultOpen))
    {
        update |= ImGui::Checkbox("Active Gamma Corection", &isGamma);
    }

    if (ImGui::CollapsingHeader("Inversion", ImGuiTreeNodeFlags_DefaultOpen))
    {

        update |= ImGui::Checkbox("Active Inversion", &isInversion);
    }

    if (ImGui::CollapsingHeader("Blur", ImGuiTreeNodeFlags_DefaultOpen))
    {
        update |= ImGui::Checkbox("Active Blur", &isBlur);
    }

    if(isBloom || isGamma || isInversion || isBlur)
        isPostProcess = true;
    else
        isPostProcess = false;
    

    if (update)
    {
        system->isPostProcess = isPostProcess;
        system->bloom.SetEnabled(isBloom);
        system->gammaCor.SetEnabled(isGamma);
        system->inversion.SetEnabled(isInversion);
        system->blur.SetEnabled(isBlur);
        system->bloom.exposure = exposure;
    }
}
