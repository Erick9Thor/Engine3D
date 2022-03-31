#pragma once

#include <any>
#include <string>

namespace Hachiko::Scripting
{
class SerializedField
{
public:
    explicit SerializedField();
    explicit SerializedField(std::string name, std::any copy, 
        std::string type_name);
    ~SerializedField() = default;

public:
    std::string name;
    std::string type_name;
    std::any copy;
};
} // namespace Hachiko::Scripting