#include "Serialization/SerializeComponent.hpp"
#include "Serialization/Utils.hpp"

namespace BwatEngine::Serialization
{
    template<>
    json SerializeComponent<TransformComponent>(const TransformComponent &transform)
    {
        json ret;

        ret["Type"] = "transform";
        ret["Data"]["position"] = SerializeVector3f(transform.position);
        ret["Data"]["rotation"] = SerializeQuatf(transform.rotation);
        ret["Data"]["scale"] = SerializeVector3f(transform.scale);

        return ret;
    }

    template<>
    json SerializeComponent<CameraComponent>(const CameraComponent &camera)
    {
        json ret;

        ret["Type"] = "camera";
        ret["Data"]["ortho"] = camera.isOrtho;
        ret["Data"]["near"] = camera.near;
        ret["Data"]["far"] = camera.far;
        if (camera.isOrtho)
        {
            ret["Data"]["left"] = camera.left;
            ret["Data"]["right"] = camera.right;
            ret["Data"]["bottom"] = camera.bottom;
            ret["Data"]["top"] = camera.top;
        }
        else
        {
            ret["Data"]["fov"] = camera.fov;
            ret["Data"]["aspect"] = camera.aspect;
        }

        return ret;
    }

    template<>
    json SerializeComponent<RigidBodyComponent>(const RigidBodyComponent &rigidbody)
    {
        json ret;

        ret["Type"] = "rigidbody";
        ret["Data"]["static"] = rigidbody.GetIsStatic();
        ret["Data"]["mass"] = rigidbody.GetMass();
        ret["Data"]["velocity"] = SerializeVector3f(rigidbody.GetVelocity());

        return ret;
    }
#define SERIALIZE_TEXTURE(texture)                    \
    if (material.texture)                             \
        materialJs[#texture] = ToGenericPath(material.texture->path)

    template<>
    json SerializeComponent<RenderableComponent>(const RenderableComponent &renderable)
    {
        json ret;

        ret["Type"] = "renderable";

        for (int i = 0; i < renderable.materials.size(); i++)
        {
            json materialJs;

            Rendering::Material &material = *(renderable.materials[i]);

            materialJs["isTextured"] = material.isTextured;

            SERIALIZE_TEXTURE(albedoMap);
            SERIALIZE_TEXTURE(normal);
            SERIALIZE_TEXTURE(metallicMap);
            SERIALIZE_TEXTURE(roughnessMap);
            SERIALIZE_TEXTURE(aoMap);

            materialJs["albedo"] = SerializeVector3f(material.albedo);
            materialJs["metallic"] = material.metallic;
            materialJs["roughness"] = material.roughness;
            materialJs["ao"] = material.ao;

            materialJs["isTilling"] = material.isTilling;
            materialJs["tile"] = SerializeVector2f(material.tile);

            ret["Data"]["materials"].push_back(materialJs);
        }

        ret["Data"]["model"] = (renderable.model) ? ToGenericPath(renderable.model->modelPath) : "";

        return ret;
    }
#undef SERIALIZE_TEXTURE

    template<>
    json SerializeComponent<ColliderComponent>(const ColliderComponent &collider)
    {
        json ret;

        ret["Type"] = "collider";

        ret["Data"]["shapeType"] = collider.GetShapeType();

        json shapeData;

        switch (collider.GetShapeType())
        {
            case Collider::CUBE:
                shapeData["halfExtents"] = SerializeVector3f(collider.GetBoxExtent());
                break;
            case Collider::SPHERE:
                shapeData["radius"] = collider.GetSphereRadius();
                break;
        }

        ret["Data"]["shapeData"] = shapeData;
        return ret;
    }

    template<>
    json SerializeComponent<ScriptComponent>(const ScriptComponent &script)
    {
        json ret;

        ret["Type"] = "script";
        ret["Data"]["path"] = ToGenericPath(script.scriptPath);

        return ret;
    }

    template<>
    json SerializeComponent<AudioSourceComponent>(const AudioSourceComponent &audio)
    {
        json ret;

        ret["Type"] = "audio";
        ret["Data"]["path"] = (audio.source.audioData) ? ToGenericPath(audio.source.audioData->path) : "";
        ret["Data"]["gain"] = audio.source.GetGain();
        ret["Data"]["pitch"] = audio.source.GetPitch();
        ret["Data"]["looping"] = audio.source.GetLooping();

        return ret;
    }

    template<>
    json SerializeComponent<LightComponent>(const LightComponent &light)
    {
        json ret;

        ret["Type"] = "light";
        ret["Data"]["lightType"] = light.typeoflight;

        ret["Data"]["position"] = SerializeVector3f(light.position);
        ret["Data"]["direction"] = SerializeVector3f(light.direction);

        ret["Data"]["ambient"] = SerializeVector3f(light.ambient);
        ret["Data"]["diffuse"] = SerializeVector3f(light.diffuse);
        ret["Data"]["specular"] = SerializeVector3f(light.specular);

        ret["Data"]["constant"] = light.constant;
        ret["Data"]["linear"] = light.linear;
        ret["Data"]["quadratic"] = light.quadratic;

        if (light.typeoflight == Rendering::Spot)
        {
            ret["Data"]["cutoff"] = light.cutoff;
            ret["Data"]["outerCutoff"] = light.outerCutoff;
        }

        return ret;
    }

    template<>
    json SerializeComponent<DataComponent>(const DataComponent &data)
    {
        json ret;

        ret["Type"] = "data";
        ret["Data"]["name"] = data.name;

        return ret;
    }

    template<>
    json SerializeComponent<AnimatorComponent>(const AnimatorComponent& anim)
    {
        json ret;

        ret["Type"] = "animator";

        for (int i = 0; i < anim.names.size(); i++)
        {
            json animation;

            animation["name"] = anim.names[i];
            animation["path"] = anim.animations[i].path;

            ret["Data"]["animations"].push_back(animation);
        }

        return ret;
    }
}