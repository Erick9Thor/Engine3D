#pragma once

#include "core/preferences/Preferences.h"

namespace Hachiko
{
    class GlobalPreferences final : public Preferences
    {
    public:
        GlobalPreferences();
        ~GlobalPreferences() override = default;
        void SetConfigurationData(const YAML::Node& node) override;
        void GetConfigurationData(YAML::Node& node) override;

    private:
        std::string title = "Hachiko Engine";
        std::string version = "v1.0.0";
    };
}
