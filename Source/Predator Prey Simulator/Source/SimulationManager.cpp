/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <SceneManager.h>
#include <ScriptManager.h>
#include <TimerManager.h>
#include <SimpleRenderable.h>
#include <SceneNode.h>
#include <Camera.h>
#include <Utils.h>
#include <InputManager.h>
#include <ScriptManager.h>
#include <hgeresource.h>
#include "PreyManager.h"
#include "PredatorManager.h"
#include "Environment.h"
#include "PredatorBehaviorFamily.h"
#include "EnvironMents/TestEnvironment.h"
#include "EnvironMents/SwampEnvironment.h"
#include "BehaviorFamilies/GenericPredatorBehaviorFamily.h"
#include "BehaviorFamilies/GenericPreyBehaviorFamily.h"
#include "BehaviorFamilies/AggressivePredatorFamily.h"
#include "BehaviorFamilies/AlertPreyFamily.h"
#include "BehaviorFamilies/AmbushPredatorFamily.h"
#include "BehaviorFamilies/CarefulPreyFamily.h"
#include "BehaviorFamilies/DefensivePreyFamily.h"
#include "BehaviorFamilies/FelinePredatorFamily.h"
#include "PreyBehaviorFamily.h"
#include "SimulationBinder.h"
#include "ReportManager.h"
#include "SimulationManager.h"

using namespace std;

SimulationManager* SimulationManager::manager(NULL);

SimulationManager::SimulationManager() : currentEnvironment(NULL), paused(false), active(false), timeFactor(1.0), remainingTime(0)
{
    preyManager = new PreyManager();
    predatorManager = new PredatorManager();

    //Environment creation code goes here.
    environments["Test"] = new TestEnvironment();
    environments["Swamp"] = new SwampEnvironment();

    //Predator BehaviorFamily creation goes here.
    predatorFamilies["Generic"] = new GenericPredatorBehaviorFamily();
    predatorFamilies["Aggressive"] = new AggressivePredatorFamily();
    predatorFamilies["Ambush"] = new AmbushPredatorFamily();
    predatorFamilies["Feline"] = new FelinePredatorFamily();

    //Prey BehaviorFamily creation goes here.
    preyFamilies["Generic"] = new GenericPreyBehaviorFamily();
    preyFamilies["Alert"] = new AlertPreyFamily();
    preyFamilies["Careful"] = new CarefulPreyFamily();
    preyFamilies["Defensive"] = new DefensivePreyFamily();

    currentEnvironment = environments.begin()->second;
}

SimulationManager::~SimulationManager()
{
    delete preyManager;
    delete predatorManager;

    currentEnvironment = NULL;

    map<string, Environment*>::const_iterator iter;
    for (iter = environments.begin(); iter != environments.end(); ++iter)
        delete iter->second;

    map<string, PredatorBehaviorFamily*>::const_iterator iter2;
    for (iter2 = predatorFamilies.begin(); iter2 != predatorFamilies.end(); ++iter2)
        delete iter2->second;

    map<string, PreyBehaviorFamily*>::const_iterator iter3;
    for (iter3 = preyFamilies.begin(); iter3 != preyFamilies.end(); ++iter3)
        delete iter3->second;

    manager = NULL;
}

void SimulationManager::start()
{
    TimerManager::get()->createTimer("simulation", true);

    ScriptManager::get()->addBindings(new SimulationBinder());

    SceneManager* scene = SceneManager::get();

    cam = scene->getCamera();

    scene->createSceneNode("cam_node", hgeVector(0, 0))->attachComponent(cam);
    oldCameraPosition = cam->getCenter();

    scene->getSceneNode("cam_node")->createChildSceneNode("background_node");

    background = static_cast<SimpleRenderable*>(scene->createComponent("SimpleRenderable", "background"));
    background->setSprite(currentEnvironment->getBackgroundSpriteName());

    scene->getSceneNode("background_node")->attachComponent(background);
    scene->getSceneNode("background_node")->setZ(1.0);

    uvCoords.x = 0;
    uvCoords.y = 0;

    oldMousePosition = InputManager::get()->getMousePosition();

    ScriptManager::get()->getResourceManager()->LoadScript("../resources/data/Pointers.res");
}

void SimulationManager::stop()
{
    TimerManager::get()->destroyTimer("simulation");
    ScriptManager::get()->getResourceManager()->Purge(1);
}

Environment* SimulationManager::getActiveEnvironment()
{
    return currentEnvironment;
}

void SimulationManager::setActiveEnvironment(const string& environment)
{
    if (environments.find(environment) != environments.end())
    {
        currentEnvironment->clearEnvironment();
        currentEnvironment = environments[environment];
    }
    else
        Utils::get()->writeToLog("Unknown Environment name passed [" + environment + "].");
}

Environment* SimulationManager::getEnvironment(const string& type)
{
    if (environments.find(type) != environments.end())
        return environments[type];
    else
        Utils::get()->writeToLog("No Environment named [" + type + "] exists, returning NULL.");
    return NULL;
}

PredatorBehaviorFamily* SimulationManager::getPredatorBehaviorFamily(const string& name)
{
    if (predatorFamilies.find(name) != predatorFamilies.end())
        return predatorFamilies[name];
    else
        Utils::get()->writeToLog("No PredatorBehaviorFamily named [" + name + "] exists, returning NULL.");
    return NULL;
}

PreyBehaviorFamily* SimulationManager::getPreyBehaviorFamily(const string& name)
{
    if (preyFamilies.find(name) != preyFamilies.end())
        return preyFamilies[name];
    else
        Utils::get()->writeToLog("No PreyBehaviorFamily named [" + name + "] exists, returning NULL.");
    return NULL;
}

void SimulationManager::pause()
{
    if (active && !paused)
        paused = true;
}

void SimulationManager::unpause()
{
    if (active && paused)
        paused = false;
}

const bool& SimulationManager::isPaused()
{
    return paused;
}

void SimulationManager::activate()
{
    if (!active)
    {
        active = true;
        paused = false;
    }
}

void SimulationManager::deactivate()
{
    if (active)
    {
        TimerManager::get()->stopTimer("simulation");
        currentEnvironment->clearEnvironment();
        active = false;
    }
}

const bool& SimulationManager::isActive()
{
    return active;
}

void SimulationManager::setTimeFactor(const double& factor)
{
    if (factor > 0)
           timeFactor = factor;
    else
        Utils::get()->writeToLog("Invalid time factor passed, time factor values must be greater than 0.");
}

const double SimulationManager::getTimeFactor()
{
    return timeFactor;
}

const double SimulationManager::getUpdateInterval()
{
    return 1.0 / MAX_FPS;
}

void SimulationManager::update()
{
    if (InputManager::get()->getKeyState(HGEK_RBUTTON) )
    {
        hgeVector mousePosition = InputManager::get()->getMousePosition();
        hgeVector mouseMoved = mousePosition - oldMousePosition;
        uvCoords += mouseMoved;
        background->setTextureCoords(uvCoords.x, uvCoords.y, 800, 600);
        cam->getParent()->translate(hgeVector(mouseMoved.y, mouseMoved.x));
        InputManager::get()->setMousePosition(oldMousePosition);
    }
    else
        oldMousePosition = InputManager::get()->getMousePosition();


    if (active)
    {
        double updateInterval = 1.0 / MAX_FPS;
        double maxCyclesPerFrame = MAX_FPS / MIN_FPS + 20;
        double updateIterations = Utils::get()->getDTime() * timeFactor + remainingTime;

        if (updateIterations > (maxCyclesPerFrame * updateInterval))
            updateIterations = (maxCyclesPerFrame * updateInterval);

        while (updateIterations > updateInterval)
        {
            updateIterations -= updateInterval;
            TimerManager::get()->addTimerTime("simulation", updateInterval);
            predatorManager->update();
            preyManager->update();
            currentEnvironment->update();
        }

        remainingTime = updateIterations;
    }
}

const double SimulationManager::getSimulationElapsedTime()
{
    return TimerManager::get()->getTimerTime("simulation");
}

const string SimulationManager::getSimulationTime()
{
    double time = getSimulationElapsedTime();

    unsigned int day = time / 86400;
    unsigned int dayTime = time - day * 86400 ;
    unsigned int hour = dayTime / 3600;
    unsigned int minute = dayTime / 60;
    unsigned int second = dayTime % 60;

    return Utils::get()->formatString("%i:%i:%i Day: %i", hour, minute, second, day);
}

SimulationManager* SimulationManager::get()
{
    if (manager == NULL)
        manager = new SimulationManager();

    return manager;
}
