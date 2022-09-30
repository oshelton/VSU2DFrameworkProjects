/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "Behaviors/GenericPredatorBehavior.h"
#include "BehaviorFamilies/GenericPredatorBehaviorFamily.h"

GenericPredatorBehaviorFamily::GenericPredatorBehaviorFamily()
{
    behaviors[PASSIVE] = behaviors[STALKING] = behaviors[PURSUING] = behaviors[CAUTIOUS] = behaviors[FLEEING] = new GenericPredatorBehavior();
}

GenericPredatorBehaviorFamily::~GenericPredatorBehaviorFamily()
{
    delete behaviors[PASSIVE];
}
