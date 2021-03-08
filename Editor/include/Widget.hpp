#ifndef BWATENGINE_WIDGET_HPP
#define BWATENGINE_WIDGET_HPP

#include <imgui.h>
#include <string>


//Forward declaration
struct ImGuiWindow;
class EditorInterface;

class Widget
{
public:
    Widget(EditorInterface* editor);
    virtual ~Widget() = default;

    void Tick();

    virtual void TickAlways();      // Called always
    virtual void TickVisible();     // Called only when the widget is visible
    virtual void OnShow();          // Called when the window becomes visible
    virtual void OnHide();          // called when the window becomes invisible
    virtual void OnPushStyleVar();  // Called just before ImGui::Begin()

    //Properties
    float GetHeight()         const { return height; }
    ImGuiWindow* GetWindow()  const { return window; }
    bool& GetVisible()              { return isVisible; }
    void SetVisible(bool visible)   { isVisible = visible; }

protected:
    bool isWindow           = true;
    bool isVisible          = true;
    int flags               = ImGuiWindowFlags_NoCollapse;
    float height            = 0;
    EditorInterface* editor = nullptr;
    ImGuiWindow* window     = nullptr;
    std::string title       = "title";
};
#endif //BWATENGINE_WIDGET_HPP
