#include "core/hepch.h"

#include "components/ComponentTransform.h"
#include "components/ComponentCamera.h"
#include "components/ComponentMesh.h"
#include "components/ComponentMaterial.h"
#include "components/ComponentDirLight.h"
#include "components/ComponentPointLight.h"
#include "components/ComponentSpotLight.h"

// UI
#include "components/ComponentCanvas.h"
#include "components/ComponentCanvasRenderer.h"
#include "components/ComponentTransform2D.h"
#include "components/ComponentImage.h"
#include "components/ComponentButton.h"
#include "Components/ComponentProgressBar.h"

// TODO: REMOVE
#include "Application.h"
#include "modules/ModuleSceneManager.h"
//

#include <debugdraw.h>

Hachiko::GameObject::GameObject(const char* name) :
    name(name)
{
    AddComponent(new ComponentTransform(this, float3::zero, Quat::identity, float3::one));
}

Hachiko::GameObject::GameObject(GameObject* parent, const float4x4& transform, const char* name, UID uid) :
    name(name),
    uid(uid)
{
    AddComponent(new ComponentTransform(this, transform));
    SetNewParent(parent);
}

Hachiko::GameObject::GameObject(GameObject* parent, const char* name, UID uid, const float3& translation, const Quat& rotation, const float3& scale) :
    name(name),
    uid(uid)
{
    AddComponent(new ComponentTransform(this, translation, rotation, scale));
    SetNewParent(parent);
}

Hachiko::GameObject::~GameObject()
{
    if (parent)
    {
        parent->RemoveChild(this);
    }

    if (scene_owner)
    {
        scene_owner->DestroyGameObject(this);
    }

    for (GameObject* child : children)
    {
        child->parent = nullptr;
        RELEASE(child);
    }
    for (Component* component : components)
    {
        RELEASE(component);
    }
}

void Hachiko::GameObject::RemoveChild(GameObject* game_object)
{
    children.erase(std::remove(children.begin(), children.end(), game_object), children.end());
}

void Hachiko::GameObject::SetNewParent(GameObject* new_parent)
{
    if (new_parent == parent)
    {
        return;
    }

    if (parent)
    {
        parent->RemoveChild(this);
    }

    parent = new_parent;

    if (new_parent)
    {
        float4x4 temp_matrix = this->GetTransform()->GetGlobalMatrix();
        new_parent->children.push_back(this);
        this->GetTransform()->SetGlobalTransform(temp_matrix);
    }
}

void Hachiko::GameObject::AddComponent(Component* component)
{
    switch (component->GetType())
    {
    case (Component::Type::TRANSFORM):
    {
        components.push_back(component);
        transform = static_cast<ComponentTransform*>(component);
        component->SetGameObject(this);
        break;
    }
    case (Component::Type::CAMERA):
    {
        components.push_back(component);
        component->SetGameObject(this);
        break;
    }
    }
}

Hachiko::Component* Hachiko::GameObject::CreateComponent(Component::Type type)
{
    Component* new_component = nullptr;
    switch (type)
    {
    case (Component::Type::TRANSFORM):
        return transform;
        break;
    case (Component::Type::CAMERA):
        new_component = new ComponentCamera(this);
        break;
    case (Component::Type::MESH):
        new_component = new ComponentMesh(this);
        break;
    case (Component::Type::MATERIAL):
        new_component = new ComponentMaterial(this);
        break;
    case (Component::Type::DIRLIGHT):
        new_component = new ComponentDirLight(this);
        break;
    case (Component::Type::POINTLIGHT):
        new_component = new ComponentPointLight(this);
        break;
    case (Component::Type::SPOTLIGHT):
        new_component = new ComponentSpotLight(this);
        break;
    case (Component::Type::CANVAS):
        if (!GetComponent<ComponentCanvas>())
            new_component = new ComponentCanvas(this);
        break;
    case (Component::Type::CANVAS_RENDERER):
        if (!GetComponent<ComponentCanvasRenderer>())
            new_component = new ComponentCanvasRenderer(this);
        break;
    case (Component::Type::TRANSFORM_2D):
        if (!GetComponent<ComponentTransform2D>())
            new_component = new ComponentTransform2D(this);
        break;
    case (Component::Type::IMAGE):
        if (!GetComponent<ComponentImage>())
            new_component = new ComponentImage(this);
        break;
    case (Component::Type::BUTTON):
        if (!GetComponent<ComponentButton>())
            new_component = new ComponentButton(this);
        break;
    case (Component::Type::PROGRESS_BAR):
        if (!GetComponent<ComponentProgressBar>())
            new_component = new ComponentProgressBar(this);
        break;
    }

    if (new_component != nullptr)
    {
        components.push_back(new_component);
    }
    else
    {
        HE_LOG("Falied to create component");
    }
    return new_component;
}

void Hachiko::GameObject::SetActive(bool set_active)
{
    if (!active && set_active)
    {
        Start();
    }
    active = set_active;
}


void Hachiko::GameObject::Start() 
{
    if (!started)
    {
        transform->Start();
        for (Component* component : components)
        {
            component->Start();
        }

        for (GameObject* child : children)
        {
            if (child->IsActive())
            {
                child->Start();
            }
        }
        started = true;
    }  
}

void Hachiko::GameObject::Update()
{
    // TODO: REMOVE
    if (name == "Gun")  // This is temporal, once scripting is finally merged, we should try to do the same there for the player 
    {
        GameObject* go = App->scene_manager->GetActiveScene()->RayCast(transform->GetGlobalPosition() - float3(0, 5, 0), transform->GetGlobalPosition());
    }
    //

    if (transform->HasChanged())
    {
        OnTransformUpdated();
    }

    for (Component* component : components)
    {
        component->Update();
    }

    for (GameObject* child : children)
    {
        if (child->IsActive())
        {
            child->Update();
        }
    }
}

void Hachiko::GameObject::DrawAll(ComponentCamera* camera, Program* program) const
{
    // Draw yourself
    Draw(camera, program);
    // Draw children recursively
    for (const GameObject* child : children)
    {
        child->DrawAll(camera, program);
    }
}

void Hachiko::GameObject::Draw(ComponentCamera* camera, Program* program) const
{
    // Call draw on all components
    for (Component* component : components)
    {
        component->Draw(camera, program);
    }
}

void Hachiko::GameObject::DrawStencil(ComponentCamera* camera, Program* program)
{
    auto* mesh = GetComponent<ComponentMesh>();
    if (mesh)
    {
        mesh->DrawStencil(camera, program);
    }
}

void Hachiko::GameObject::OnTransformUpdated()
{
    // Update components
    for (Component* component : components)
    {
        component->OnTransformUpdated();
    }

    // Update children
    for (GameObject* child : children)
    {
        child->OnTransformUpdated();
    }

    UpdateBoundingBoxes();
}

void Hachiko::GameObject::DebugDrawAll()
{
    // Draw yourself
    DebugDraw();
    // Draw children recursively
    for (GameObject* child : children)
    {
        child->DebugDrawAll();
    }
}

void Hachiko::GameObject::DebugDraw() const
{
    DrawBoundingBox();
    for (Component* component : components)
    {
        component->DebugDraw();
    }
}

void Hachiko::GameObject::DrawBoundingBox() const
{
    ddVec3 p[8];
    // This order was pure trial and error, i dont know how to really do it
    // Using center and points does not show the rotation
    static const int order[8] = {0, 1, 5, 4, 2, 3, 7, 6};
    for (int i = 0; i < 8; ++i)
    {
        p[i] = obb.CornerPoint(order[i]);
    }
    dd::box(p, dd::colors::White);
}

void Hachiko::GameObject::UpdateBoundingBoxes()
{
    ComponentMesh* component_mesh = GetComponent<ComponentMesh>();
    if (component_mesh != nullptr)
    {
        for (int i = 0; i < component_mesh->GetMeshesCount(); ++i)
        {
            obb = component_mesh->GetAABB(i);
            obb.Transform(transform->GetMatrix());
            // Enclose is accumulative, reset the box
            aabb.SetNegativeInfinity();
            aabb.Enclose(obb);
        }
    }
    else
    {
        constexpr float default_bounding_size = 1.0f;
        // If there is no mesh generate a default size
        aabb.SetNegativeInfinity();
        aabb.SetFromCenterAndSize(transform->GetGlobalPosition(), float3(default_bounding_size));
        obb = aabb;
    }

    // Without the check main camera crashes bcs there is no quadtree
    if (scene_owner)
    {
        const Quadtree* quadtree = scene_owner->GetQuadtree();
        quadtree->Remove(this);
        quadtree->Insert(this);
    }
}

bool Hachiko::GameObject::AttemptRemoveComponent(Component* component)
{
    //TODO: Should I delete the component?
    if (component->CanBeRemoved())
    {
        components.erase(std::remove(components.begin(), components.end(), component));
        return true;
    }
    return false;
}

void Hachiko::GameObject::Save(YAML::Node& node) const
{
    node[GAME_OBJECT_ID] = uid;
    node[GAME_OBJECT_NAME] = name.c_str();
    node[GAME_OBJECT_ENABLED] = active;
    node[GAME_OBJECT_PARENT_ID] = parent != nullptr ? parent->uid : 0;

    
    for (unsigned i = 0; i < components.size(); ++i)
    {
        node[COMPONENT_NODE][i][COMPONENT_ID] = (size_t)components[i]->GetID();
        node[COMPONENT_NODE][i][COMPONENT_TYPE] = (int)components[i]->GetType();
        node[COMPONENT_NODE][i][COMPONENT_ENABLED] = components[i]->IsActive();
        components[i]->Save(node[COMPONENT_NODE][i]);
    }

    for (unsigned i = 0; i < children.size(); ++i)
    {
        children[i]->Save(node[CHILD_NODE][i]);
    }
}

void Hachiko::GameObject::Load(const YAML::Node& node)
{
    const YAML::Node components_node = node[COMPONENT_NODE];
    for (unsigned i = 0; i < components_node.size(); ++i)
    {

        UID c_uid = components_node[i][COMPONENT_ID].as<unsigned long long>();
        bool active = components_node[i][COMPONENT_ENABLED].as<bool>();
        const auto type = static_cast<Component::Type>(components_node[i][COMPONENT_TYPE].as<int>());

        Component* component = CreateComponent(type);
        component->SetID(c_uid);
        component->Load(components_node[i]);
        active ? component->Enable() : component->Disable();
    }

    const YAML::Node childs_node = node[CHILD_NODE];
    if (!childs_node.IsDefined())
    {
        return;
    }
    for (unsigned i = 0; i < childs_node.size(); ++i)
    {
        std::string child_name = childs_node[i][GAME_OBJECT_NAME].as<std::string>();
        UID child_uid = childs_node[i][GAME_OBJECT_ID].as<unsigned long long>();
        const auto child = new GameObject(this, child_name.c_str(), child_uid);
        child->scene_owner = scene_owner;
        child->Load(childs_node[i]);
    }
}
