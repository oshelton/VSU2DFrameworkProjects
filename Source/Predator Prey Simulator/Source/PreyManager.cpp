/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <Utils.h>
#include "Predator.h"
#include "Prey.h"
#include "ReportManager.h"
#include "ReportSection.h"
#include "SimulationManager.h"
#include "Environment.h"
#include "PreyManager.h"

using namespace std;

void PreyManager::flushPredators()
{
    listeningPredators.clear();
}

void PreyManager::registerPredator(Predator* predator)
{
    listeningPredators.push_back(predator);
}

void PreyManager::removePredator(Predator* predator)
{
    starvedPredators.push_back(predator);
}

void PreyManager::preyAttacked(Prey* prey)
{
    movedPrey.remove(prey);
    stateChangedPrey.remove(prey);
}

void PreyManager::preyNoticesPredator(Prey* prey, Predator* predator)
{
    predator->noticed(prey);
}

void PreyManager::preyStateChanged(Prey* prey)
{
    stateChangedPrey.push_back(prey);
}

void PreyManager::preyMoved(Prey* prey)
{
    movedPrey.push_back(prey);
}

void PreyManager::update()
{

    list<Predator*>::iterator iter;
    for (iter = listeningPredators.begin(); iter != listeningPredators.end(); ++iter)
        (*iter)->update(movedPrey, stateChangedPrey);


    while (starvedPredators.begin() != starvedPredators.end())
    {
        Predator* pred = starvedPredators.back();
        starvedPredators.pop_back();
        listeningPredators.remove(pred);
        SimulationManager::get()->getActiveEnvironment()->killPredator(pred);
    }
    starvedPredators.clear();

    movedPrey.clear();
    stateChangedPrey.clear();
}
