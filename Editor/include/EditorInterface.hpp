#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "Widget.hpp"
#include "Window.hpp"


class  EditorInterface
{
public:
    EditorInterface();
    ~EditorInterface(){};

    void OnTick();
    void Initialise(Bwat::Window mainWindow);
    void DestroyImGui();

private:
    void ApplyStyle() const;
    void BeginWindow();

    std::vector<std::shared_ptr<Widget>> widgets;
    bool initialised = false;
    bool editorBegun = false;

};




#endif //BWATENGINE_EDITORINTERFACE_HPP

