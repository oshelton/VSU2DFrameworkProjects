/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef AMBUSHPREDATOR_H_INCLUDED
#define AMBUSHPREDATOR_H_INCLUDED

#include "PredatorBehavior.h"

///Predator behavior for Predators that, unless really hungry, stay mostly still and wait for Prey to come to them.
class AmbushPredator : public PredatorBehavior
{
public:
    ///Get the name of the PredatorBehavior.
    const std::string getName(){ return "Ambush"; }

    /** Update the associated Owner using the Behavior.
    * \param owner The Predator using the Behavior.
    * \param movedPrey The list containing all prey animals that moved in the last update cycle.
    * \param stateChangedPrey The list containing all prey animals whose state changed during the last update cycle.
    */
    void update(Predator* owner, const std::list<Prey*>& movedPrey, const std::list<Prey*>& stateChangedPrey);

	/** Special method used for updating when a Predator has been noticed by a Prey.  This method doesn't do anything for this PredatorBehavior.
	* \param owner The Predator using the PredatorBehavior.
	* \param spotter The Prey that noticed the Predator.
	*/
    void predatorNoticed(Predator* owner, Prey* spotter){}
};

#endif // AMBUSHPREDATOR_H_INCLUDED
