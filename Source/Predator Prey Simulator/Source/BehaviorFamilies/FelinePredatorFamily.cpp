/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/FelinePredatorFamily.h"
#include "Behaviors/HungerFactoredPredator.h"
#include "Behaviors/AggressivePredator.h"
#include "Behaviors/FleeingPredator.h"

FelinePredatorFamily::FelinePredatorFamily()
{
    behaviors[PASSIVE] = new HungerFactoredPredator();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = new AggressivePredator();
    behaviors[CAUTIOUS] = behaviors[PASSIVE];
    behaviors[FLEEING] = new FleeingPredator();
}

FelinePredatorFamily::~FelinePredatorFamily()
{
    delete behaviors[PASSIVE];
    delete behaviors[PURSUING];
    delete behaviors[FLEEING];
}
