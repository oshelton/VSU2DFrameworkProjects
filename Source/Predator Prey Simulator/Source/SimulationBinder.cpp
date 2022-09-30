/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#include <string>
#include <angelscript.h>
#include <hgevector.h>
#include "SimulationManager.h"
#include "Environment.h"
#include "SimulationBinder.h"

using namespace std;

void createPredatorName(const string& type, const string& name, hgeVector position)
{
    SimulationManager::get()->getActiveEnvironment()->createPredator(type, name, position);
}

void createPredator(const string& type, hgeVector position)
{
    SimulationManager::get()->getActiveEnvironment()->createPredator(type, position);
}

void createPreyName(const string& type, const string& name, hgeVector position)
{
    SimulationManager::get()->getActiveEnvironment()->createPrey(type, name, position);
}

void createPrey(const string& type, hgeVector position)
{
    SimulationManager::get()->getActiveEnvironment()->createPrey(type, position);
}

void SimulationBinder::bind(asIScriptEngine* engine)
{
    int r = 0;
    r = engine->RegisterGlobalFunction("void createPredator(const string&, const string&, Vector2)", asFUNCTION(createPredatorName), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalFunction("void createPredator(const string&, Vector2)", asFUNCTION(createPredator), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalFunction("void createPrey(const string&, const string&, Vector2)", asFUNCTION(createPreyName), asCALL_CDECL); assert (r >= 0);
    r = engine->RegisterGlobalFunction("void createPrey(const string&, Vector2)", asFUNCTION(createPrey), asCALL_CDECL); assert (r >= 0);
}
