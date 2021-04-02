#ifndef BWATENGINE_EDITORINTERFACE_HPP
#define BWATENGINE_EDITORINTERFACE_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class  EditorInterface
{
public:
    unsigned int fbo;
    unsigned int tex;
    unsigned int rbo;

    EditorInterface();

    void InitImGui(GLFWwindow* window);
    void CreateFrame();
    void RenderImGui();
    void DrawInterface(float color[3]);
    void DestroyImGui();
    static void MenuFile();
    static void MainMenuBar();
    static void MenuOption();
};




#endif //BWATENGINE_EDITORINTERFACE_HPP
