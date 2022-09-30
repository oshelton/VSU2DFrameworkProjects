/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/DefensivePreyFamily.h"
#include "Behaviors/CarefulPrey.h"
#include "Behaviors/DefensivePrey.h"

DefensivePreyFamily::DefensivePreyFamily()
{
    behaviors[PASSIVE] = new CarefulPrey();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = behaviors[PASSIVE];
    behaviors[CAUTIOUS] = new DefensivePrey();
    behaviors[FLEEING] = behaviors[CAUTIOUS];
}

DefensivePreyFamily::~DefensivePreyFamily()
{
    delete behaviors[PASSIVE];
    delete behaviors[CAUTIOUS];
}
