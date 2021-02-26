#include "Widget.hpp"
#include "EditorInterface.hpp"
#include "imgui_internal.h"

Widget::Widget(EditorInterface* edit)
{
    editor = edit;
    window = nullptr;
};

void Widget::TickAlways()
{

}

void Widget::TickVisible()
{

}

void Widget::OnShow()
{

}

void Widget::OnHide()
{

}

void Widget::OnPushStyleVar()
{

}

void Widget::Tick()
{
    TickAlways();

    if (!isWindow)
        return;

    bool begun = false;
    {
        if (!isVisible)
            return;

        if (ImGui::Begin(title.c_str(), &isVisible, flags))
        {
            window = ImGui::GetCurrentWindow();
            height = ImGui::GetWindowHeight();
            begun = true;
        }
        else if (window && window->Hidden)
            begun = true;

        if (window && window->Appearing)
        {
            OnShow();
        }
        else if (!isVisible)
        {
            OnHide();
        }
    }

    if (begun)
    {
        TickVisible();

        ImGui::End();
    }
}


