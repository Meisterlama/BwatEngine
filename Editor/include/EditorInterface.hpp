#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "Widget.hpp"
#include "Window.hpp"

namespace BwatEngine
{
    class Engine;
}

class  EditorInterface
{
public:
    EditorInterface(BwatEngine::Engine* _engine);
    ~EditorInterface(){};

    void OnTick();
    void Initialise();
    void DestroyImGui();

    BwatEngine::Engine* engine = nullptr;

private:
    void ApplyStyle() const;
    void BeginWindow();

    std::vector<std::unique_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;

};




#endif //BWATENGINE_EDITORINTERFACE_HPP

