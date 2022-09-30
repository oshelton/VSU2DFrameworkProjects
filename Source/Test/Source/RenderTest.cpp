#include <InputManager.h>
#include <SystemManager.h>
#include <CEGUIEventArgs.h>
#include <hge.h>
#include <CEGUI.h>
#include <hgevector.h>
#include <hgecolor.h>
#include <SceneManager.h>
#include <SceneNode.h>
#include <SimpleRenderable.h>
#include <TextRenderable.h>
#include <LineRenderable.h>
#include <TriangleRenderable.h>
#include <CompoundRenderable.h>
#include <ScriptManager.h>
#include <hgeresource.h>
#include <Camera.h>
#include <Utils.h>
#include <GuiManager.h>
#include <InputManager.h>
#include <GuiManager.h>
#include "main.h"
#include "RenderTest.h"

using namespace CEGUI;

void RenderTest::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\test_layout.layout");
    gui->getButton("mainMenuButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&homeButtonPushed));
    gui->getWindow("infoText")->setText("Arrow keys animate the background texture.");

    ScriptManager::get()->loadResourceScript("../resources/data/advanced_sprites.res");
    ScriptManager::get()->loadResourceScript("../resources/data/fonts.res");
    ScriptManager::get()->loadResourceScript("../resources/data/textures.res");

    SceneManager* scene = SceneManager::get();

    background = scene->getRootSceneNode()->createChildSceneNode("background");
    background->setZ(1.0);
    SimpleRenderable* back = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "background"));
    back->setSprite("background");
    back->getTextureCoords(&u, &v, &width, &height);
    background->attachComponent(back);
    background->setScale(1.55);

    SceneNode* node = scene->getRootSceneNode()->createChildSceneNode("tri1");
    node->setPosition(hgeVector(-128, 200));
    node->setZ(0.5);

    SimpleRenderable* renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triAddRed"));
    renderable->setSprite("triAddRed");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("tri2");
    node->setPosition(hgeVector(0, 200));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triAddGreen"));
    renderable->setSprite("triAddGreen");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("tri3");
    node->setPosition(hgeVector(128, 200));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triAddBlue"));
    renderable->setSprite("triAddBlue");
    node->attachComponent(renderable);


    node = scene->getRootSceneNode()->createChildSceneNode("tri4");
    node->setPosition(hgeVector(-128, 100));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triMulRed"));
    renderable->setSprite("triMulRed");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("tri5");
    node->setPosition(hgeVector(0, 100));

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triMulGreen"));
    renderable->setSprite("triMulGreen");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("tri6");
    node->setPosition(hgeVector(128, 100));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triMulBlue"));
    renderable->setSprite("triMulBlue");
    node->attachComponent(renderable);


    node = scene->getRootSceneNode()->createChildSceneNode("tri7");
    node->setPosition(hgeVector(-64, 0));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triAlphaAdd"));
    renderable->setSprite("triAlphaAdd");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("tri8");
    node->setPosition(hgeVector(64, 0));
    node->setZ(0.5);

    renderable = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "triAlphaBlend"));
    renderable->setSprite("triAlphaBlend");
    node->attachComponent(renderable);

    node = scene->getRootSceneNode()->createChildSceneNode("text1");
    TextRenderable* text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text1"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("Additive Blending.");
    node->attachComponent(text);
    node->setPosition(hgeVector(0, 160));

    node = scene->getRootSceneNode()->createChildSceneNode("text2");
    text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text2"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("Multiplicative Blending (tinting, default).");
    node->attachComponent(text);
    node->setPosition(hgeVector(0, 60));

    node = scene->getRootSceneNode()->createChildSceneNode("text3");
    text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text3"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("Additive and blend Alpha modes (blend default).");
    node->attachComponent(text);
    node->setPosition(hgeVector(0, -40));

    node = scene->getRootSceneNode()->createChildSceneNode("line1");
    LineRenderable* line = static_cast<LineRenderable*>(scene->createComponent("LineRenderable", "line"));
    line->addLine(hgeVector(-50, -50), hgeVector(-50, 50), hgeColor(1, 0, 0, 0.5));
    line->addLine(hgeVector(-50, -50), hgeVector(50, -50), hgeColor(0, 1, 0, 0.7));
    line->addLine(hgeVector(-50, 50), hgeVector(50, 50), hgeColor(0, 0, 1, 0.5));
    line->addLine(hgeVector(50, 50), hgeVector(50, -50), hgeColor(1, 1, 0, 1));
    node->setPosition(hgeVector(-200, -150));
    node->attachComponent(line);

    node = scene->getRootSceneNode()->createChildSceneNode("text4");
    text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text4"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("Line rendering.");
    node->attachComponent(text);
    node->setPosition(hgeVector(-200, -240));

    node = scene->getRootSceneNode()->createChildSceneNode("triangle");
    TriangleRenderable* tri = static_cast<TriangleRenderable*>(scene->createComponent("TriangleRenderable", "triangle"));
    tri->addTriangle(hgeVector(-50, -50), hgeVector(-50, 50), hgeVector(50, -50),
                     hgeVector(0, 0), hgeVector(0, 0), hgeVector(0, 0),
                     hgeColor(1, 0, 0, 0.5), hgeColor(0, 1, 0, 0.7), hgeColor(0, 0, 1, 1));
    tri->addTriangle(hgeVector(-50, 50), hgeVector(50, 50), hgeVector(50, -50),
                     hgeVector(0, 0), hgeVector(.5, 0), hgeVector(.5, .5),
                     hgeColor(1, 1, 0, 0.5), hgeColor(0, 1, 1, 0.7), hgeColor(1, 0, 0, 1),
                     "tri");
    node->attachComponent(tri);
    node->setPosition(hgeVector(200, -150));

    node = scene->getRootSceneNode()->createChildSceneNode("text5");
    text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text5"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("Triangle rendering.");
    node->attachComponent(text);
    node->setPosition(hgeVector(200, -240));

    node = scene->getRootSceneNode()->createChildSceneNode("compound");
    CompoundRenderable* compound = static_cast<CompoundRenderable*>(scene->createComponent("CompoundRenderable", "compound"));
    compound->addRenderable(line);
    compound->addRenderable(tri);
    node->attachComponent(compound);
    node->setPosition(hgeVector(0, -150));

    node = scene->getRootSceneNode()->createChildSceneNode("text6");
    text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "text6"));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setText("CompoundRenderable.");
    node->attachComponent(text);
    node->setPosition(hgeVector(0, -240));
}

void RenderTest::clear()
{
    GuiManager::get()->clear();
    SceneManager::get()->clearScene();
    ScriptManager::get()->getResourceManager()->Purge();
}

void RenderTest::FrameFunc()
{
    InputManager* input = InputManager::get();

    SimpleRenderable* renderable = static_cast<SimpleRenderable*>(background->getComponent());

    if (input->getKey() == HGEK_LEFT)
    {
        u -= 20 * Utils::get()->getDTime();
        renderable->setTextureCoords(u, v, width, height);
    }
    else if (input->getKey() == HGEK_RIGHT)
    {
        u += 20 * Utils::get()->getDTime();
        renderable->setTextureCoords(u, v, width, height);
    }
    else if (input->getKey() == HGEK_UP)
    {
        v -= 20 * Utils::get()->getDTime();
        renderable->setTextureCoords(u, v, width, height);
    }
    else if (input->getKey() == HGEK_DOWN)
    {
        v += 20 * Utils::get()->getDTime();
        renderable->setTextureCoords(u, v, width, height);
    }

    SceneManager::get()->getSceneNode("line1")->rotate(5 * Utils::get()->getDTime());
    SceneManager::get()->getSceneNode("triangle")->rotate(5 * Utils::get()->getDTime());
}
