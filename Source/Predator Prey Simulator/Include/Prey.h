/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREY_H_INCLUDED
#define PREY_H_INCLUDED

#include "Animal.h"

class PreyBehaviorFamily;
class Predator;

///Clss that represents a Prey animal.
class Prey : public Animal
{
private:
    PreyBehaviorFamily* behaviorFamily;

public:
    /** Constructor
    * \param name The name of the Prey.
    * \param species The species of the Prey.
    */
    Prey(const std::string& name, const std::string& species);
    ///Deconstructor.
    ~Prey();

    ///Get the type of the class.
    const std::string getType(){ return "Predator"; }

    /** Thismethod changes the current behavioral state of the Prey.  This method also notifies the PreyManager if an actual state change occurs.
    * \param state The BehaviorState to set the Prey to, what the new State actually does depends on the PreyBehaviorFmily in use.
    */
    void setBehaviorState(const BehaviorState& state);

    /** Set the PredatorBehaviorFamily of the Predator.
    * \param family The PredatorBehaviorFamily to set.
    */
    void setBehaviorFamily(const std::string& family);
    ///Get the PredatorBehaviorFamily used by the Predator.
    PreyBehaviorFamily* getBehaviorFamily();

    /** Move the Prey.
    * \param factor The amount by which to modify the base speed, should be greater than 0.  Negative values will move the Animal backwards.
    */
    void move(const double& factor);

    /** Update the Predator.
    * \param movedPrey The list of Prey animals moved in the last update cycle.
    * \param stateChangedPrey The list of Prey animals that changed state in the last update cycle.
    */
    void update(const std::list<Predator*>& movedPredators, const std::list<Predator*>& stateChangedPredators);

    /** Utility method used to determine if a Prey can see a Predator.
    * \param prey The Predator animal to check.
    */
    const bool canSee(Predator* const predator);
    /** Utility method used to determine if a Prey can hear a Predator.
    * \param prey The Predator animal to check.
    */
    const bool canHear(Predator* const predator);
};

#endif // PREY_H_INCLUDED
