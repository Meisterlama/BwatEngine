#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../../Engine/include/Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class  EditorInterface
{
public:
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
    unsigned int rbo;
};




#endif //BWATENGINE_EDITORINTERFACE_HPP
