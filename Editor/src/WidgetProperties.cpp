#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderableComponent.hpp>
#include <ECS/Components/RigidBodyComponent.hpp>
#include <ECS/Components/AudioSourceComponent.hpp>
#include <ECS/Components/ColliderComponent.hpp>
#include <ECS/Components/CameraComponent.hpp>
#include <ECS/Components/PlayerComponent.hpp>

#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Coordinator.hpp"

#include <Rendering/Model.hpp>
#include <ECS/Components/ScriptComponent.hpp>

#include "WidgetProperties.hpp"

#include "imgui_stdlib.h"

BwatEngine::EntityID WidgetProperties::currentEntity = 0;

WidgetProperties::WidgetProperties(EditorInterface *editor) : Widget(editor)
{
    title = "Properties";
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::TransformComponent>(BwatEngine::TransformComponent& component)
{
    if (ImGui::CollapsingHeader("Transform",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", component.position.values, 0.01);
        ImGui::DragFloat3("Rotation", component.rotation.values, 0.01);
        ImGui::DragFloat3("Scale", component.scale.values, 0.01);
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RenderableComponent>(BwatEngine::RenderableComponent& component)
{
    if (ImGui::CollapsingHeader("Renderable",ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string modelName;
        if (component.model != nullptr)
            modelName = component.model->modelPath.filename().string();
        else
            modelName = "";

        ImGui::Text("Mesh");
        ImGui::SameLine();
        if(ImGui::BeginCombo("##Mesh", modelName.c_str()))
        {
            auto meshList = BwatEngine::ResourceManager::Instance()->GetModelList();

            for(auto &model : meshList)
            {
                std::filesystem::path path = model;
                bool selected = (modelName == path.filename().string());
                if(ImGui::Selectable(path.string().c_str(), selected))
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
            material->SetDiffuse(*BwatEngine::ResourceManager::Instance()
                    ->GetOrLoadTexture("Assets/image/moteur.jpg",Rendering::Texture::Type::E_DIFFUSE));
            component.materials.push_back(material);
        }

        for (int i = 0; i < component.materials.size(); i++)
        {
            std::string DiffName;
            if (component.materials[i]->diffuse != nullptr)
                DiffName = component.materials[i]->diffuse->path;
            else
                DiffName = "";

            ImGui::Text("Diffuse Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Diff", DiffName.c_str()))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (DiffName == text.c_str());
                    if(ImGui::Selectable(text.c_str(), selected))
                    {
                        component.materials[i]->diffuse = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(text, Rendering::Texture::Type::E_DIFFUSE);
                    }
                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            std::string SpecName;
            if (component.materials[i]->specular != nullptr)
                SpecName = component.materials[i]->specular->path;
            else
                SpecName = "";

            ImGui::Text("Specular Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Spec", SpecName.c_str()))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (SpecName == text.c_str());
                    if(ImGui::Selectable(text.c_str(), selected))
                    {
                        component.materials[i]->specular = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(text, Rendering::Texture::Type::E_SPECULAR);;
                    }
                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RigidBodyComponent>(BwatEngine::RigidBodyComponent& component)
{
    if (ImGui::CollapsingHeader("RigidBody",ImGuiTreeNodeFlags_DefaultOpen))
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
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::AudioSourceComponent>(BwatEngine::AudioSourceComponent &component)
{
    if (ImGui::CollapsingHeader("Audio Source", ImGuiTreeNodeFlags_DefaultOpen))
    {
        bool update = false;
        float gain = component.source.GetGain();
        float pitch = component.source.GetPitch();
        bool loop = component.source.GetLooping();

        update |= ImGui::DragFloat("gain", &gain, 0.1f, 0.0f, 100.f);
        update |= ImGui::DragFloat("pitch", &pitch, 0.01f, 0.0f, 100.f);
        update |= ImGui::Checkbox("loop", &loop);

        if (update)
        {
            component.source.SetGain(gain);
            component.source.SetPitch(pitch);
            component.source.SetLooping(loop);
        }

        if(ImGui::Button("Play"))
            component.source.Play();
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::CameraComponent>(BwatEngine::CameraComponent &component)
{
    if (ImGui::CollapsingHeader("Camera Component", ImGuiTreeNodeFlags_DefaultOpen))
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
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::ScriptComponent>(BwatEngine::ScriptComponent &component)
{
    if (ImGui::CollapsingHeader("Camera Component", ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string ScriptName = component.scriptPath;
        if(ImGui::InputText("ScriptFile", &ScriptName, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            component.scriptPath = ScriptName;
        }
    }
}

void WidgetProperties::TickVisible()
{
    using namespace BwatEngine;

    Coordinator &coordinator = Coordinator::GetInstance();
    if (ImGui::Button("Create Entity"))
    {
        coordinator.CreateEntity();
    }

    Signature entitySignature = coordinator.GetEntitySignature(currentEntity);

    if (ImGui::BeginMenu("AddComponent"))
    {
        bool hasComponentAvailable = false;

        hasComponentAvailable |= AddComponentMenuItem<TransformComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<RigidBodyComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<RenderableComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<AudioSourceComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<ColliderComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<CameraComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<PlayerComponent>(currentEntity);
        hasComponentAvailable |= AddComponentMenuItem<ScriptComponent>(currentEntity);

        ImGui::EndMenu();
    }

    ShowComponentMenuItem<TransformComponent>(currentEntity);
    ShowComponentMenuItem<RenderableComponent>(currentEntity);
    ShowComponentMenuItem<RigidBodyComponent>(currentEntity);
    ShowComponentMenuItem<AudioSourceComponent>(currentEntity);
    ShowComponentMenuItem<CameraComponent>(currentEntity);
    ShowComponentMenuItem<ScriptComponent>(currentEntity);
    //ShowComponentMenuItem<ColliderComponent>(currentEntity);
}

void WidgetProperties::Inspect(BwatEngine::EntityID entity)
{
    currentEntity = entity;
}

template<typename T>
bool WidgetProperties::AddComponentMenuItem(BwatEngine::EntityID entity)
{
    BwatEngine::Coordinator &coordinator = BwatEngine::Coordinator::GetInstance();
    BwatEngine::Signature entitySignature = coordinator.GetEntitySignature(entity);

    if (!coordinator.HaveComponent<T>(entity))
    {
        //TODO: proper component name
        if (ImGui::MenuItem(typeid(T).name()))
            //TODO: proper default value for the component
            coordinator.AddComponent<T>(entity, {});
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
        ShowComponent(coordinator.GetComponent<T>(currentEntity));
        return true;
    }
    return false;
}
