/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef AMBUSHPREDATORFAMILY_H_INCLUDED
#define AMBUSHPREDATORFAMILY_H_INCLUDED

#include "PredatorBehaviorFamily.h"

///Behavior family for ambush predators, which don't move very often unless they are hungry and can sense a nearby prey animal.
class AmbushPredatorFamily : public PredatorBehaviorFamily
{
public:
    ///Constructor, sets up the Behaviors.
    AmbushPredatorFamily();
    ///Required deconstructor.
    ~AmbushPredatorFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Ambush Predator"; }
};

#endif // AMBUSHPREDATORFAMILY_H_INCLUDED
