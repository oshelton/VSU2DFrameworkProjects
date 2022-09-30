/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREYBEHAVIORFAMILY_H_INCLUDED
#define PREYBEHAVIORFAMILY_H_INCLUDED

#include <string>
#include "BehaviorStates.h"

class PreyBehavior;

/**Simple class used for grouping prey behaviors into a related group.
* Subclasses must fill the behaviors array in their own constructor.
*/
class PreyBehaviorFamily
{
protected:
        ///The stored Behaviors, one for each of the BehaviorTypes.
        PreyBehavior* behaviors[5];

public:
        ///Required virtual deconstructor.
        virtual ~PreyBehaviorFamily(){}

        ///Get the name of the BehaviorFamily.
        virtual const std::string getName() = 0;

        /** Get one of theBehaviors associated with the BehaviorFamily.
        * \param type The type of Behavior to retrieve.
        */
        PreyBehavior* getBehavior(const BehaviorState& type){ return behaviors[type]; }
};

#endif // PREYBEHAVIORFAMILY_H_INCLUDED
