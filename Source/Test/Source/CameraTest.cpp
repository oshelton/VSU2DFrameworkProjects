#include <InputManager.h>
#include <SystemManager.h>
#include <CEGUIEventArgs.h>
#include <CEGUI.h>
#include <hgevector.h>
#include <SceneManager.h>
#include <SceneNode.h>
#include <SimpleRenderable.h>
#include <ScriptManager.h>
#include <hgeresource.h>
#include <Camera.h>
#include <Utils.h>
#include <GuiManager.h>
#include <InputManager.h>
#include <GuiManager.h>
#include "Utils.h"
#include "main.h"
#include "CameraTest.h"

using namespace CEGUI;
using namespace std;

void CameraTest::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\test_layout.layout");
    gui->getButton("mainMenuButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&homeButtonPushed));
    gui->getWindow("infoText")->setText("Arrow keys move the camera.");

    ScriptManager::get()->loadResourceScript("../resources/data/basic_sprites.res");

    SceneManager* scene = SceneManager::get();

    camNode = scene->getRootSceneNode()->createChildSceneNode("Camera Node");
    camNode->attachComponent(scene->getCamera());
    camNode->setRotation(90);

    sun = scene->getRootSceneNode()->createChildSceneNode("sun");

    SimpleRenderable* renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "sun"));
    renderable->setSprite("yellowSprite");

    sun->attachComponent(renderable);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "planet"));
    renderable->setSprite("redSprite");

    planet1 = sun->createChildSceneNode("planet1");
    planet1->attachComponent(renderable);
    planet1->setPosition(hgeVector(300, 0));

    planet2 = sun->createChildSceneNode("planet2");
    planet2->attachComponent(renderable);
    planet2->setPosition(hgeVector(0, 200));

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "moon"));
    renderable->setSprite("blueSprite");
    scene->registerRenderableListener(renderable);

    moon1 = planet1->createChildSceneNode("moon1");
    moon1->attachComponent(renderable);
    moon1->setInheritRotation(false);
    moon1->setPosition(hgeVector(-50, 0));

    moon2 = planet1->createChildSceneNode("moon2");
    moon2->attachComponent(renderable);
    moon2->setPosition(hgeVector(50, 0));
}

void CameraTest::clear()
{
    GuiManager::get()->clear();
    SceneManager::get()->clearScene();
    ScriptManager::get()->getResourceManager()->Purge();
}

void CameraTest::FrameFunc()
{
    sun->rotate(7 * Utils::get()->getDTime());
    planet1->rotate(12 * Utils::get()->getDTime());
    planet2->rotate(8 * Utils::get()->getDTime());

    if (InputManager::get()->getKey() == HGEK_LEFT)
        camNode->translate(hgeVector(-80, 0) * Utils::get()->getDTime());
    else if (InputManager::get()->getKey() == HGEK_RIGHT)
        camNode->translate(hgeVector(80, 0) * Utils::get()->getDTime());
    else if (InputManager::get()->getKey() == HGEK_UP)
        camNode->translate(hgeVector(0, 80) * Utils::get()->getDTime());
    else if (InputManager::get()->getKey() == HGEK_DOWN)
        camNode->translate(hgeVector(0, -80) * Utils::get()->getDTime());
}
