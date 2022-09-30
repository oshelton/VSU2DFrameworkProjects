/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <TimerManager.h>
#include <Utils.h>
#include <SceneNode.h>
#include "SimulationManager.h"
#include "Environment.h"
#include "predatorManager.h"
#include "PredatorBehavior.h"
#include "PredatorBehaviorFamily.h"
#include "Prey.h"
#include "ReportManager.h"
#include "ReportSection.h"
#include "PreyManager.h"
#include "Predator.h"

using namespace std;

Predator::Predator(const string& name, const string& species) : Animal(), hungryTime(0), starvationTime(0), maxAttackDistance(0), numberPreyKilled(0),  behaviorFamily(NULL)
{
    this->name = name;
    this->species = species;

    setupNodeHeirarchy();
    SimulationManager::get()->getPreyManager()->registerPredator(this);
    TimerManager::get()->createTimer(name + species, true);

    ReportManager::get()->createReportSection(name + species)->addMessage("Predator: " + name + " Species: " + species);
}

Predator::~Predator()
{
    destroyNodeHeirarchy();
    TimerManager::get()->destroyTimer(name + species);
}

void Predator::setBehaviorState(const BehaviorState& state)
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
        SimulationManager::get()->getPredatorManager()->predatorStateChanged(this);
        currentBehavior = state;
    }
}

void Predator::setHungerTime(double time)
{
    if (time <= 0)
        time *= -1;
    hungryTime = time;
}

void Predator::setStarvationTime(double time)
{
    if (time <= 0)
        time *= -1;
    starvationTime = time;
}

const double Predator::getHungerFactor()
{
    TimerManager* timers = TimerManager::get();
    if (timers->getTimerTime(name + species) <= hungryTime)
        return timers->getTimerTime(name + species) / hungryTime;
    else
    {
        double currentTime = TimerManager::get()->getTimerTime(name + species) - hungryTime;
        return currentTime /  starvationTime + 1;
    }
}

void Predator::setMaxAttackDistance(double distance)
{
    if (distance == 0)
        distance = 1;
    else if (distance < 0)
        maxAttackDistance = distance * -1;
    else
        maxAttackDistance = distance;
}

const double& Predator::getMaxAttackDistance()
{
    return maxAttackDistance;
}

const unsigned int& Predator::getNumberPreyKilled()
{
    return numberPreyKilled;
}

void Predator::setBehaviorFamily(const string& family)
{
    behaviorFamily = SimulationManager::get()->getPredatorBehaviorFamily(family);
}

PredatorBehaviorFamily* Predator::getBehaviorFamily()
{
    return behaviorFamily;
}

void Predator::move(const double& factor)
{
    mainNode->translate(hgeVector(0, baseSpeed * SimulationManager::get()->getUpdateInterval() * factor));
    SimulationManager::get()->getPredatorManager()->predatorMoved(this);
}

void Predator::attack(Prey* prey)
{
    SimulationManager::get()->getPredatorManager()->predatorAttacked(this, prey);
    TimerManager::get()->stopTimer(name + species);
    TimerManager::get()->startTimer(name + species);
    ++numberPreyKilled;
}

void Predator::update(const std::list<Prey*>& movedPrey, const std::list<Prey*>& stateChangedPrey)
{
    if (TimerManager::get()->getTimerTime(name + species) >= hungryTime + starvationTime)
    {
        ReportManager::get()->getReportSection(name + species)->addMessage("\t" + SimulationManager::get()->getSimulationTime() + " Starved to death.");
        ReportManager::get()->getReportSection(name + species)->addMessage("\t" + string("Number of Prey killed: ") + Utils::get()->intToString(numberPreyKilled));
        SimulationManager::get()->getPredatorManager()->predatorStarved(this);
    }
    else
    {

        updatePointer();
        if (!SimulationManager::get()->isPaused())
        {
            TimerManager::get()->addTimerTime(name + species, SimulationManager::get()->getUpdateInterval());
            behaviorFamily->getBehavior(currentBehavior)->update(this, movedPrey,stateChangedPrey);
        }
    }
}

const bool Predator::canSee(Prey* const prey)
{
    hgeVector position = prey->getPosition();

    Utils* utils = Utils::get();

    double distance = utils->distanceBetween(getPosition(), prey->getPosition());

    if (distance <= (sightDistance * (1.0 -prey->getCamoflauge())))
    {
        double angle = utils->angleDegrees(utils->angleBetween(getPosition(), position));
        double halfAngle = sightAngle / 2;
        if (angle <= (getHeading() + halfAngle) && angle >= (getHeading() - halfAngle))
            return true;
        else
            return false;
    }
    else
        return false;
}

const bool Predator::canHear(Prey* const prey)
{
    if ((Utils::get()->distanceBetween(getPosition(), prey->getPosition()) <= (hearingDistance * (1.0 - prey->getStealth()))))
        return true;
    else
        return false;
}

void Predator::noticed(Prey* const spotter)
{
    behaviorFamily->getBehavior(currentBehavior)->predatorNoticed(this, spotter);
}
