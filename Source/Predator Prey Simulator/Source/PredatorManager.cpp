/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <Utils.h>
#include "PreyManager.h"
#include "Predator.h"
#include "Prey.h"
#include "ReportManager.h"
#include "SimulationManager.h"
#include "Environment.h"
#include "ReportSection.h"
#include "PredatorManager.h"

using namespace std;

void PredatorManager::flushPredators()
{
    movedPredators.clear();
    stateChangedPredators.clear();

    SimulationManager::get()->getPreyManager()->flushPredators();
}

void PredatorManager::registerPrey(Prey* prey)
{
    listeningPrey.push_back(prey);
}

void PredatorManager::removePrey(Prey* prey)
{
    listeningPrey.remove(prey);
}

void PredatorManager::predatorStarved(Predator* pred)
{
    movedPredators.remove(pred);
    stateChangedPredators.remove(pred);

    SimulationManager::get()->getPreyManager()->removePredator(pred);
}

void PredatorManager::predatorAttacked(Predator* attacker, Prey* target)
{
    ReportManager::get()->getReportSection(attacker->getName() + attacker->getSpecies())->addMessage("\t" + SimulationManager::get()->getSimulationTime() + " Attacked Prey: " + target->getName());
    ReportManager::get()->getReportSection(target->getName() + target->getSpecies())->addMessage("\t" + SimulationManager::get()->getSimulationTime() + " Attacked and Killed by: " + attacker->getName());
    SimulationManager::get()->getPreyManager()->preyAttacked(target);
    SimulationManager::get()->getActiveEnvironment()->killPrey(target);
}

void PredatorManager::predatorStateChanged(Predator* predator)
{
    stateChangedPredators.push_back(predator);
}

void PredatorManager::predatorMoved(Predator* predator)
{
    movedPredators.push_back(predator);
}

void PredatorManager::update()
{
    list<Prey*>::const_iterator iter;
    for (iter = listeningPrey.begin(); iter != listeningPrey.end(); ++iter)
        (*iter)->update(movedPredators, stateChangedPredators);

    movedPredators.clear();
    stateChangedPredators.clear();
}
