#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <vector>
#include <memory>

#include "../../Engine/include/Window.hpp"
#include "Widget.hpp"


class  EditorInterface
{
public:
    EditorInterface() = default;
    ~EditorInterface();

    void OnTick();

private:
    void Initialise(Bwat::Window mainWindow);
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

void InitImGui(Bwat::Window mainWindow);
void CreateFrame();
void RenderImGui();
void ShowScene(float color[3]);
void DrawInterface(float color[3]);
void DestroyImGui();
static void MenuFile();
static void MainMenuBar();
static void MenuOption();

private:
unsigned int fbo;
unsigned int tex;
unsigned int rbo;*/
