/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef PREYMANAGER_H_INCLUDED
#define PREYMANAGER_H_INCLUDED

#include <list>

class Predator;
class Prey;

///Special class for mediating Prey/Predator relations.
class PreyManager
{
private:
    ///List of Preys that have moved during the last update cycle.
    std::list<Prey*> movedPrey;
    ///List of Preys that haved changed states during the last update cycle.
    std::list<Prey*> stateChangedPrey;
    ///List of all Predators in the system.
    std::list<Predator*> listeningPredators;

    ///List that keeps track of any Predators that starved in the last update, used to prevent iterator invalidation.
    std::list<Predator*> starvedPredators;

public:

    ///Flush all predators from the simulation.
    void flushPredators();

    /** Register a new Predtor animal to receive notifications from the PreyManager.
    * \param prey The Predator animal to be registered.
    * \remark This is an internal method and is only called by an Environment when creating a new Predator animal.
    */
    void registerPredator(Predator* predator);
    /** Stop a Predator animal from receiving notifications from the PreyManager.
    * \param prey The Prey animal to be removed.
    * \remark This is an internal method and is only called by an Environment when a Predator animal is destroyed.
    */
    void removePredator(Predator* predator);

    /** Removes an attcked Prey animal from the movedPrey and stateChangedPrey lists.
    * \param prey The animal attacked.
    */
    void preyAttacked(Prey* prey);

	/** Notify the PreyManager that a Prey animal has spotted a Predator.
	* \param prey The Prey animal that has noticed a Predator.
	* \param predator The Predator that bas been spotted.
	*/
	void preyNoticesPredator(Prey* prey, Predator* predator);
	/** Notify the PreyManager that a Prey has changed its state.
    * \param prey The Prey that has changed its state.
    */
    void preyStateChanged(Prey* prey);
    /** Notify the PreyManager that a Prey has moved.
    * \param prey The Prey that moved.
    */
    void preyMoved(Prey* prey);

    ///Send the lists of moved and state changed Prey to the Predators.
    void update();
};

#endif // PREYMANAGER_H_INCLUDED
