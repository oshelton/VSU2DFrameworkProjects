/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef SWAMPENVIRONMENT_H_INCLUDED
#define SWAMPENVIRONMENT_H_INCLUDED

#include "Environment.h"

///Simple south Georgian swamp environment.
class SwampEnvironment : public Environment
{
public:
    ///Constructor.
    SwampEnvironment();
    ///Deconstructor.
    ~SwampEnvironment();

    ///Get the type name of the Environment, in this case it is simply Test.
    const std::string getType(){ return "Swamp"; }

    ///Get the name of the sprite to use for the background.
    const std::string getBackgroundSpriteName(){ return "swamp"; }

    ///Get the directory that stores the simulation scripts.
    const std::string getScriptDirectory(){ return "../resources/data/environments/swamp"; }

    /** Create a Predator.
    * \param type, The type of Predator to create.
    * \param name The name of the Predator to create.
    * \param pos Where to place the created Predator.
    * \remark This Environment supports Alligator, Black Bear, and Bobcat Predator species.
    */
    Predator* createPredator(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0));

    /** Create a Prey.
    * \param type, The type of Prey to create.
    * \param name The name of the Prey to create.
    * \param pos Where to place the created Prey.
    * \remark This Environment supports Deer, Possum, and Rabbit Prey species.
    */
    Prey* createPrey(const std::string& type, const std::string& name, const hgeVector& pos = hgeVector(0, 0));
};

#endif // SWAMPENVIRONMENT_H_INCLUDED
