#pragma once

#include <Termina/World/World.hpp>
#include <Termina/Physics/IPhysicsCallbacks.hpp>
#include "Prefab.hpp"
#include "Scene.hpp"

namespace TerminaScript {
    /// Represents a scriptable component that can be attached to an actor.
    class ScriptableComponent : public Termina::Component, public Termina::IPhysicsCallbacks
    {
    public:
        ScriptableComponent() = default;
        ScriptableComponent(Termina::Actor* owner) : Termina::Component(owner) {}

        /// Called when the component is first created.
        virtual void Awake() {}
        /// Called when the scene starts.
        virtual void Start() {}
        /// Called when the scene stops.
        virtual void Stop() {}
        /// Called before the component is updated.
        virtual void PreUpdate(float deltaTime) {}
        /// Called during the component's update.
        virtual void Update(float deltaTime) {}
        /// Called after the component is updated.
        virtual void PostUpdate(float deltaTime) {}
        /// Called before the component's physics are updated.
        virtual void PrePhysics(float deltaTime) {}
        /// Called during the component's physics update.
        virtual void Physics(float deltaTime) {}
        /// Called after the component's physics are updated.
        virtual void PostPhysics(float deltaTime) {}

        // Override to persist fields across hot-reloads and world saves.
        virtual void Serialize(nlohmann::json& out) const override {}
        virtual void Deserialize(const nlohmann::json& in) override {}

        virtual void OnCollisionEnter(Termina::Actor* other) override {}
        virtual void OnCollisionStay(Termina::Actor* other)  override {}
        virtual void OnCollisionExit(Termina::Actor* other)  override {}
        virtual void OnTriggerEnter(Termina::Actor* other)   override {}
        virtual void OnTriggerStay(Termina::Actor* other)    override {}
        virtual void OnTriggerExit(Termina::Actor* other)    override {}

        Termina::UpdateFlags GetUpdateFlags() const override { return (Termina::UpdateFlags)0; }

        std::string SetName(std::string newName){ m_Name = newName; }
    private:
        friend class Termina::Actor;
        void OnInit()                override;
        void OnPlay()                override { Start(); }
        void OnStop()                override { Stop(); }
        void OnPreUpdate(float dt)   override { PreUpdate(dt); }
        void OnUpdate(float dt)      override { Update(dt); }
        void OnPostUpdate(float dt)  override { PostUpdate(dt); }
        void OnPrePhysics(float dt)  override { PrePhysics(dt); }
        void OnPhysics(float dt)     override { Physics(dt); }
        void OnPostPhysics(float dt) override { PostPhysics(dt); }

    protected:
        friend class ScriptManager;

        /// Instantiates an empty actor.
        Termina::Actor* Instantiate() { return m_Owner->GetParentWorld()->SpawnActor(); }
        /// Instantiates a new actor by cloning an existing one.
        Termina::Actor* Instantiate(Termina::Actor* actor);
        /// Instantiates a new actor from a prefab asset.
        Termina::Actor* Instantiate(const Prefab& prefab);
        /// Destroys the given actor.
        void Destroy(Termina::Actor* actor);

        /// Requests a transition to the scene at the given path.
        /// The transition is deferred until the start of the next frame.
        void LoadScene(const Scene& scene);
        /// Requests a transition to the scene at the given path.
        /// The transition is deferred until the start of the next frame.
        void LoadScene(const std::string& path);

        /// The transform component of this actor.
        Termina::Transform* m_Transform;
        /// The name of this actor.
        std::string m_Name;

        template<typename T>
        T* AddComponent()
        {
            return m_Owner->AddComponent<T>();
        }

        template<typename T>
        T* GetComponent()
        {
            return m_Owner->GetComponent<T>();
        }

        template<typename T>
        T* RemoveComponent()
        {
            return m_Owner->RemoveComponent<T>();
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Owner->HasComponent<T>();
        }

        std::vector<Termina::Actor*> GetChildren()
        {
            return m_Owner->GetChildren();
        }
    };
}
