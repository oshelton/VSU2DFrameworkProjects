/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#include <ScriptManager.h>
#include <GuiManager.h>
#include <SystemManager.h>
#include <InputManager.h>
#include <CEGUI.h>
#include <CEGUIEventArgs.h>
#include <hgevector.h>
#include <Utils.h>
#include "AlgorithmRunner.h"
#include "PointShape.h"
#include "TriangleShape.h"
#include "CyclicVector.h"
#include "AlgorithmState.h"

using namespace std;
using namespace CEGUI;

AlgorithmState* AlgorithmState::state(NULL);

bool resetButtonPushed(const EventArgs& e)
{
    AlgorithmState::get()->reset();
    return true;
}

bool calculateButtonPushed(const EventArgs& e)
{
    if (AlgorithmState::get()->canConvert())
    {
        AlgorithmState::get()->performConversion();
        GuiManager::get()->getCheckbox("editBox")->setSelected(false);
    }
}

bool quitButtonPushed(const EventArgs& e)
{
    SystemManager::get()->quitNextUpdate();
    return true;
}

AlgorithmState::AlgorithmState() : mouseDown(false)
{
    runner = new AlgorithmRunner();
}

AlgorithmState::~AlgorithmState()
{
    delete runner;
}

void AlgorithmState::reset()
{
    outline->clearPoints();
    triangles1->clearTriangles();
    triangles2->clearTriangles();
}

void AlgorithmState::performConversion()
{
    runner->convertShape(outline, triangles1, triangles2);
}

bool AlgorithmState::canConvert()
{
    return outline->isConvertable();
}

bool AlgorithmState::mouseInsideWindow()
{
    hgeVector mousePosition = InputManager::get()->getMousePosition();
    if (GuiManager::get()->getWindow("controlWindow")->isHit(Vector2(mousePosition.x, mousePosition.y)))
        return true;
    else
        return false;
}

void AlgorithmState::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\algorithm.layout");
    gui->getButton("resetButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&resetButtonPushed));
    gui->getButton("calculateButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&calculateButtonPushed));
    gui->getButton("quitButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&quitButtonPushed));

    ScriptManager::get()->loadResourceScript("../resources/data/fonts.res");

    outline = new PointShape();
    triangles1 = new TriangleShape("Triangles 1");
    triangles1->hide();
    triangles2 = new TriangleShape("Triangles 2");

    outline->addPoint(hgeVector(-100, 100));
    outline->addPoint(hgeVector(0, 0));
    outline->addPoint(hgeVector(100, 100));
    outline->addPoint(hgeVector(125, -100));
    outline->addPoint(hgeVector(-125, -100));
    outline->finalize();
}

void AlgorithmState::clear()
{
    delete outline;
    delete triangles1;
    delete triangles2;
}

void AlgorithmState::FrameFunc()
{
    if (GuiManager::get()->getCheckbox("originalOutput")->isSelected())
        triangles1->show();
    else
        triangles1->hide();

    if (GuiManager::get()->getCheckbox("optomizedOutput")->isSelected())
        triangles2->show();
    else
        triangles2->hide();

    if (InputManager::get()->getKeyState(HGEK_LBUTTON) && !mouseDown && GuiManager::get()->getCheckbox("editBox")->isSelected()
        && !outline->isConvertable() && !mouseInsideWindow())
    {
        mouseDown = true;
        hgeVector mousePosition = InputManager::get()->getMousePosition();
        mousePosition.x -= 400;
        mousePosition.y -= 300;
        mousePosition.y *= -1;

        CyclicVector<hgeVector> points = outline->getPoints();

        Utils* utils = Utils::get();

        if (points.size() > 0)
        {
            bool valid = true;
            for (int i = 1; i < points.size(); ++i)
            {
                if (utils->distanceBetween(mousePosition, points[i]) < 20)
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
            {
                if (utils->distanceBetween(mousePosition, points[0]) < 20)
                    outline->finalize();
                else
                    outline->addPoint(mousePosition);
            }
        }
        else
            outline->addPoint(mousePosition);
    }
    else if (!InputManager::get()->getKeyState(HGEK_LBUTTON))
        mouseDown = false;
}
