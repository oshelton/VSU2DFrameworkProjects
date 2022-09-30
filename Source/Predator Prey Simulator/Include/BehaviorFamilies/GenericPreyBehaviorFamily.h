/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef GENERICPREYBEHAVIORFAMILY_H_INCLUDED
#define GENERICPREYBEHAVIORFAMILY_H_INCLUDED

#include "PreyBehaviorFamily.h"

///Generic Prey Behavior Family class. Used for testing and when no other Behavior Families fit.  This uses the GenericPreyBehavior class for all states.
class GenericPreyBehaviorFamily : public PreyBehaviorFamily
{
public:
    ///Constructor, sets up the Behaviors.
    GenericPreyBehaviorFamily();
    ///Required virtual deconstructor.
    ~GenericPreyBehaviorFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Generic"; }
};

#endif // GENERICPREYBEHAVIORFAMILY_H_INCLUDED
