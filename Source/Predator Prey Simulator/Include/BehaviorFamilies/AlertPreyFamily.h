/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef ALERTPREYFAMILY_H_INCLUDED
#define ALERTPREYFAMILY_H_INCLUDED

#include "PreyBehaviorFamily.h"

///Prey behavior family for Prey animals that are extremely skiddish and will run at the first sight of a predator.
class AlertPreyFamily : public PreyBehaviorFamily
{
public:
    ///Constructor, sets up the behaviors.
    AlertPreyFamily();
    ///Deconstructor, deletes the behaviors.
    ~AlertPreyFamily();

    ///Get the name of the BehaviorFamily.
    const std::string getName(){ return "Alert Prey"; }
};

#endif // ALERTPREYFAMILY_H_INCLUDED
