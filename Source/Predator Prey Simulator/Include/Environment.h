/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef ENVIRONMENT_H_INCLUDED
#define ENVIRONMENT_H_INCLUDED

#include <map>
#include <list>
#include <string>
#include <hgevector.h>
#include <BindableManaged.h>

class Predator;
class Prey;

/**Class responsible for creating animals.
* This class serves as the abstract factory class in the abstract factory pattern.
*/
class Environment : public BindableManaged
{
protected:
    ///Counter,used for generating names for predators when the no name createPredator method is called.
    unsigned long predatorCounter;
    ///Counter,used for generating names for prey when the no name createPrey method is called.
    unsigned long preyCounter;

    ///Used to determine whether or not a simulation is currently running.
    bool simulationRunning;

    ///Map of all existing predators.
    std::map<std::string, Predator*> predators;
    ///Map of all existing prey.
    std::map<std::string, Prey*>prey;

    ///Initialize the environment.
    void init();

public:
    ///Required virtual deconstructor.
    virtual ~Environment(){}

    ///Get the type of the environment, will usually be something like "African Savannah" or "Pacific Northwest"
    virtual const std::string getType() = 0;
    ///Get the name of the Sprite to be used for the background with this environment.
    virtual const std::string getBackgroundSpriteName() = 0;

    ///Get the directory where the simulation scripts for the Environment are stored.
    virtual const std::string getScriptDirectory() = 0;
    ///Get the file names of all files found within the Enviroment's script directory.  This is used in conjunction with getScriptDirectory to load and compile the simulation script.
    virtual const std::list<std::string> getFileNames();
    /** Load a simulation from a file.
    * \param fileName The file name of the simulation to load.
    * \remark Only the name of the file is needed, the drectory can be obtained through the getScriptDirectory method.
    */
    void loadSimulation(const std::string& fileName);

    /** Create a new Predator.
    * \param type Specific type of predator to create.
    * \param pos The location at which to place the Predator.
    * \remark If no predator type named type is handled in the subclass calling this method NULL will be returned.
    * \remark This method assumes a default name made of the type plus the current value of the predator counter.
    * \remark If that name is already in use the already existing predator will be returned.
    */
    Predator* createPredator(const std::string& type, const hgeVector& pos = hgeVector(0, 0));
    /** Create a new Predator.
    * This method is implemented by subclasses to support different kinds of predators.
    * \param type Specific type of predator to create.
    * \param name The name to be given to the Predator.
    * \param pos The location at which to place the Predator.
    * \remark If a Predator named name already exists the previously existing Predator will be returned.
    * \remark If no predator type named type is handled in the subclass calling this method NULL will be returned.
    */
    virtual Predator* createPredator(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0)) = 0;
    /** Destroy a predator.
    *\param name The name of the predator to destroy.
    * \remark If no Predator named name exists this method will do nothing.
    */
    void killPredator(const std::string& name);
    /** Destroy a predator.
    * \param animal A pointer to the predator to destroy.
    */
    void killPredator(Predator* animal);

    /** Create a new Prey.
    * \param type Specific type of Prey to create.
    * \param pos The location at which to place the Predator.
    * \remark If no Prey type named type is handled in the subclass calling this method NULL will be returned.
    * \remark This method assumes a default name made of the type plus the current value of the prey counter.
    * \remark If that name is already in use the already existing prey will be returned.
    */
    Prey* createPrey(const std::string& type, const hgeVector& pos = hgeVector(0, 0));
    /** Create a new Prey.
    * This method is implemented by subclasses to support different kinds of predators.
    * \param type Specific type of Prey to create.
    * \param name The name to be given to the Predator.
    * \param pos The location at which to place the Predator.
    * \remark If a Prey named name already exists the previously existing Prey will be returned.
    * \remark If no Prey type named type is handled in the subclass calling this method NULL will be returned.
    */
    virtual Prey* createPrey(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0)) = 0;
    /** Destroy a Prey.
    *\param name The name of the Prey to destroy.
    * \remark If no Prey named name exists this method will do nothing.
    */
    void killPrey(const std::string& name);
    /** Destroy a Prey.
    * \param animal A pointer to the Prey to destroy.
    */
    void killPrey(Prey* animal);

    ///Kill all Animals in the Environment.
    void clearEnvironment();

    ///Called by the Simulationmanager, used to stop the simulation when no more predators remain.
    void update();
};

#endif // ENVIRONMENT_H_INCLUDED
