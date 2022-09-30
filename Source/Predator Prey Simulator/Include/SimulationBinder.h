/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef SIMULATIONBINDER_H_INCLUDED
#define SIMULATIONBINDER_H_INCLUDED

#include <ScriptBinder.h>

/** Class that generates AngelScript bindings for the core SimulationManager and Environment functionality needed to load simulations.
* The source file associated with this header includes functions to simplify Predator and Prey creation.
* This class registers four global functions, createPredator(type, name, position), createPredator(type, position), createPrey(type, name, position), and createPrey(type,position) all of which return void.
* This class only gives access to the ability to load animals into a simulation and nothing else.
*/
class SimulationBinder : public ScriptBinder
{
public:
    /** Method that generates the bindings needed to load simulations.
    * \param engine The AngelScript script engine that the bindings are to begenerated for and with.
    */
    void bind(asIScriptEngine* engine);
};

#endif // SIMULATIONBINDER_H_INCLUDED
