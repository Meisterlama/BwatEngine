ECS
===

Getting Started
###############

Everything works with the Coordinator

.. doxygenclass:: BwatEngine::Coordinator

To operate, you need to register each components and systems needed for the engine like this :

..  code-block:: cpp
    :linenos:

    // Cache the instance
    Coordinator& coordinator = Coordinator::GetInstance();

    // Register the components required by PhysicsSystem
    coordinator.RegisterComponent<TransformComponent>();
    coordinator.RegisterComponent<RigidBodyComponent>();

    // Register the system
    PhysicsSystem* physicsSystem = *coordinator.RegisterSystem<PhysicsSystem>();

    // Create the signature for the system
    Signature signature;
    signature.set(coordinator.GetComponentType<RigidBodyComponent>());
    signature.set(coordinator.GetComponentType<TransformComponent>());

    // Set the signature
    coordinator.SetSystemSignature<PhysicsSystem>(signature);

    //Init the system
    physicsSystem->Init();

Now that the system is initialized, its Update function must be called during the main loop

Creating an Entity
##################

To create entities and add components on them, here is a snippet

..  code-block:: cpp
    :linenos:

    // Create an entity and returns its ID
    Entity entity = coordinator.CreateEntity();

    // Adding components
    coordinator.AddComponent<TransformComponent>(entity,
                {
                    Math::Vec3f{0.f, 0.f, 0.f} // position
                    Math::Vec3f{0.f, 0.f, 0.f} // rotation
                    Math::Vec3f{1.f, 1.f, 1.f} // scale
                });
    coordinator.AddComponent<RigidBodyComponent>(entity,
                {
                    Math::Vec3f{0.f, 0.f, 0.f} // velocity
                    Math::Vec3f{0.f, 0.f, 0.f} // acceleration
                });

Now this entity has a Transform and a RigidBody. Because its signature corresponds to the signature
of the system we initialized just before, its ID will be passed through the system on the update,
performing the relevant code of the update function.

Creating a Component
####################

You can just create a simple struct

Example of a boiler-plate RigidBody :

..  code-block:: cpp
    :linenos:

    namespace BwatEngine
    {
        struct RigidBodyComponent
        {
            Math::Vec3f velocity;
            Math::Vec3f acceleration;
        };
    }

Creating a System
#################

To create a system, you must create a class that inherits from System
and implement the Init and Update functions.

Example of a boiler-plate PhysicsSystem

..  code-block:: cpp
    :linenos:

    class PhysicsSystem : public System
    {
    public:
        void Init() {};

        void Update(float dt)
        {
            const Vec3f gravity{0, -10, 0};
            for (Entity entityID : entities)
            {
                Coordinator& coordinator = Coordinator::GetInstance();
                auto& rigidBody = coordinator.GetComponent<RigidBodyComponent>(entityID);
                auto& transform = coordinator.GetComponent<TransformComponent>(entityID);

                transform.position += rigidBody.velocity * dt;
                rigidBody.velocity += gravity * dt;
            }
        };
    };

Referenced headers

.. toctree::
    ECS/Coordinator