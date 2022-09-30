/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef GENERICPREDATORBEHAVIORFAILY_H_INCLUDED
#define GENERICPREDATORBEHAVIORFAMILY_H_INCLUDED

#include "PredatorBehaviorFamily.h"

///Generic Predator Behavior Family class. Used for testing and when no other Behavior Families fit.  This uses the GenericPredatorBehavior class for all states.
class GenericPredatorBehaviorFamily : public PredatorBehaviorFamily
{
public:
    ///Constructor, sets up the Behaviors.
    GenericPredatorBehaviorFamily();
    ///Required deconstructor.
    ~GenericPredatorBehaviorFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Generic"; }
};

#endif // GENERICPREDATORBEHAVIORFAMILY_H_INCLUDED
