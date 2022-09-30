/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <list>
#include <map>
#include <Utils.h>
#include <SystemManager.h>
#include <CEGUIEventArgs.h>
#include <CEGUI.h>
#include <SceneManager.h>
#include <GuiManager.h>
#include "Environment.h"
#include "SimulationManager.h"
#include "SimulationState.h"

using namespace std;
using namespace CEGUI;

void setupItem(ListboxTextItem* item)
{
    item->setSelectionBrushImage((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"ListboxSelectionBrush");
    item->setSelectionColours(colour(1.0, 0, 0, 1.0));
    item->setAutoDeleted(true);
}

bool quitButtonPushed(const EventArgs& e)
{
    SimulationManager::get()->stop();
    SystemManager::get()->quitNextUpdate();
    return true;
}

bool environmentChanged(const EventArgs& e)
{
    list<string> simulations = SimulationManager::get()->getEnvironment(
                               string(GuiManager::get()->getCombobox("environmentSelector")->getSelectedItem()->getText().c_str())
                               )->getFileNames();
    Listbox* box = GuiManager::get()->getListbox("simulations");
    box->resetList();

    list<string>::const_iterator iter;

    for (iter = simulations.begin(); iter != simulations.end(); ++iter)
    {
        ListboxTextItem* item = new ListboxTextItem(*iter);
        setupItem(item);
        box->addItem(item);
    }

    return true;
}

bool loadButtonPushed(const EventArgs& e)
{
    Listbox* box = GuiManager::get()->getListbox("simulations");
    if (box->getFirstSelectedItem() != NULL)
    {
        SimulationManager::get()->setActiveEnvironment(string(GuiManager::get()->getCombobox("environmentSelector")->getSelectedItem()->getText().c_str()));
        SimulationManager::get()->getActiveEnvironment()->loadSimulation(string(box->getFirstSelectedItem()->getText().c_str()));
    }
    return true;
}

bool pauseButtonPushed(const EventArgs& e)
{
    if (SimulationManager::get()->isActive())
    {
        if (SimulationManager::get()->isPaused())
        {
            GuiManager::get()->getButton("pauseButton")->setText("Pause");
            SimulationManager::get()->unpause();
        }
        else
        {
            GuiManager::get()->getButton("pauseButton")->setText("Resume");
            SimulationManager::get()->pause();
        }
    }
    return true;
}

bool setTimeButtonPushed(const EventArgs& e)
{
    Combobox* selector = GuiManager::get()->getCombobox("timeFactors");
    if (selector->getText() != "")
    {
        double enteredFactor = Utils::get()->stringToDouble(selector->getText().c_str());

        if (!enteredFactor > 0)
            enteredFactor = 1;

        SimulationManager::get()->setTimeFactor(enteredFactor);
    }

    return true;
}

SimulationState::SimulationState()
{
    manager = SimulationManager::get();
}

SimulationState::~SimulationState()
{
    delete manager;
}

void SimulationState::createScene()
{
    GuiManager* gui = GuiManager::get();
    gui->loadLayout("..\\resources\\gui\\layouts\\simulation.layout");

    gui->getButton("quitButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&quitButtonPushed));
    gui->getButton("loadButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&loadButtonPushed));
    gui->getButton("pauseButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&pauseButtonPushed));
    gui->getButton("setTimeFactorButton")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&setTimeButtonPushed));

    Combobox* selector = gui->getCombobox("environmentSelector");
    selector->setReadOnly(true);

    map<string, Environment*> environments = manager->getEnvironments();
    map<string, Environment*>::const_iterator iter1;

    for (iter1 = environments.begin(); iter1 != environments.end(); ++iter1)
    {
        ListboxTextItem* item = new ListboxTextItem(iter1->second->getType());
        setupItem(item);
        selector->addItem(item);
    }

    selector->subscribeEvent(Combobox::EventListSelectionAccepted, Event::Subscriber(&environmentChanged));

    selector = gui->getCombobox("timeFactors");
    selector->setReadOnly(true);

    ListboxTextItem* item = new ListboxTextItem(".25");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem(".5");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem("1");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem("2");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem("5");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem("10");
    setupItem(item);

    selector->addItem(item);

    item = new ListboxTextItem("20");
    setupItem(item);

    selector->addItem(item);

    manager->start();
}

void SimulationState::clear()
{
    manager->stop();
    SceneManager::get()->clearScene();
    GuiManager::get()->clear();
}

void SimulationState::FrameFunc()
{
    manager->update();
}
