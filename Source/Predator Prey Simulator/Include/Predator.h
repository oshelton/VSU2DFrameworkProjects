/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREDATOR_H_INCLUDED
#define PREDATOR_H_INCLUDED

#include <list>
#include "Animal.h"

class PredatorBehaviorFamily;
class Prey;

///Predator animal class.
class Predator : public Animal
{
private:
    ///How much time after a successful attack will need to pass before the Predator becomes hungry (in seconds).
    double hungryTime;
    ///How much time will pass after a Predator becomes hungry that it will starve (in seconds).
    double starvationTime;

    ///The maximum distance at which the Predator can attack a Prey.
    double maxAttackDistance;

    ///The number of prey killed by the Predator.
    unsigned int numberPreyKilled;

    ///The PredatorBehaviorFamily being used by the Predator.
    PredatorBehaviorFamily* behaviorFamily;

public:
    /** Constructor
    * \param name The name of the Predator.
    * \param species The species of the Predator.
    */
    Predator(const std::string& name, const std::string& species);
    ///Deconstructor.
    ~Predator();

    ///Get the type of the class.
    const std::string getType(){ return "Prey"; }

    /** Thismethod changes the current behavioral state of the Predator.  This method also notifies the PredatorManager if an actual state change occurs.
    * \param state The BehaviorState to set the Predator to, what the new State actually does depends on the PredatorBehaviorFmily in use.
    */
    void setBehaviorState(const BehaviorState& state);

    /** Set how much time will pass before the Predator will become hungry.
    * \param time Time in seconds.
    */
    void setHungerTime(double time);
    /** Set how much time will pass before the Predator will starve.
    * \param time Time in seconds, this will be added to the hunger time.
    */
    void setStarvationTime(double time);

    ///Get how hungry the animal is, 0 to 1 means no hunger, 1 to 2 means hungry, and greater than 2 means starvation.
    const double getHungerFactor();

    /** Set the maximumdistance at which the Predator can attack Prey.
    * \param distance The distance, in pixels that the Predator can attack.
    * \remark This property should be positive and greater than 0.
    */
    void setMaxAttackDistance(double distance);

    ///Get the maximum attack range of the Predator.
    const double& getMaxAttackDistance();

    ///Get the number of Prey killed by thePredator.
    const unsigned int& getNumberPreyKilled();

    /** Set the PredatorBehaviorFamily of the Predator.
    * \param family The PredatorBehaviorFamily to set.
    */
    void setBehaviorFamily(const std::string& family);
    ///Get the PredatorBehaviorFamily used by the Predator.
    PredatorBehaviorFamily* getBehaviorFamily();

    /** Move the Predator.
    * \param factor The amount by which to modify the base speed, should be greater than 0.  Negative values will move the Animal backwards.
    */
    void move(const double& factor);

    /** Attack a Prey animal.
    * \param prey The Prey animal attacked.
    */
    void attack(Prey* prey);

    /** Update the Predator.
    * \param movedPrey The list of Prey animals moved in the last update cycle.
    * \param stateChangedPrey The list of Prey animals that changed state in the last update cycle.
    */
    void update(const std::list<Prey*>& movedPrey, const std::list<Prey*>& stateChangedPrey);

    /** Utility method used to determine if a Predator can see a Prey.
    * \param prey The Prey animal to check.
    */
    const bool canSee(Prey* const prey);
    /** Utility method used to determine if a Predator canhear a Prey.
    * \param prey The Prey animal to check.
    */
    const bool canHear(Prey* const prey);

    /** Notify the Predator that it has been spotted by a Prey animal.
    * \param spotter The Prey animal that spotted the Predator.
    */
    void noticed(Prey* const spotter);
};

#endif // PREDATOR_H_INCLUDED
