/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef CAREFULPREYFAMILY_H_INCLUDED
#define CAREFULPREYFAMILY_H_INCLUDED

#include "PreyBehaviorFamily.h"

///Prey behavior family for Prey animals that that stop moving until predators get extremely close and then run.
class CarefulPreyFamily : public PreyBehaviorFamily
{
public:
    ///Constructor, sets up the behaviors.
    CarefulPreyFamily();
    ///Deconstructor, deletes the behaviors.
    ~CarefulPreyFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Careful Prey"; }
};

#endif // CAREFULPREYFAMILY_H_INCLUDED
