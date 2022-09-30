/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREDATORBEHAVIORFAMILY_H_INCLUDED
#define PREDATORBEHAVIORFAMILY_H_INCLUDED

#include <string>
#include "BehaviorStates.h"

class PredatorBehavior;

/**Simple class used for grouping predator behaviors into a related group.
* Subclasses must fill the behaviors array in their own constructor.
*/
class PredatorBehaviorFamily
{
protected:
        ///The stored Behaviors, one for each of the BehaviorTypes.
        PredatorBehavior* behaviors[5];

public:
        ///Required virtual deconstructor.
        virtual ~PredatorBehaviorFamily(){}

        ///Get the name of the BehaviorFamily.
        virtual const std::string getName() = 0;

        /** Get one of theBehaviors associated with the BehaviorFamily.
        * \param state The type of Behavior to retrieve.
        */
        inline PredatorBehavior* getBehavior(const BehaviorState& state){ return behaviors[state]; }
};

#endif // PREDATORBEHAVIORFAMILY_H_INCLUDED
