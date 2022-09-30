/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <Utils.h>
#include <hgecolor.h>
#include <ScriptManager.h>
#include <hgeresource.h>
#include "Predator.h"
#include "Prey.h"
#include "Environments/TestEnvironment.h"

using namespace std;

TestEnvironment::TestEnvironment()
{
    init();
    ScriptManager::get()->getResourceManager()->LoadScript("../resources/data/TestEnvironment.res");
}

TestEnvironment::~TestEnvironment()
{
    ScriptManager::get()->getResourceManager()->Purge(2);
}

Predator* TestEnvironment::createPredator(const string& type, const string& name, const hgeVector& pos)
{
    if (predators.find(name) == predators.end())
    {
        if (type == "Test")
        {
            predators[name] = new Predator(name, "Test Predator");
            Predator* pred = predators[name];
            pred->setBehaviorFamily("Ambush");
            pred->setBehaviorState(PASSIVE);
            pred->setHungerTime(500);
            pred->setStarvationTime(1000);
            pred->setSpeed(60);
            pred->setCamoflauge(.2);
            pred->setStealth(.5);
            pred->setWeight(50);
            pred->setHearingDistance(300);
            pred->setSightAngle(60);
            pred->setSightDistance(450);
            pred->setMaxAttackDistance(75);
            pred->setPosition(pos);

            pred->constructRenderables("TestPredator", "PredatorPointer", hgeColor(0.2, 0.2, 1.0, 0.8), hgeColor(1, 0, 0, 1));
            return pred;
        }
        else
        {
            Utils::get()->writeFormattedToLog("Environment [%s] does not handle Predator type [%s], returning NULL.", true, getType().c_str(), type.c_str());
            return NULL;
        }
    }
    else
    {
        Utils::get()->writeToLog("Predator with name [" + name + "] already exists, returning the previously existing Predator.");
        return predators[name];
    }
}

Prey* TestEnvironment::createPrey(const string& type, const string& name, const hgeVector& pos)
{
    if (prey.find(name) == prey.end())
    {
        if (type == "Test")
        {
            prey[name] = new Prey(name, "Test prey");
            Prey* animal = prey[name];
            animal->setBehaviorFamily("Generic");
            animal->setBehaviorState(PASSIVE);
            animal->setSpeed(35);
            animal->setCamoflauge(.5);
            animal->setStealth(.2);
            animal->setWeight(50);
            animal->setHearingDistance(300);
            animal->setSightAngle(60);
            animal->setSightDistance(450);
            animal->setPosition(pos);

            animal->constructRenderables("TestPrey", "PreyPointer", hgeColor(0.2, 1.0, .2, 0.8), hgeColor(1, 1, 0, 1));
            return animal;
        }
        else
        {
            Utils::get()->writeFormattedToLog("Environment [%s] does not handle Prey type [%s], returning NULL.", true, getType().c_str(), type.c_str());
            return NULL;
        }
    }
    else
    {
        Utils::get()->writeToLog("Prey with name [" + name + "] already exists, returning the previously existing Prey.");
        return prey[name];
    }
}
