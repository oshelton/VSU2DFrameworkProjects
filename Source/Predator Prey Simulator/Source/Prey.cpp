/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <TimerManager.h>
#include <Utils.h>
#include <SceneNode.h>
#include "SimulationManager.h"
#include "PreyBehaviorFamily.h"
#include "PreyBehavior.h"
#include "ReportManager.h"
#include "ReportSection.h"
#include "PreyManager.h"
#include "PredatorManager.h"
#include "Predator.h"
#include "Prey.h"

using namespace std;

Prey::Prey(const string& name, const string& species) : Animal()
{
    this->name = name;
    this->species = species;

    setupNodeHeirarchy();
    SimulationManager::get()->getPredatorManager()->registerPrey(this);

    ReportManager::get()->createReportSection(name + species)->addMessage("Prey: " + name + " Species: " + species);
}

Prey::~Prey()
{
    destroyNodeHeirarchy();
    SimulationManager::get()->getPredatorManager()->removePrey(this);
}

void Prey::setBehaviorState(const BehaviorState& state)
{
    if (currentBehavior != state)
    {
        string newState = "";
        string oldState = "";

        switch (state)
        {
            case PASSIVE:
                newState = "Passive";
                break;
            case STALKING:
                newState = "Stalking";
                break;
            case PURSUING:
                newState = "Pursuing";
                break;
            case CAUTIOUS:
                newState = "Cautious";
                break;
            case FLEEING:
                newState = "Fleeing";
                break;
        }

        switch (currentBehavior)
        {
            case PASSIVE:
                oldState = "Passive";
                break;
            case STALKING:
                oldState = "Stalking";
                break;
            case PURSUING:
                oldState = "Pursuing";
                break;
            case CAUTIOUS:
                oldState = "Cautious";
                break;
            case FLEEING:
                oldState = "Fleeing";
                break;
        }

        ReportManager::get()->getReportSection(name + species)->addMessage("\t" + SimulationManager::get()->getSimulationTime() + " Changed behavior state from " + oldState + " to " + newState + ".");
        SimulationManager::get()->getPreyManager()->preyStateChanged(this);
        currentBehavior = state;
    }
}

void Prey::setBehaviorFamily(const string& family)
{
    behaviorFamily = SimulationManager::get()->getPreyBehaviorFamily(family);
}

PreyBehaviorFamily* Prey::getBehaviorFamily()
{
    return behaviorFamily;
}

void Prey::move(const double& factor)
{
    mainNode->translate(hgeVector(0, baseSpeed * SimulationManager::get()->getUpdateInterval() * factor));
    SimulationManager::get()->getPreyManager()->preyMoved(this);
}

void Prey::update(const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators)
{
    updatePointer();
    if (!SimulationManager::get()->isPaused())
        behaviorFamily->getBehavior(currentBehavior)->update(this, movedPredators, stateChangedPredators);
}

const bool Prey::canSee(Predator* const predator)
{
    hgeVector position = predator->getPosition();

    Utils* utils = Utils::get();

    double distance = utils->distanceBetween(getPosition(), predator->getPosition());

    if (distance <= (sightDistance * (1.0 -predator->getCamoflauge())))
    {
        double angle = utils->angleDegrees(utils->angleBetween(getPosition(), position));
        double halfAngle = sightAngle / 2;
        if (angle <= (getHeading() + halfAngle) && angle >= (getHeading() - halfAngle))
        {
            predator->noticed(this);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

const bool Prey::canHear(Predator* const predator)
{
    if ((Utils::get()->distanceBetween(getPosition(), predator->getPosition()) <= (hearingDistance * (1.0 - predator->getStealth()))))
    {
        predator->noticed(this);
        return true;
    }
    else
        return false;
}
