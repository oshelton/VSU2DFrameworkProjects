/**
* \author Jack Owen Shelton
* CS4322 Project Predator VS. Prey Simulator.
* \date Spring 2009
*/

#ifndef SIMULATIONMANAGER_H_INCLUDED
#define SIMULATIONMANAGER_H_INCLUDED

#include <string>
#include <map>

enum UpdateStats
{
    MAX_FPS = 60,
    MIN_FPS = 15,
};

class PreyManager;
class PredatorManager;
class Environment;
class PredatorBehaviorFamily;
class PreyBehaviorFamily;
class SimpleRenderable;
class Camera;

///Main class for managing the simulation.
class SimulationManager
{
private:
    ///Pointer to the PreyManager object.
    PreyManager* preyManager;
    ///Pointer to the PredatorManager object.
    PredatorManager* predatorManager;

    ///Map of all Environments in the system.
    std::map<std::string, Environment*> environments;
    ///The currently used Environment.  This will default to the first Environment in environments when the system is initialized.
    Environment* currentEnvironment;

    ///Map of PredatorBehaviorFamilies.
    std::map<std::string, PredatorBehaviorFamily*> predatorFamilies;
    ///Map of PredatorBehaviorFamilies.
    std::map<std::string, PreyBehaviorFamily*> preyFamilies;

    ///Bool for determining if the simulation is paused or running.
    bool paused;
    ///Bool for determining if the simulation is currently actively running (There are animals left).
    bool active;

    ///Pointer to the background image.
    SimpleRenderable* background;
    ///Default camera.
    Camera* cam;

    ///Singleton pointer to the Singleton instance of SystemManager.
    static SimulationManager* manager;

    ///Old mouse position, used for moving the camera.
    hgeVector oldMousePosition;
    ///Old camera position, used for moving the background.
    hgeVector oldCameraPosition;
    ///UV coords of the background.
    hgeVector uvCoords;

    ///Since the simulation manually updates its timers the timeFactor is stored within the SimulationManager.
    double timeFactor;

    double remainingTime;

public:
    /** Constructor.
    * This method performs all initial object creation where all the Environments are initially created and the other core objects are created.
    * The SimulationManager is created in the constructor of the SimulationState class.
    */
    SimulationManager();
    ///Deconstructor.
    ~SimulationManager();

    /** Perform all creation activities that need access to the HGE object or other graphical resources.
    * This method is called from the createScene method of SimulationState.
    */
    void start();
    /** Special method that purges all Simulation specific from the current scene, including stopping and reseting all timers.
    * This method is called from the SimulationState clear method.
    */
    void stop();

    ///Get the currently active Environment, this will never return NULL.
    Environment* getActiveEnvironment();

    ///Get the PredatorManager, this method should only be called from within the simulation.
    PredatorManager* getPredatorManager(){ return predatorManager; }
    ///Get the PreyManager, this method should only be called from within the simulation.
    PreyManager* getPreyManager(){ return preyManager; }

    /** Set the currently active Environment.
    * \param environment The name of the Environment to switch to.
    * \remark If no Environment named environment exist nothing will happen.
    */
    void setActiveEnvironment(const std::string& environment);

    /** Get an Environment.
    * \param type The type name of the Environment to retrieve.
    */
    Environment* getEnvironment(const std::string& type);

    ///Return a map containing all existing Environments.
    const std::map<std::string, Environment*>& getEnvironments(){ return environments; }

    /** Get a PredatorBehaviorFamily.
    * \param family The name of the PredatorBehaviorFamily to retrieve.
    * \remark If no PredatorBehaviorFamily named family exists, NULL will be returned.
    */
    PredatorBehaviorFamily* getPredatorBehaviorFamily(const std::string& family);
    /** Get a PreyBehaviorFamily.
    * \param family The name of the PreyBehaviorFamily to retrieve.
    * \remark If no PreyBehaviorFamily named family exists, NULL will be returned.
    */
    PreyBehaviorFamily* getPreyBehaviorFamily(const std::string& family);

    ///Pause the simulation.
    void pause();
    ///Unpause the simulation.
    void unpause();
    ///Get whether or not the simulation is paused.
    const bool& isPaused();

    ///Activate the simulation, this is internal and should only be called by the active Environment when it starts a simulation.
    void activate();
    ///Deactivate the simulation, this is internal and should only be called by the active Environment when it starts a simulation.  This will also write the report to file.
    void deactivate();
    ///Get whether or not the simulation is active or not.
    const bool& isActive();

    /** Set the time factor, numbers < 1 mean time slows down, > 1 means time acceleration.
    * This method primarily affects timers, but will also influence movement speeds.
    * \param factor The new time factor value.
    * \remark Values <= 0 will be rejected.
    */
    void setTimeFactor(const double& factor);
    ///Get the current time factor.
    const double getTimeFactor();

    ///Get the time interval used for updates.
    const double getUpdateInterval();

    ///Update the simulation, called from SimulationState's FrameFunc.
    void update();

    ///Get the raw elapsed time since the simulation started.
    const double getSimulationElapsedTime();
    ///Get the simulation time as a string, formatted as HH/MM/SS Day #.
    const std::string getSimulationTime();

    ///Singleton access method.
    static SimulationManager* get();
};

#endif // SIMULATIONMANAGER_H_INCLUDED
