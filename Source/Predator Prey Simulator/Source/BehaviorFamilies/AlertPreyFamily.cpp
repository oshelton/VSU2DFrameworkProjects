/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/AlertPreyFamily.h"
#include "Behaviors/AlertPrey.h"
#include "Behaviors/GenericPreyBehavior.h"

AlertPreyFamily::AlertPreyFamily()
{
    behaviors[PASSIVE] = new AlertPrey();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = behaviors[PASSIVE];
    behaviors[CAUTIOUS] = behaviors[PASSIVE];
    behaviors[FLEEING] = behaviors[PASSIVE];
}

AlertPreyFamily::~AlertPreyFamily()
{
    delete behaviors[PASSIVE];
}
