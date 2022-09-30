/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef GAMEMANAGER_H_INCLUDED
#define GAMEMANAGER_H_INCLUDED

#include <string>
#include <map>
#include <hge.h>
#include "dll.h"

class Camera;
class ScriptManager;
class SceneManager;
class GuiManager;
class SystemState;
class Utils;
class InputManager;

class HGE;

///System management class.
class EXPORT_FRAME SystemManager
{
private:
    ///Core HGE object.
    HGE* hge;
    ///The system's current state.
    SystemState* currentState;
    ///Map of registered SystemStates.
    std::map<std::string, SystemState*> systemStates;

    ///Whether or not the SystemState should be changed at the start of the next frame.
    bool changeStateNextFrame;
    ///The new SystemState to switch to if changeStateNextFrame is true.
    std::string changeStateTo;

    ///Whether or not the application should exit at the start of the next frame.
    bool quitNextFrame;

    ///Bool used to makesure only one screenshot is produced at a time.
    bool printKeyDown;

    ///Pointer to the singleton instance of the class.
    static SystemManager* manager;

    ///Constructor.
    SystemManager();

public:
    ///Deconstructor.
    ~SystemManager();

    /**Start up the system, starts the rendring and update processes.
    * \param initialState The initial SystemState to start the System with.
    * \remark If no SystemState named initialState has been added to the SystemManager bad things will happen :).
    */
    void start(const std::string& initialState, const std::string& windowTitle);

    /** Save a copy of the current screen to a file.
    * \param fileName The file to save the screenshot to.
    * \remark This is slow, and there is nothing anyone can do about it.
    */
    void takeScreenshot(const std::string& fileName);

    ///Get the currently active SystemState.
    SystemState* getCurrentState();

    /**Register a new SystemState.
    * This method doesn't actually activate the state but makes it available for use by changeState.
    * \param state The SystemState to be added.
    * \remark If state has already been added nothing will happen.
    */
    void addSystemState(SystemState* state);
    /** Change the currently active SystemState.
    * \param newState The name of the SystemState to switch to.
    * \remark If newState does not match the name of any added SystemStates nothing will happen.
    */
    void changeState(const std::string newState);
    /** Safe method of changing SystemStates which ensures that the current frame finishes before the SystemState is switched.
    * \param state The name of the SystemState to switch to.
    * \remark If state does not match the name of any added SystemStates nothing will happen.
    */
    void changeStateNextUpdate(const std::string state);
    ///Exit the application safely at the start of the next frame.
    void quitNextUpdate();

    ///Wrapper for the HGE frame func, calls the SceneManager's update method.
    bool FrameFunc();
    ///Wrapper for the HGE render func, calls the SceneManager's render method.
    void RenderFunc();

    ///Get the width of the render window.
    const int getWindowWidth();
    ///Get the height of the render window.
    const int getWindowHeight();

    ///Get the core HGE object.
    HGE* getHGEManager();

    ///Singleton access method, returns a pointer to the SystemManager.
    static SystemManager* get();
};

#endif // GAMEMANAGER_H_INCLUDED
