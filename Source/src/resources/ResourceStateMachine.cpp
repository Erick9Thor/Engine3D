#include "core/hepch.h"
#include "ResourceStateMachine.h"
#include "modules/ModuleResources.h"
#include "ResourceAnimation.h"

void Hachiko::ResourceStateMachine::RemoveTransition(unsigned int index) 
{
    transitions.erase(transitions.begin() + index);
}

Hachiko::ResourceStateMachine::ResourceStateMachine(UID uid) : Resource(uid, Resource::Type::STATE_MACHINE)
{}

Hachiko::ResourceStateMachine::~ResourceStateMachine() {}

void Hachiko::ResourceStateMachine::AddClip(const std::string& name, UID animation, bool loop)
{
    clips.push_back(Clip(name, animation, loop));
}

int Hachiko::ResourceStateMachine::FindClip(const std::string& name) const
{
    int index = 0;
    for (index; index < clips.size(); ++index)
    {
        if (clips[index].name == name)
        {
            break;
        }
    }
    return index;
}

void Hachiko::ResourceStateMachine::RemoveClip(const std::string& name)
{
    int index = FindClip(name);
    if (index != clips.size())
    {
        // RemoveState?
        clips.erase(clips.begin() + index);
    }
}

void Hachiko::ResourceStateMachine::RemoveClip(unsigned int index)
{
    std::vector<Node>::iterator it = nodes.begin();

    while (it != nodes.end())
    {
        if (it->clip == clips[index].name)
        {
            RemoveNodeTransitions(it->name);
            it = nodes.erase(it);
        }
        else
        {
            ++it;
        }
    }

    clips.erase(clips.begin() + index);
}

void Hachiko::ResourceStateMachine::RemoveNodeTransitions(std::string& name)
{
    std::vector<Transition>::iterator it = transitions.begin();

    while (it != transitions.end())
    {
        if (it->source == name || it->target == name)
        {
            it = transitions.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Hachiko::ResourceStateMachine::EditClipLoop(const std::string& name, bool newLoop) 
{
    int index = FindClip(name);
    clips[index].loop = newLoop;
}

void Hachiko::ResourceStateMachine::SetClipRes(unsigned int index, UID uid)
{
    App->resources->ReleaseResource(clips[index].animation);
    clips[index].animation = static_cast<ResourceAnimation*>(App->resources->GetResource(Resource::Type::ANIMATION, uid));
}

void Hachiko::ResourceStateMachine::AddNode(const std::string& name, const std::string& clip)
{
    nodes.push_back(Node(name, clip));
}

int Hachiko::ResourceStateMachine::FindNode(const std::string& name) const 
{
    int index = 0;
    for (index; index < nodes.size(); ++index)
    {
        if (nodes[index].name == name)
        {
            break;
        }
    }
    return index;
}

std::vector<int> Hachiko::ResourceStateMachine::FindNodeTransitions(const std::string& name) const
{
    std::vector<int> stateTransitionsIndex;
    for (int i = 0; i < transitions.size(); ++i)
    {
        if (transitions[i].source == name || transitions[i].target == name)
        {
            stateTransitionsIndex.push_back(i);
        }
    }
    return stateTransitionsIndex;
}

void Hachiko::ResourceStateMachine::RemoveNode(const std::string& name)
{
    int index = FindNode(name);
    if (index != nodes.size())
    {
        std::vector<int> stateTransitionsIndex = FindNodeTransitions(name);
        for (int i = stateTransitionsIndex.size() - 1; i >= 0; --i)
        {
            transitions.erase(transitions.begin() + stateTransitionsIndex[i]);
        }
        nodes.erase(nodes.begin() + index);
    }
}

void Hachiko::ResourceStateMachine::EditNodeClip(const std::string& name, const std::string& newClip)
{
    int index = FindNode(name);
    nodes[index].clip = newClip;
}

void Hachiko::ResourceStateMachine::AddTransition(const std::string& source, const std::string& target, const std::string& trigger, unsigned int blend)
{
    transitions.push_back(Transition(source, target, trigger, blend));
}

int Hachiko::ResourceStateMachine::FindTransitionWithTrigger(const std::string& source, const std::string& trigger) const
{
    int index = 0;
    for (index; index < transitions.size(); ++index)
    {
        if (transitions[index].source == source && transitions[index].trigger == trigger)
        {
            break;
        }
    }
    return index;
}

int Hachiko::ResourceStateMachine::FindTransitionWithTarget(const std::string& source, const std::string& target) const
{
    int index = 0;
    for (index; index < transitions.size(); ++index)
    {
        if (transitions[index].source == source && transitions[index].target == target)
        {
            break;
        }
    }
    return index;
}

std::vector<Hachiko::ResourceStateMachine::Transition> Hachiko::ResourceStateMachine::FindTransitionsFromNode(const std::string& name) const
{
    std::vector<Hachiko::ResourceStateMachine::Transition> transitionsFromState;
    for (int i = 0; i < transitions.size(); ++i)
    {
        if (transitions[i].source == name)
        {
            Transition t = transitions[i];
            transitionsFromState.push_back(t);
        }
    }
    return transitionsFromState;
}

void Hachiko::ResourceStateMachine::RemoveTransitionWithTrigger(const std::string& source, const std::string& trigger)
{
    int index = FindTransitionWithTrigger(source, trigger);
    if (index != transitions.size())
    {
        transitions.erase(transitions.begin() + index);
    }
}

void Hachiko::ResourceStateMachine::RemoveTransitionWithTarget(const std::string& source, const std::string& target)
{
    int index = FindTransitionWithTarget(source, target);
    if (index != transitions.size())
    {
        transitions.erase(transitions.begin() + index);
    }
}

void Hachiko::ResourceStateMachine::EditTransitionSource(const std::string& newSource, const std::string& target, const std::string& trigger)
{
    int index = 0;
    for (index; index < transitions.size(); ++index)
    {
        if (transitions[index].target == target && transitions[index].trigger == trigger)
        {
            break;
        }
    }
    transitions[index].source = newSource;
}

void Hachiko::ResourceStateMachine::EditTransitionTarget(const std::string& source, const std::string& newTarget, const std::string& trigger)
{
    int index = 0;
    for (index; index < transitions.size(); ++index)
    {
        if (transitions[index].source == source && transitions[index].trigger == trigger)
        {
            break;
        }
    }
    transitions[index].target = newTarget;
}

void Hachiko::ResourceStateMachine::EditTransitionTrigger(const std::string& source, const std::string& target, const std::string& newTrigger)
{
    int index = 0;
    for (index; index < transitions.size(); ++index)
    {
        if (transitions[index].source == source && transitions[index].target == target)
        {
            break;
        }
    }
    transitions[index].trigger = newTrigger;
}

void Hachiko::ResourceStateMachine::EditTransitionInterpolationTime(const std::string& source, const std::string& target, unsigned int newInterpolationTime)
{
    int index = FindTransitionWithTarget(source, target);
    transitions[index].blend = newInterpolationTime;
}

Hachiko::ResourceStateMachine::Clip::Clip(const std::string& name, UID animation_id, bool loop) : name(name), loop(loop)
{
    animation = static_cast<ResourceAnimation*>(App->resources->GetResource(Resource::Type::ANIMATION, animation_id));
};
