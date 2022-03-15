#pragma once

namespace Hachiko
{
    class Scene;
    class GameObject;
    class Component;

    class SceneSerializer
    {
        friend ModuleSceneManager;

    public:
        SceneSerializer() = default;
        ~SceneSerializer() = default;

        bool Save(const Scene* scene);
    private:
        // Load is private to ensure only ModuleScene can call it 
        // as we retrieve ownership of scene object pointer
        Scene* Load(const char* path);
        static void ImportFromAssets(const char* path, Resource::Type type);
        bool CheckIfImported(const char* path) const;
        ResourcesPreferences* preferences;
    };
}