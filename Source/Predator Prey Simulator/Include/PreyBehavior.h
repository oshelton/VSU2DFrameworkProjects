/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREYBEHAVIOR_H_INCLUDED
#define PREYBEHAVIOR_H_INCLUDED

#include <string>
#include <list>

class Prey;
class Predator;

///Base Prey behavior class.  Behaviors don't associate themselves with a specific state.  That is up to the BehaviorFamily to associate a Behavior with an animal state.
class PreyBehavior
{
public:
    ///Required virtual deconstructor.
    virtual ~PreyBehavior(){}

    ///Get the name of the PreyBehavior.
    virtual const std::string getName() = 0;

    /** Update the associated Owner using the Behavior.
    * \param owner The Prey using the Behavior.
    * \param movedPredators The list containing all predator animals that moved in the last update cycle.
    * \param stateChangedPredators The list containing all predator animals whose state changed during the last update cycle.
    */
    virtual void update(Prey* owner, const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators) = 0;
};

#endif // PREYBEHAVIOR_H_INCLUDED
