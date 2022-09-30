/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "Behaviors/GenericPreyBehavior.h"
#include "BehaviorFamilies/GenericPreyBehaviorFamily.h"

GenericPreyBehaviorFamily::GenericPreyBehaviorFamily()
{
    behaviors[PASSIVE] = behaviors[STALKING] = behaviors[PURSUING] = behaviors[CAUTIOUS] = behaviors[FLEEING] = new GenericPreyBehavior();
}

GenericPreyBehaviorFamily::~GenericPreyBehaviorFamily()
{
    delete behaviors[PASSIVE];
}
