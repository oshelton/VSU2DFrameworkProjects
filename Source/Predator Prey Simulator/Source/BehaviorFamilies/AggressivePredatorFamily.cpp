/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/AggressivePredatorFamily.h"
#include "Behaviors/AggressivePredator.h"
#include "Behaviors/FleeingPredator.h"

AggressivePredatorFamily::AggressivePredatorFamily()
{
    behaviors[PASSIVE] = new AggressivePredator();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = behaviors[PASSIVE];
    behaviors[CAUTIOUS] = behaviors[PASSIVE];
    behaviors[FLEEING] = new FleeingPredator();
}

AggressivePredatorFamily::~AggressivePredatorFamily()
{
    delete behaviors[PASSIVE];
    delete behaviors[FLEEING];
}
