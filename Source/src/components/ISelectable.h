#pragma once

namespace Hachiko
{
    class HACHIKO_API ISelectable
    {
    public:
        virtual ~ISelectable() {}
        void OnPointerEnter() {
            hovered = true;
        }
        void OnPointerExit()
        {
            hovered = false;
        }
        void OnSelect()
        {
            selected = true;
        }
        void OnUnSelect()
        {
            selected = false;
        }
        virtual void Activate() = 0;
        

        [[nodiscard]] bool IsSelected() const
        {
            return selected;
        }

        [[nodiscard]] bool IsHovered() const
        {
            return hovered;
        }

    protected:
        bool selected = false;
        bool hovered = false;
    };
} // namespace Hachiko