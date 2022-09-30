/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef DEFENSIVEPREYFAMILY_H_INCLUDED
#define DEFENSIVEPREYFAMILY_H_INCLUDED

#include "PreyBehaviorFamily.h"

///Prey behavior family for Prey animals that actually become aggressive when approached by a predator of slightly larger and smaller size.
class DefensivePreyFamily : public PreyBehaviorFamily
{
public:
    ///Constructor, sets up the behaviors.
    DefensivePreyFamily();
    ///Deconstructor, deletes the behaviors.
    ~DefensivePreyFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Defensive Prey"; }
};

#endif // DEFENSIVEPREYFAMILY_H_INCLUDED
