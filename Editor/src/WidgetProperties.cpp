#include <ECS/Components/TransformComponent.hpp>
#include <ECS/Components/RenderableComponent.hpp>
#include <ECS/Components/RigidBodyComponent.hpp>
#include <ECS/Components/AudioSourceComponent.hpp>
#include <ECS/Components/ColliderComponent.hpp>

#include "ResourceManager/ResourceManager.hpp"
#include "ECS/Coordinator.hpp"

#include <Rendering/Model.hpp>

#include "WidgetProperties.hpp"

BwatEngine::Entity WidgetProperties::currentEntity = 0;

WidgetProperties::WidgetProperties(EditorInterface *editor) : Widget(editor)
{
    title = "Properties";
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::TransformComponent>(BwatEngine::TransformComponent& component)
{
    if (ImGui::CollapsingHeader("Transform",ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat3("Position", component.transform.position.values, 0.01);
        ImGui::DragFloat3("Rotation", component.transform.rotation.values, 0.01);
        ImGui::DragFloat3("Scale", component.transform.scale.values, 0.01);
    }
}

template<>
void WidgetProperties::ShowComponent<BwatEngine::RenderableComponent>(BwatEngine::RenderableComponent& component)
{
    if (ImGui::CollapsingHeader("Renderable",ImGuiTreeNodeFlags_DefaultOpen))
    {
        const char* modelName = component.model->modelPath.filename().string().c_str();
        ImGui::Text("Mesh");
        ImGui::SameLine();
        if(ImGui::BeginCombo("##Mesh", modelName))
        {
            auto meshList = BwatEngine::ResourceManager::Instance()->GetModelList();

            for(auto &model : meshList)
            {
                bool selected = (modelName == model.c_str());
                if(ImGui::Selectable(model.c_str(), selected))
                {
                    component.model = BwatEngine::ResourceManager::Instance()->GetOrLoadModel(model);
                }
                if(selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        for (int i = 0; i < component.materials.size(); i++)
        {
            const char* DiffName;
            if (component.materials[i]->diffuse != nullptr)
                DiffName = component.materials[i]->diffuse->path.c_str();
            else
                DiffName = "";

            ImGui::Text("Diffuse Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Diff", DiffName))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (DiffName == text.c_str());
                    if(ImGui::Selectable(text.c_str(), selected))
                    {
                        component.materials[i]->diffuse = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(text, Rendering::Texture::Format::E_DIFFUSE);
                    }
                    if(selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            const char* SpecName;
            if (component.materials[i]->specular != nullptr)
                SpecName = component.materials[i]->specular->path.c_str();
            else
                SpecName = "";

            ImGui::Text("Specular Texture");
            ImGui::SameLine();
            if(ImGui::BeginCombo("##Spec", SpecName))
            {
                auto textList = BwatEngine::ResourceManager::Instance()->GetTextList();

                for(auto &text : textList)
                {
                    bool selected = (SpecName == text.c_str());
                    if(ImGui::Selectable(text.c_str(), selected))
                    {
                        component.materials[i]->specular = BwatEngine::ResourceManager::Instance()->GetOrLoadTexture(text, Rendering::Texture::Format::E_SPECULAR);;
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

        bool isStatic = component.rigidBody.GetIsStatic();
        update |= ImGui::Checkbox("isStatic", &isStatic);

        if (!isStatic)
        {
            bool updateNotStatic = false;
            float mass = component.rigidBody.GetMass();
            BwatEngine::Math::Vec3f velocity = component.rigidBody.GetVelocity();

            updateNotStatic |= ImGui::DragFloat("Mass", &mass, 0.1f, 0.0f, 100.f);
            updateNotStatic |= ImGui::DragFloat3("Velocity", velocity.values, 0.1f);

            if (updateNotStatic)
            {
                component.rigidBody.SetMass(mass);
                component.rigidBody.SetVelocity(velocity);
            }
        }

        if (update)
            component.rigidBody.SetStatic(isStatic);
        
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

void WidgetProperties::TickVisible()
{
    using namespace BwatEngine;

    Coordinator &coordinator = *Coordinator::GetInstance();
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

        ImGui::EndMenu();
    }

    ShowComponentMenuItem<TransformComponent>(currentEntity);
    ShowComponentMenuItem<RenderableComponent>(currentEntity);
    ShowComponentMenuItem<RigidBodyComponent>(currentEntity);
    ShowComponentMenuItem<AudioSourceComponent>(currentEntity);
    //ShowComponentMenuItem<ColliderComponent>(currentEntity);
}

void WidgetProperties::Inspect(BwatEngine::Entity &entity)
{
    currentEntity = entity;
}

template<typename T>
bool WidgetProperties::AddComponentMenuItem(BwatEngine::Entity entity)
{
    BwatEngine::Coordinator &coordinator = *BwatEngine::Coordinator::GetInstance();
    BwatEngine::Signature entitySignature = coordinator.GetEntitySignature(entity);

    if (!entitySignature.test(coordinator.GetComponentType<T>()))
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
bool WidgetProperties::ShowComponentMenuItem(BwatEngine::Entity entity)
{
    BwatEngine::Coordinator &coordinator = *BwatEngine::Coordinator::GetInstance();
    BwatEngine::Signature entitySignature = coordinator.GetEntitySignature(entity);

    if (entitySignature.test(coordinator.GetComponentType<T>()))
    {
        ShowComponent(coordinator.GetComponent<T>(currentEntity));
        return true;
    }
    return false;
}
