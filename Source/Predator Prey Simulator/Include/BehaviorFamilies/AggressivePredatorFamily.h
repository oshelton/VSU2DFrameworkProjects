/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef AGGRESSIVEPREDATORFAMILY_H_INCLUDED
#define AGGRESSIVEPREDATORFAMILY_H_INCLUDED

#include "PredatorBehaviorFamily.h"

///Behavior family for aggressive predators, which will go after anything they can sense, and move a lot faster when hungry.
class AggressivePredatorFamily : public PredatorBehaviorFamily
{
public:
    ///Constructor, sets up the Behaviors.
    AggressivePredatorFamily();
    ///Required deconstructor.
    ~AggressivePredatorFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Aggressive Predator"; }
};

#endif // AGGRESSIVEPREDATORFAMILY_H_INCLUDED
