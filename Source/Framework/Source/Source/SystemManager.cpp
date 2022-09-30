/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hge.h>
#include <hgeresource.h>
#include <CEGUIWindow.h>
#include <hgesprite.h>
#include "ScriptManager.h"
#include "SceneManager.h"
#include "GuiManager.h"
#include "Camera.h"
#include "TimerManager.h"
#include "Utils.h"
#include "InputManager.h"
#include "angelscript.h"
#include "UtilBinder.h"
#include "SystemState.h"
#include "SimpleRenderableCreator.h"
#include "LineRenderableCreator.h"
#include "CompoundRenderableCreator.h"
#include "TextRenderableCreator.h"
#include "TriangleRenderableCreator.h"
#include "RenderTextureManager.h"
#include "SystemManager.h"

using namespace std;

// This function will be called by HGE once per frame.
// Put your game loop code here. In this example we
bool BaseFrameFunc()
{
    return SystemManager::get()->FrameFunc();
}

bool BaseRenderFunc()
{
    SystemManager::get()->RenderFunc();
    return false;
}

SystemManager* SystemManager::manager(NULL);

SystemManager::SystemManager() : hge(NULL), currentState(NULL), changeStateNextFrame(false), changeStateTo(""), quitNextFrame(false), printKeyDown(false)
{
    Utils::get()->writeToLog("Log initialized.");
    Utils::get()->writeToLog("Created general utilities.");

    TimerManager::get();
    Utils::get()->writeToLog("Created timer manager.");

    ScriptManager::get();
    Utils::get()->writeToLog("Created script manager.");

    SceneManager::get()->registerComponentType("SimpleRenderable", new SimpleRenderableCreator());
    SceneManager::get()->registerComponentType("LineRenderable", new LineRenderableCreator());
    SceneManager::get()->registerComponentType("CompoundRenderable", new CompoundRenderableCreator());
    SceneManager::get()->registerComponentType("TextRenderable", new TextRenderableCreator());
    SceneManager::get()->registerComponentType("TriangleRenderable", new TriangleRenderableCreator());

    Utils::get()->writeToLog("Creating scene manager.");
    InputManager::get();
    Utils::get()->writeToLog("Created input manager.");
    GuiManager::get();
    Utils::get()->writeToLog("Created gui manager.");
    RenderTextureManager::get();
    Utils::get()->writeToLog("Created render texture manager.");

    // Here we use global pointer to HGE interface.
    // Instead you may use hgeCreate() every
    // time you need access to HGE. Just be sure to
    // have a corresponding hge->Release()
    // for each call to hgeCreate()
    hge = HGE::hgeCreate(HGE_VERSION);
    if (hge == NULL)
        Utils::get()->writeToLog("Error creating HGE object.");
}

void SystemManager::start(const string& initialState, const string& windowTitle)
{

    // Set the window title
    hge->System_SetState(HGE_TITLE, windowTitle.c_str());

    // Run in windowed mode
    // Default window size is 800x600
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_SCREENWIDTH, 800);
    hge->System_SetState(HGE_SCREENHEIGHT, 600);
    hge->System_SetState(HGE_SCREENBPP, 32);

    hge->System_SetState(HGE_LOGFILE, "HGE Log.txt");
    hge->System_SetState(HGE_USESOUND, false);

    hge->System_SetState(HGE_FPS, 60);
    hge->System_SetState(HGE_ZBUFFER, true);
    hge->System_SetState(HGE_SHOWSPLASH,false);

    // Set our frame function
    hge->System_SetState(HGE_FRAMEFUNC, BaseFrameFunc);
    //Set the render function
    hge->System_SetState(HGE_RENDERFUNC, BaseRenderFunc);

    // Tries to initiate HGE with the states set.
    // If something goes wrong, "false" is returned
    // and more specific description of what have
    // happened can be read with System_GetErrorMessage().

    ScriptManager::get()->addBindings(new UtilBinder());

    if (hge->System_Initiate())
    {
        hge->System_Initiate();

        GuiManager::get()->initialize();
        changeState(initialState);

        hge->System_Start();
    }
    else
    {
        // If HGE initialization failed show error message
        MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
}

void SystemManager::takeScreenshot(const string& fileName)
{
    hge->System_Snapshot(fileName.c_str());
}

SystemManager::~SystemManager()
{
    map<string, SystemState*>::iterator iter;
    for (iter= systemStates.begin(); iter != systemStates.end(); ++iter)
    {
        SystemState* tmp = iter->second;
        delete tmp;
    }
    systemStates.clear();

    delete ScriptManager::get();
    delete GuiManager::get();
    delete InputManager::get();
    delete RenderTextureManager::get();
    delete Utils::get();
    delete SceneManager::get();
    manager = NULL;

    // Release the HGE interface.
    // If there are no more references,
    // the HGE object will be deleted.
    hge->Release();

    // Restore video mode and free
    // all allocated resources
    hge->System_Shutdown();
}

SystemState* SystemManager::getCurrentState()
{
    return currentState;
}

void SystemManager::addSystemState(SystemState* state)
{
    map<string, SystemState*>::iterator iter;
    for (iter = systemStates.begin(); iter != systemStates.end(); ++iter)
    {
        if (iter->second == state)
        {
            Utils::get()->writeToLog("An instance of the [" + state->getName() + "] state already exists, ignoring.");
            return;
        }
    }

    systemStates[state->getName()] = state;
}

void SystemManager::changeState(const string newState)
{
    if (systemStates.find(newState) != systemStates.end())
    {
        GuiManager::get()->clear();
        if (currentState != NULL)
            currentState->clear();

        TimerManager::get()->clearTimers();

        changeStateNextFrame = false;
        changeStateTo = "";

        currentState = systemStates[newState];
        currentState->createScene();
        Utils::get()->writeToLog("Switching SystemState to: " + newState + ".");
    }
    else
        Utils::get()->writeToLog("No SystemState named " + newState + " exists, ignoring.");
}

void SystemManager::changeStateNextUpdate(const string state)
{
    changeStateNextFrame = true;
    changeStateTo = state;
}

void SystemManager::quitNextUpdate()
{
    quitNextFrame = true;
}

bool SystemManager::FrameFunc()
{
    if (quitNextFrame)
        return true;
    if (changeStateNextFrame)
    {
        changeStateNextFrame = false;
        changeState(changeStateTo);
    }

    if (hge->Input_GetKey() == HGEK_PAUSE && !printKeyDown)
        takeScreenshot("screen shot.png");

    if (hge->Input_GetKey() == HGEK_PAUSE)
        printKeyDown = true;
    else
        printKeyDown = false;

    if (currentState != NULL)
    {
        TimerManager::get()->update();
        if (hge->Input_KeyDown(HGEK_COMMA))
            GuiManager::get()->getConsole()->setVisible(!GuiManager::get()->getConsole()->isVisible());
        GuiManager::get()->update();
        currentState->FrameFunc();
    }

    return false;
}

void SystemManager::RenderFunc()
{
    if (currentState != NULL)
    {
        hge->Gfx_BeginScene();
        hge->Gfx_Clear(0);

        SceneManager::get()->render();
        GuiManager::get()->render();
        hge->Gfx_EndScene();
    }
}

const int SystemManager::getWindowWidth()
{
    return hge->System_GetState(HGE_SCREENWIDTH);
}

const int SystemManager::getWindowHeight()
{
    return hge->System_GetState(HGE_SCREENHEIGHT);
}

HGE* SystemManager::getHGEManager()
{
    return hge;
}

SystemManager* SystemManager::get()
{
    if (manager == NULL)
        manager = new SystemManager();

    return manager;
}
