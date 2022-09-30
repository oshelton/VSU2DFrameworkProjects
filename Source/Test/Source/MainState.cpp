#include <InputManager.h>
#include <SystemManager.h>
#include <CEGUIEventArgs.h>
#include <CEGUI.h>
#include "GuiManager.h"
#include "MainState.h"

using namespace CEGUI;

bool quitButtonPushed(const EventArgs& e)
{
    SystemManager::get()->quitNextUpdate();
    return true;
}

bool sceneGraphButtonPushed(const EventArgs& e)
{
    SystemManager::get()->changeStateNextUpdate("SceneGraphTest");
    return true;
}

bool cameraButtonPushed(const EventArgs& e)
{
    SystemManager::get()->changeStateNextUpdate("CameraTest");
    return true;
}

bool renderButtonPushed(const EventArgs &e)
{
    SystemManager::get()->changeStateNextUpdate("RenderTest");
    return true;
}

void MainState::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\main_menu.layout");
    gui->getButton("quitButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&quitButtonPushed));
    gui->getButton("sceneGraphButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&sceneGraphButtonPushed));
    gui->getButton("cameraButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&cameraButtonPushed));
    gui->getButton("renderingButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&renderButtonPushed));
}

void MainState::clear()
{
    GuiManager::get()->clear();
}

void MainState::FrameFunc()
{
}
