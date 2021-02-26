#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "Rendering/Render.hpp"
#include "Widget.hpp"


class  EditorInterface
{
public:
    EditorInterface() = default;
    ~EditorInterface();

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

/*public:
EditorInterface();
~EditorInterface();

void ShowScene(float color[3]);
void DrawInterface(float color[3]);


private:
unsigned int fbo;
unsigned int tex;
unsigned int rbo;*/
