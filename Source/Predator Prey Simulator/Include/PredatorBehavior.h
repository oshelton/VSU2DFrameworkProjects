/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREDATORBEHAVIOR_H_INCLUDED
#define PREDATORBEHAVIOR_H_INCLUDED

#include <string>
#include <list>

class Predator;
class Prey;

///Base Predator behavior class.  Behaviors don't associate themselves with a specific state.  That is up to the BehaviorFamily to associate a Behavior with an animal state.
class PredatorBehavior
{
public:
    ///Required virtual deconstructor.
    virtual ~PredatorBehavior(){}

    ///Get the name of the PredatorBehavior.
    virtual const std::string getName() = 0;

    /** Update the associated Owner using the Behavior.
    * \param owner The Predator using the Behavior.
    * \param movedPrey The list containing all prey animals that moved in the last update cycle.
    * \param stateChangedPrey The list containing all prey animals whose state changed during the last update cycle.
    */
    virtual void update(Predator* owner, const std::list<Prey*>& movedPrey, const std::list<Prey*>& stateChangedPrey) = 0;

	/** Special method used for updating when a Predator has been noticed by a Prey.
	* \param owner The Predator using the PredatorBehavior.
	* \param spotter The Prey that noticed the Predator.
	*/
	virtual void predatorNoticed(Predator* owner, Prey* spotter) = 0;
};

#endif // PREDATORBEHAVIOR_H_INCLUDED
