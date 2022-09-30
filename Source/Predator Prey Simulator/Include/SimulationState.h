/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef SIMULATIONSTATE_H_INCLUDED
#define SIMULATIONSTATE_H_INCLUDED

#include <SystemState.h>

class SimulationManager;

///SystemState through which the simulation is controlled and updated.
class SimulationState : public SystemState
{
private:
    ///Conveniance pointer to the SimulationManager.
    SimulationManager* manager;

public:
    ///Constructor.
    SimulationState();
    ///Deconstructor.
    ~SimulationState();

    ///Get the name of the SimulationState.
    std::string getName(){ return "SimulationState";}

    ///Create the scene, start the simulation.
    void createScene();

    ///Clear the scene, stop the simulation.
    void clear();

    ///Update function, updates the simulation.
    void FrameFunc();
};

#endif // SIMULATIONSTATE_H_INCLUDED
