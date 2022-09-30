/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef BEHAVIORTYPES_H_INCLUDED
#define BEHAVIORTYPES_H_INCLUDED

/**Special enumerator for the different behavioral states.
* There is no distinction between Predator and Prey behaviors since a Predator might need to flee and an enraged prey might decide to turn the tables.
*/
enum BehaviorState
{
    PASSIVE = 0,
    STALKING = 1,
    PURSUING = 2,
    CAUTIOUS = 3,
    FLEEING = 4,
};

#endif // BEHAVIORTYPES_H_INCLUDED
