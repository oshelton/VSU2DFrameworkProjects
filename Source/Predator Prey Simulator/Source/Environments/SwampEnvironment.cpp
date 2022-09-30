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
#include "Environments/SwampEnvironment.h"

using namespace std;

SwampEnvironment::SwampEnvironment()
{
    init();
    ScriptManager::get()->getResourceManager()->LoadScript("../resources/data/SwampEnvironment.res");
}

SwampEnvironment::~SwampEnvironment()
{
    ScriptManager::get()->getResourceManager()->Purge(2);
}


Predator* SwampEnvironment::createPredator(const string& type, const string& name, const hgeVector& pos)
{
    if (predators.find(name) == predators.end())
    {
        if (type == "Alligator")
        {
            predators[name] = new Predator(name, "Alligator");
            Predator* pred = predators[name];
            pred->setBehaviorFamily("Ambush");
            pred->setBehaviorState(PASSIVE);
            pred->setHungerTime(1000);
            pred->setStarvationTime(3000);
            pred->setSpeed(20);
            pred->setCamoflauge(.6);
            pred->setStealth(.7);
            pred->setWeight(200);
            pred->setHearingDistance(150);
            pred->setSightAngle(120);
            pred->setSightDistance(800);
            pred->setMaxAttackDistance(40);
            pred->setPosition(pos);

            pred->constructRenderables("alligator", "PredatorPointer", hgeColor(0.2, 0.2, 1.0, 0.8), hgeColor(1, 0, 0, 1));

            return pred;
        }
        else if (type == "Black Bear")
        {
            predators[name] = new Predator(name, "BlackBear");
            Predator* pred = predators[name];
            pred->setBehaviorFamily("Aggressive");
            pred->setBehaviorState(PASSIVE);
            pred->setHungerTime(700);
            pred->setStarvationTime(1000);
            pred->setSpeed(30);
            pred->setCamoflauge(.2);
            pred->setStealth(.2);
            pred->setWeight(500);
            pred->setHearingDistance(300);
            pred->setSightAngle(60);
            pred->setSightDistance(250);
            pred->setMaxAttackDistance(30);
            pred->setPosition(pos);

            pred->constructRenderables("blackbear", "PredatorPointer", hgeColor(0.2, 0.2, 1.0, 0.8), hgeColor(1, 0, 0, 1));
            return pred;
        }
        else if (type == "Bobcat")
        {
            predators[name] = new Predator(name, "Bobcat");
            Predator* pred = predators[name];
            pred->setBehaviorFamily("Feline");
            pred->setBehaviorState(PASSIVE);
            pred->setHungerTime(700);
            pred->setStarvationTime(1000);
            pred->setSpeed(70);
            pred->setCamoflauge(.4);
            pred->setStealth(.7);
            pred->setWeight(75);
            pred->setHearingDistance(450);
            pred->setSightAngle(50);
            pred->setSightDistance(950);
            pred->setMaxAttackDistance(30);
            pred->setPosition(pos);

            pred->constructRenderables("bobcat", "PredatorPointer", hgeColor(0.2, 0.2, 1.0, 0.8), hgeColor(1, 0, 0, 1));
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

Prey* SwampEnvironment::createPrey(const string& type, const string& name, const hgeVector& pos)
{
    if (prey.find(name) == prey.end())
    {
        if (type == "Deer")
        {
            prey[name] = new Prey(name, "Deer");
            Prey* animal = prey[name];
            animal->setBehaviorFamily("Alert");
            animal->setBehaviorState(PASSIVE);
            animal->setSpeed(70);
            animal->setCamoflauge(.2);
            animal->setStealth(.6);
            animal->setWeight(120);
            animal->setHearingDistance(450);
            animal->setSightAngle(90);
            animal->setSightDistance(250);
            animal->setPosition(pos);

            animal->constructRenderables("deer", "PreyPointer", hgeColor(0.2, 1.0, .2, 0.8), hgeColor(1, 1, 0, 1));
            return animal;
        }
        else if (type == "Possum")
        {
            prey[name] = new Prey(name, "Possum");
            Prey* animal = prey[name];
            animal->setBehaviorFamily("Defensive");
            animal->setBehaviorState(PASSIVE);
            animal->setSpeed(25);
            animal->setCamoflauge(.2);
            animal->setStealth(.7);
            animal->setWeight(20);
            animal->setHearingDistance(100);
            animal->setSightAngle(45);
            animal->setSightDistance(500);
            animal->setPosition(pos);

            animal->constructRenderables("possum", "PreyPointer", hgeColor(0.2, 1.0, .2, 0.8), hgeColor(1, 1, 0, 1));
            return animal;
        }
        else if (type == "Rabbit")
        {
            prey[name] = new Prey(name, "Rabbit");
            Prey* animal = prey[name];
            animal->setBehaviorFamily("Careful");
            animal->setBehaviorState(PASSIVE);
            animal->setSpeed(40);
            animal->setCamoflauge(.2);
            animal->setStealth(.4);
            animal->setWeight(15);
            animal->setHearingDistance(150);
            animal->setSightAngle(75);
            animal->setSightDistance(200);
            animal->setPosition(pos);

            animal->constructRenderables("rabbit", "PreyPointer", hgeColor(0.2, 1.0, .2, 0.8), hgeColor(1, 1, 0, 1));
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
