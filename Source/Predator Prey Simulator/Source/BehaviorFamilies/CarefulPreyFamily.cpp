/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/CarefulPreyFamily.h"
#include "Behaviors/CarefulPrey.h"
#include "Behaviors/RandomFleePrey.h"

CarefulPreyFamily::CarefulPreyFamily()
{
    behaviors[PASSIVE] = new CarefulPrey();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = behaviors[PASSIVE];
    behaviors[CAUTIOUS] = behaviors[PASSIVE];
    behaviors[FLEEING] = new RandomFleePrey();
}

CarefulPreyFamily::~CarefulPreyFamily()
{
    delete behaviors[PASSIVE];
    delete behaviors[FLEEING];
}
