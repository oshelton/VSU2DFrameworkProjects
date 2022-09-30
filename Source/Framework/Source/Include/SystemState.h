/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SYSTEMSTATE_H_INCLUDED
#define SYSTEMSTATE_H_INCLUDED

#include "UpdateListener.h"
#include <string>
#include "dll.h"

class HGE;
class SystemManager;
class ScriptManager;
class SceneManager;

///Represents a self-supporting state in the system, also referred to as a game states.
class EXPORT_FRAME SystemState
{
protected:
    ///Boolean for storing weather or not the SystemState is paused.
    bool paused;

public:
    ///Required virtual deconstructor.
    virtual ~SystemState(){}

    ///Get the name of the SystemState.
    virtual std::string getName() = 0;

    /** Create the SystemState's associated scene.
    * This typically loads the SystemState's GUI layout and sets up events and any initiall scene objects.
    */
    virtual void createScene() = 0;
    /** This method clears the SystemState.
    * This method calls SceneManager::clearScene and GuiManager::clear().
    */
    virtual void clear() = 0;

    ///Get whether the SystemState is paused or not.
    bool isPaused(){return paused;}
    /** Set the SystemState to be paused or unpaused.
    * \param paused True if theSystemState should be paused or false if it should be unpaused.
    */
    void setPaused(bool paused){this->paused = paused;}

    ///Frame update func, called by the SystemManager.
    virtual void FrameFunc() = 0;
};

#endif // SYSTEMSTATE_H_INCLUDED
