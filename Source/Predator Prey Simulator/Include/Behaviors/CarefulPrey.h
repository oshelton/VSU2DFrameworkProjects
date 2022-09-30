/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef CAREFULPREY_H_INCLUDED
#define CAREFULPREY_H_INCLUDED

#include "PreyBehavior.h"

///Prey behavior for Prey that stop moving when they first notice a Predator and start running when it gets half way into its line of sight or hearing radius.
class CarefulPrey : public PreyBehavior
{
public:
    ///Get the name of the PredatorBehavior.
    const std::string getName(){ return "Careful"; }

    /** Update the associated Owner using the Behavior.
    * \param owner The Predator using the Behavior.
    * \param movedPrey The list containing all prey animals that moved in the last update cycle.
    * \param stateChangedPrey The list containing all prey animals whose state changed during the last update cycle.
    */
    void update(Prey* owner, const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators);
};

#endif // CAREFULPREY_H_INCLUDED
