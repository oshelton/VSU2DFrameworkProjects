/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef TESTENVIRONMENT_H_INCLUDED
#define TESTENVIRONMENT_H_INCLUDED

#include "Environment.h"

///Simple Environment used for testing.
class TestEnvironment : public Environment
{
public:
    ///Constructor.
    TestEnvironment();
    ///Deconstructor.
    ~TestEnvironment();

    ///Get the type name of the Environment, in this case it is simply Test.
    const std::string getType(){ return "Test"; }

    ///Get the name of the sprite to use for the background.
    const std::string getBackgroundSpriteName(){ return "ground"; }

    ///Get the directory that stores the simulation scripts.
    const std::string getScriptDirectory(){ return "../resources/data/environments/test"; }

    /** Create a Predator.
    * This Environment subclass only handles the Test Predator type.
    * \param type, The type of Predator to create.
    * \param name The name of the Predator to create.
    * \param pos Where to place the created Predator.
    */
    Predator* createPredator(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0));

    /** Create a Prey.
    * This Environment subclass only handles the Test Prey type.
    * \param type, The type of Prey to create.
    * \param name The name of the Prey to create.
    * \param pos Where to place the created Prey.
    */
    Prey* createPrey(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0));
};

#endif // TESTENVIRONMENT_H_INCLUDED
