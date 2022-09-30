/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef FELINEPREDATORFAMILY_H_INCLUDED
#define FELINEPREDATORFAMILY_H_INCLUDED

#include "PredatorBehaviorFamily.h"

/** Behavior family for feline predators, which will avoid attacking groups of prey and have a slight ambush quality to them.
* As the predator becomes hungrier the more aggressive it becomes and the less likely it is to ambush.
*/
class FelinePredatorFamily : public PredatorBehaviorFamily
{
public:
    ///Constructor, sets up the Behaviors.
    FelinePredatorFamily();
    ///Required deconstructor.
    ~FelinePredatorFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Feline Predator"; }
};

#endif // FELINEPREDATORFAMILY_H_INCLUDED
