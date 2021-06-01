#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderableComponent.hpp>
#include <ECS/Components/RigidBodyComponent.hpp>
#include <ECS/Components/AudioSourceComponent.hpp>
#include <ECS/Components/ColliderComponent.hpp>
#include <ECS/Components/CameraComponent.hpp>
#include <ECS/Components/PlayerComponent.hpp>
#include <ECS/Components/LightComponent.hpp>
#include <ECS/Components/DataComponent.hpp>
#include <ECS/Components/ScriptComponent.hpp>
#include <ECS/Components/AnimatorComponent.hpp>

#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Coordinator.hpp"

#include <Rendering/Model.hpp>
#include "WidgetProperties.hpp"

#include "imgui_stdlib.h"

WidgetProperties::WidgetProperties(EditorInterface *editor) : Widget(editor)
{
    title = "Properties";
    flags |= ImGuiWindowFlags_MenuBar;
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::DataComponent>(BwatEngine::DataComponent& component)
{
    auto& coordinator = BwatEngine::Coordinator::GetInstance();
    ImGui::Text("Entity ID: %i", coordinator.GetEntityIDFrom(component));
    ImGui::InputText("Name", &component.name);
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::TransformComponent>(BwatEngine::TransformComponent& component)
{
        ImGui::DragFloat3("Position", component.position.values, 0.01);

        // Handle rotation
        if (ImGui::DragFloat3("Rotation", eulersInDegrees.values, 1.0))
        {
            BwatEngine::Math::Vec3f radEulers;
            radEulers.X = BwatEngine::Math::ToRads(eulersInDegrees.X);
            radEulers.Y = BwatEngine::Math::ToRads(eulersInDegrees.Y);
            radEulers.Z = BwatEngine::Math::ToRads(eulersInDegrees.Z);
            component.rotation = BwatEngine::Math::Quatf(radEulers);
        }

        ImGui::DragFloat3("Scale", component.scale.values, 0.01);
}

void TextCenter(std::string text)
{
    ImGui::Text("");
    float font_size = ImGui::GetFontSize() * text.size() / 2;
    ImGui::SameLine( ImGui::GetWindowSize().x / 2 - font_size + (font_size / 2) - 10);
    ImGui::Text(text.c_str());
}

void CreateSelectedBox(Rendering::Texture*& component,int index, std::string nameCategory, bool reset = false)
{
    std::string name;

    if (component != nullptr)
        name = component->path;
    else
        name = "";


    if (ImGui::BeginCombo(nameCategory.c_str(), name.c_str()))
    {
        auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

        for (auto &text : textList)
        {
            std::string path = text;
            bool selected = (name == path);

            if (ImGui::Selectable(path.c_str(), selected))
                component = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(text, Rendering::Texture::Type::E_DIFFUSE);;
   
            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    if (reset)
        name = "";
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RenderableComponent>(BwatEngine::RenderableComponent& component)
{
        std::string modelName;
        if (component.model != nullptr)
            modelName = component.model->modelPath;
        else
            modelName = "";

        ImGui::Text("Mesh");
        ImGui::SameLine();
        if(ImGui::BeginCombo("##Mesh", modelName.c_str()))
        {
            auto meshList = BwatEngine::ResourceManager::Instance()->GetModelList();

            for(auto &model : meshList)
            {
                std::string path = model;
                bool selected = (modelName == path);
                if(ImGui::Selectable(path.c_str(), selected))
                {
                    component.model = BwatEngine::ResourceManager::Instance()->GetOrLoadModel(model);
                }
                if(selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Add Materials"))
        {
            auto material = new Rendering::Material;

            component.materials.push_back(material);
        }

        for (int i = 0; i < component.materials.size(); i++)
        {
            bool resetTexture = false;

            if (ImGui::Button("Clear Texture"))
            {
                component.materials[i]->normal = nullptr;
                component.materials[i]->albedoMap = nullptr;
                component.materials[i]->metallicMap = nullptr;
                component.materials[i]->roughnessMap = nullptr;
                component.materials[i]->aoMap = nullptr;

                resetTexture = true;
            }

            bool update = false;

            bool isTextured = component.materials[i]->isTextured;
            update |= ImGui::Checkbox("Textured", &isTextured);

            CreateSelectedBox(component.materials[i]->normal, i, "Normal", resetTexture);

            if (isTextured)
            {
                CreateSelectedBox(component.materials[i]->albedoMap, i, "Albedo", resetTexture);
                CreateSelectedBox(component.materials[i]->metallicMap, i, "Metallic", resetTexture);
                CreateSelectedBox(component.materials[i]->roughnessMap, i, "Roughness", resetTexture);
                CreateSelectedBox(component.materials[i]->aoMap, i, "Ao", resetTexture);
            }
            else
            {
                ImGui::DragFloat3("Albedo", component.materials[i]->albedo.values,0.1f);
                ImGui::DragFloat("Metallic", &component.materials[i]->metallic, 0.1f, 0.0f, 100.f);
                ImGui::DragFloat("Roughness", &component.materials[i]->roughness, 0.01f, 0.0f, 100.f);
                ImGui::DragFloat("Ao", &component.materials[i]->ao, 0.01f, 0.0f, 100.f);

            }

            bool isColored = component.materials[i]->isTilling;
            update |= ImGui::Checkbox("Tilling", &isColored);

            if (component.materials[i]->isTilling)
            {
                ImGui::DragFloat2("Tiles", component.materials[i]->tile.values);
            }

            TextCenter("Shadow Option");

            bool castShadow = component.castShadow;
            update |= ImGui::Checkbox("Cast Shadow", &castShadow);

            if (update)
            {
                component.materials[i]->isTextured = isTextured;
                component.materials[i]->isTilling = isColored;
                component.castShadow = castShadow;
            }

        }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RigidBodyComponent>(BwatEngine::RigidBodyComponent& component)
{
        bool update = false;
        bool isStatic = component.GetIsStatic();
        update |= ImGui::Checkbox("isStatic", &isStatic);

        if (!isStatic)
        {
            bool updateNotStatic = false;
            float mass = component.GetMass();
            BwatEngine::Math::Vec3f velocity = component.GetVelocity();

            updateNotStatic |= ImGui::DragFloat("Mass", &mass, 0.1f, 0.0f, 100.f);
            updateNotStatic |= ImGui::DragFloat3("Velocity", velocity.values, 0.1f);

            if (updateNotStatic)
            {
                component.SetMass(mass);
                component.SetVelocity(velocity);
            }
        }

        if (update)
            component.SetStatic(isStatic);

}

template<>
void WidgetProperties::ShowComponent<BwatEngine::AudioSourceComponent>(BwatEngine::AudioSourceComponent &component)
{
    bool update = false;
    float gain = component.source.GetGain();
    float pitch = component.source.GetPitch();
    bool loop = component.source.GetLooping();

    update |= ImGui::DragFloat("gain", &gain, 0.1f, 0.0f, 100.f);
    update |= ImGui::DragFloat("pitch", &pitch, 0.01f, 0.0f, 100.f);
    update |= ImGui::Checkbox("loop", &loop);

    std::string audioSourcePath;
    if (component.source.audioData)
        audioSourcePath = component.source.audioData->path;

    if(ImGui::BeginCombo("##Audio", audioSourcePath.c_str()))
    {
        auto audioList = BwatEngine::ResourceManager::Instance()->GetAudioList();

        for(auto &audio : audioList)
        {
            std::string path = audio;
            bool selected = (audioSourcePath == path);
            if(ImGui::Selectable(path.c_str(), selected))
            {
                component.source.audioData = BwatEngine::ResourceManager::Instance()->GetOrLoadAudio(path);
                component.source.Refresh();
            }
            if(selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (update)
    {
        component.source.SetGain(gain);
        component.source.SetPitch(pitch);
        component.source.SetLooping(loop);
    }

    if (ImGui::Button("Play"))
        component.source.Play();
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::CameraComponent>(BwatEngine::CameraComponent &component)
{
        if (component.isOrtho)
        {
            ImGui::DragFloat("Left", &component.left);
            ImGui::DragFloat("Right", &component.right);
            ImGui::DragFloat("Top", &component.top);
            ImGui::DragFloat("Bottom", &component.bottom);

        }
        else
        {
            ImGui::DragFloat("Field of view", &component.fov);
            ImGui::DragFloat("Aspect", &component.aspect, 0.001);
        }
        ImGui::DragFloat("Near", &component.near);
        ImGui::DragFloat("Far", &component.far);
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::ScriptComponent>(BwatEngine::ScriptComponent &component)
{
    std::string ScriptName = component.scriptPath;
    if (ImGui::InputText("ScriptFile", &ScriptName, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        component.scriptPath = ScriptName;
    }
    if (ImGui::Button("Reload"))
    {
        component.isStarted = false;
        component.waitingForChanges = false;
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::ColliderComponent>(BwatEngine::ColliderComponent &component)
{
    bool shouldUpdate = false;
    bool isTrigger = component.collider->GetIsTrigger();

    shouldUpdate |= ImGui::Checkbox("Is Trigger", &isTrigger);

    if (shouldUpdate)
    {
        component.collider->SetIsTrigger(isTrigger);
    }
}
template<>
void WidgetProperties::ShowComponent<BwatEngine::PlayerComponent>(BwatEngine::PlayerComponent &component) {}

void WidgetProperties::TickVisible()
{
    using namespace BwatEngine;

    Coordinator &coordinator = Coordinator::GetInstance();

    if (!coordinator.IsValid(currentEntity))
        return;

    if (currentEntity != 0)
    {
        if (ImGui::BeginMenuBar())
        {

            bool hasComponentAvailable = false;
            if (ImGui::BeginMenu("Add Component"))
            {
                hasComponentAvailable |= AddComponentMenuItem<TransformComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<RigidBodyComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<RenderableComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<AudioSourceComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<ColliderComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<CameraComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<PlayerComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<LightComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<DataComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<ScriptComponent>(currentEntity);
                hasComponentAvailable |= AddComponentMenuItem<AnimatorComponent>(currentEntity);

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }
    
    ShowComponentMenuItem<DataComponent>(currentEntity);
    ShowComponentMenuItem<TransformComponent>(currentEntity);
    ShowComponentMenuItem<RigidBodyComponent>(currentEntity);
    ShowComponentMenuItem<RenderableComponent>(currentEntity);
    ShowComponentMenuItem<AudioSourceComponent>(currentEntity);
    ShowComponentMenuItem<ColliderComponent>(currentEntity);
    ShowComponentMenuItem<CameraComponent>(currentEntity);
    ShowComponentMenuItem<PlayerComponent>(currentEntity);
    ShowComponentMenuItem<LightComponent>(currentEntity);
    ShowComponentMenuItem<AnimatorComponent>(currentEntity);
    ShowComponentMenuItem<ScriptComponent>(currentEntity);
}

void WidgetProperties::Inspect(BwatEngine::EntityID entity)
{
    currentEntity = entity;

    BwatEngine::Coordinator &coordinator = BwatEngine::Coordinator::GetInstance();
    if (coordinator.HaveComponent<BwatEngine::TransformComponent>(entity))
    {
        auto transform = coordinator.GetComponent<BwatEngine::TransformComponent>(currentEntity);
        eulersInDegrees = transform.rotation.GetEulerAngles();
        eulersInDegrees.X = BwatEngine::Math::ToDegs(eulersInDegrees.X);
        eulersInDegrees.Y = BwatEngine::Math::ToDegs(eulersInDegrees.Y);
        eulersInDegrees.Z = BwatEngine::Math::ToDegs(eulersInDegrees.Z);
    }
}

template<typename T>
bool WidgetProperties::AddComponentMenuItem(BwatEngine::EntityID entity)
{
    BwatEngine::Coordinator &coordinator = BwatEngine::Coordinator::GetInstance();

    if (!coordinator.HaveComponent<T>(entity))
    {
        //TODO: proper component name
        if (ImGui::MenuItem(coordinator.GetInternalName<T>().c_str()))
            //TODO: proper default value for the component
            coordinator.AddComponent<T>(entity);
        return true;
    }
    return false;
}


template<typename T>
bool WidgetProperties::ShowComponentMenuItem(BwatEngine::EntityID entity)
{
    BwatEngine::Coordinator &coordinator = BwatEngine::Coordinator::GetInstance();
    BwatEngine::Signature entitySignature = coordinator.GetEntitySignature(entity);

    if (entitySignature.test(coordinator.GetComponentType<T>()))
    {
        ImGui::PushID(coordinator.GetInternalName<T>().c_str());
        if (ImGui::CollapsingHeader(coordinator.GetInternalName<T>().c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            bool componentDeleted = false;
            if (ImGui::BeginPopupContextItem("ComponentContextMenu"))
            {
                if (ImGui::MenuItem("Delete Component"))
                {
                    coordinator.RemoveComponent<T>(currentEntity);
                    componentDeleted = true;
                }
                ImGui::EndPopup();
            }
            if (!componentDeleted)
            {
                ShowComponent(coordinator.GetComponent<T>(currentEntity));
            }
        }
        ImGui::PopID();
        return true;
    }
    return false;
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::LightComponent>(BwatEngine::LightComponent& component)
{
        bool update = false;
        BwatEngine::Math::Vec3f position = component.position;
        BwatEngine::Math::Vec3f direction = component.direction;
        BwatEngine::Math::Vec3f ambient = component.ambient;
        BwatEngine::Math::Vec3f specular = component.specular;
        BwatEngine::Math::Vec3f diffuse = component.diffuse;
        float intensity = component.intensity;

        const char* items[] = { "Directional", "Point", "Spot", };

        if (ImGui::BeginCombo("##Typeoflight", items[component.typeoflight]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                if (ImGui::Selectable(items[n], component.typeoflight == n))
                {
                    component.typeoflight = (Rendering::TYPE_LIGHT)n;
                }
                //if (is_selected)
                //    ImGui::SetItemDefaultFocus();   
            }
            ImGui::EndCombo();
        }

        update |= ImGui::DragFloat3("Position", position.values, 0.1f);
        update |= ImGui::DragFloat3("Direction", direction.values, 0.01f, -4.f, 4.f);

        update |= ImGui::ColorEdit3("Ambient", ambient.values, ImGuiColorEditFlags_Float);
        update |= ImGui::ColorEdit3("Specular", specular.values, ImGuiColorEditFlags_Float);
        update |= ImGui::ColorEdit3("Diffuse", diffuse.values, ImGuiColorEditFlags_Float);

        update |= ImGui::DragFloat("Intensity", &intensity, 0.1f, 0.0f);

        float constant = component.constant;
        float linear = component.linear;
        float quadratic = component.quadratic;

        float cutOff = component.cutoff;
        float outerCutOff = component.outerCutoff;

        if (component.typeoflight == Rendering::TYPE_LIGHT::Point || component.typeoflight == Rendering::TYPE_LIGHT::Spot)
        {

            update |= ImGui::DragFloat("Constant", &constant , 0.1f, 0.0f);
            update |= ImGui::DragFloat("linear", &linear, 0.01f, 0.0f);
            update |= ImGui::DragFloat("quadratic", &quadratic, 0.001f, 0.0f);

            if (component.typeoflight == Rendering::TYPE_LIGHT::Spot)
            {
                update |= ImGui::DragFloat("cutOff",&cutOff , 0.01f, 0.0f);
                update |= ImGui::DragFloat("outerCutOff", &outerCutOff, 0.01f, 0.0f);
            }
        }

        if (update)
        {
            //Directional Light 
            component.position = position;
            component.direction = direction;

            component.ambient = ambient;
            component.specular = specular;
            component.diffuse = diffuse;

            component.intensity = intensity;

            // Point Light 
            component.constant     = constant;
            component.linear       = linear;
            component.quadratic    = quadratic;

            // Spot Light 
            component.cutoff       = cutOff;
            component.outerCutoff  = outerCutOff;

        }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::AnimatorComponent>(BwatEngine::AnimatorComponent& component)
{
    static std::string saveName;

    ImGui::InputText("Animation Name", &saveName);

    static std::string namemodel;


    if (ImGui::BeginCombo("Animation", namemodel.c_str()))
    {
        auto textList = BwatEngine::ResourceManager::Instance()->GetModelList();

        for (auto& text : textList)
        {
            std::string path = text;
            bool selected = (namemodel == path);

            if (ImGui::Selectable(path.c_str(), selected))
                namemodel = text;

            if (selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    bool checkButton = !saveName.empty() && !namemodel.empty();

    if (checkButton && ImGui::Button("Add Animation"))
    {
        component.SetNewAnimation(saveName, namemodel);
    }

    for (int i = 0; i < component.names.size(); i++)
    {
        ImGui::Text("Animation name : %s" , component.names[i].c_str());
        
        std::string playText = "Play##" + component.names[i];

        if (ImGui::Button(playText.c_str()))
            component.PlayAnimation(component.names[i]);
        
        ImGui::SameLine();
        
        std::string deleteText = "Delete##" + component.names[i];

        if (ImGui::Button(deleteText.c_str()))
            component.DeleteAnimation(component.names[i]);
    }

    if (component.names.size() > 0)
    {
        if (ImGui::Button("Pause Animation"))
        component.isValid = false;

        ImGui::SameLine();

        if (ImGui::Button("Continue Animation"))
            component.isValid = true;
    }
    bool update = false;
    float speedAnim = component.speedAnimation;

    update |= ImGui::DragFloat("Speed Animation", &speedAnim, 1.0f, 0.0f);

    if (update)
    {
        component.speedAnimation = speedAnim;
    }

}
