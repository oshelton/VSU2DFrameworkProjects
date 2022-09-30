/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef RANDOMFLEEPREY_H_INCLUDED
#define RANDOMFLEEPREY_H_INCLUDED

#include "PreyBehavior.h"

///Prey behavior for Prey that rather than runnning directly away from pursuing Predators migt change direction to within 30 degrees of the fleeing angle.  Not practical, bt neat.
class RandomFleePrey: public PreyBehavior
{
public:
    ///Get the name of the PredatorBehavior.
    const std::string getName(){ return "Flee"; }

    /** Update the associated Owner using the Behavior.
    * \param owner The Predator using the Behavior.
    * \param movedPrey The list containing all prey animals that moved in the last update cycle.
    * \param stateChangedPrey The list containing all prey animals whose state changed during the last update cycle.
    */
    void update(Prey* owner, const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators);
};

#endif // RANDOMFLEEPREY_H_INCLUDED
