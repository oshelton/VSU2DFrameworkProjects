/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef ALERTPREY_H_INCLUDED
#define ALERTPREY_H_INCLUDED

#include "PreyBehavior.h"

///Prey behavior for Prey that run at the first sight of a Predator, kind of mimicks the standard GenericPreyBehavior, but simpler.
class AlertPrey : public PreyBehavior
{
public:
    ///Get the name of the PredatorBehavior.
    const std::string getName(){ return "Alert"; }

    /** Update the associated Owner using the Behavior.
    * \param owner The Predator using the Behavior.
    * \param movedPrey The list containing all prey animals that moved in the last update cycle.
    * \param stateChangedPrey The list containing all prey animals whose state changed during the last update cycle.
    */
    void update(Prey* owner, const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators);
};

#endif // ALERTPREY_H_INCLUDED
