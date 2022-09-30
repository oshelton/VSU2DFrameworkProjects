#include <InputManager.h>
#include <SystemManager.h>
#include <CEGUI.h>
#include <hgevector.h>
#include <SceneManager.h>
#include <SceneNode.h>
#include <SimpleRenderable.h>
#include <ScriptManager.h>
#include <hgeresource.h>
#include <Camera.h>
#include <GuiManager.h>
#include <InputManager.h>
#include <GuiManager.h>
#include "Utils.h"
#include "main.h"
#include "SceneGraphTest.h"

using namespace CEGUI;
using namespace std;

void SceneGraphTest::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\test_layout.layout");
    gui->getButton("mainMenuButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&homeButtonPushed));
    gui->getWindow("infoText")->setText("Arrow keys move the sun, a and s rtate the sun, z and x scale it.");

    ScriptManager::get()->loadResourceScript("../resources/data/basic_sprites.res");

    SceneManager* scene = SceneManager::get();
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
    planet2->setInheritScale(false);

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

void SceneGraphTest::clear()
{
    GuiManager::get()->clear();
    SceneManager::get()->clearScene();
    ScriptManager::get()->getResourceManager()->Purge();
}

void SceneGraphTest::FrameFunc()
{
    InputManager* input = InputManager::get();

    if (InputManager::get()->getKey() == HGEK_LEFT)
        sun->translate(hgeVector(-20, 0) * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_RIGHT)
        sun->translate(hgeVector(20, 0) * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_UP)
        sun->translate(hgeVector(0, 20) * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_DOWN)
        sun->translate(hgeVector(0, -20) * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_A)
        sun->rotate(10 * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_S)
        sun->rotate(-10 * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_Z)
        sun->setScale(sun->getScale() + .1 * Utils::get()->getDTime());
    else if (input->getKey() == HGEK_X)
    {
        if (sun->getScale() > 0.3)
            sun->setScale(sun->getScale() - .1 * Utils::get()->getDTime());
    }
}
