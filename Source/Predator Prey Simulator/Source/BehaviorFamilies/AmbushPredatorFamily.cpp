/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include "BehaviorFamilies/AmbushPredatorFamily.h"
#include "Behaviors/AggressivePredator.h"
#include "Behaviors/AmbushPredator.h"
#include "Behaviors/FleeingPredator.h"

AmbushPredatorFamily::AmbushPredatorFamily()
{
    behaviors[PASSIVE]= new AmbushPredator();
    behaviors[STALKING] = behaviors[PASSIVE];
    behaviors[PURSUING] = new AggressivePredator();
    behaviors[CAUTIOUS] = behaviors[PASSIVE];
    behaviors[FLEEING] = new FleeingPredator;
}

AmbushPredatorFamily::~AmbushPredatorFamily()
{
    delete behaviors[PASSIVE];
    delete behaviors[PURSUING];
    delete behaviors[FLEEING];
}
