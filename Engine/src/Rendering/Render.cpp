#include "Rendering/Render.hpp"

using namespace Rendering;

Render::Render()
{
    Shader sh("Assets/basic.vs", "Assets/multilight.fs");
    myShaderLight = sh;

    Model m((std::string)"Assets/bag/backpack.obj");
    myModel = &m;

    Rendering::Light mylight(Rendering::TYPE_LIGHT::Point, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f }, { 0.1f,0.1f,0.5f });
    lights.push_back(&mylight);
}

void Render::RenderScene()
{
    glEnable(GL_DEPTH_TEST);
    //glViewport(0, 0, mainWindow.GetWidth(), mainWindow.GetHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera
    //cam.UseFreeFly(&mainWindow, deltaTime);

    // projection, view and model
    BMath::Matrix4<float> projection = BMath::Matrix4<float>::CreatePerspective(60.f, mainWindow.GetWidth() / mainWindow.GetHeight(), 0.1f, 100.0f);
    BMath::Matrix4<float> view = cam.GetViewMatrix();
    BMath::Matrix4<float> model = BMath::Matrix4<float>::CreateScaleMat(1.f);

    //use shader
    myShaderLight.use();
    myShaderLight.setMat4("proj", projection);
    myShaderLight.setMat4("model", model);
    myShaderLight.setMat4("view", view);
    myShaderLight.setVec3("viewPos", cam.cameraPos.X, cam.cameraPos.Y, cam.cameraPos.Z);

    //myTri.Update();
    myModel->Draw(myShaderLight,lights);
}

