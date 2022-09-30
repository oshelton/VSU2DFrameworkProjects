/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREDATORMANAGER_H_INCLUDED
#define PREDATORMANAGER_H_INCLUDED

#include <list>

class Predator;
class Prey;

///Special class for mediating Predator/Prey relations.
class PredatorManager
{
private:
    ///List of Predators that have moved during the last update cycle.
    std::list<Predator*> movedPredators;
    ///List of Predators that haved changed states during the last update cycle.
    std::list<Predator*> stateChangedPredators;
    ///List of all Prey in the system.
    std::list<Prey*> listeningPrey;

public:

    ///Flush any deleted predators from the moved lists.
    void flushPredators();

    /** Register a new Prey animal to receive notifications from the PredatorManager.
    * \param prey The Prey animal to be registered.
    * \remark This is an internal method and is only called by an Environment when creating a new Prey animal.
    */
    void registerPrey(Prey* prey);
    /** Stop a Prey animal from receiving notifications from the PredatorManager.
    * \param prey The Prey animal to be removed.
    * \remark This is an internal method and is only called by an Environment when a Prey animal is destroyed.
    */
    void removePrey(Prey* prey);

    /** Notify the PredatorManager that a Predator has starved to death.
    * \param pre The Predator that starved.
    */
    void predatorStarved(Predator* pred);

    /** Notify the PredatorManager that a Predator has attacked a Prey.
    * \param attacker The Predator that performed the attack.
    * \param target The Prey animal attacked.
    */
    void predatorAttacked(Predator* attacker, Prey* target);
    /** Notify the PredatorManager that a Predator haschanged its state.
    * \param predator The Predator that has changed its state.
    */
    void predatorStateChanged(Predator* predator);
    /** Notify the PredatorManager that a Predator has moved.
    * \param predator The Predator that moved.
    */
    void predatorMoved(Predator* predator);
    ///Send the lists of moved and state changed Predators to the Prey.
    void update();
};

#endif // PREDATORMANAGER_H_INCLUDED
