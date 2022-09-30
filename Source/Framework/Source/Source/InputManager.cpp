/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <angelscript.h>
#include <hge.h>
#include "ScriptManager.h"
#include "SystemManager.h"
#include "InputManager.h"

InputManager* InputManager::input(NULL);

InputManager::~InputManager()
{
    input = NULL;
}

bool InputManager::keyDown(int key)
{
    return SystemManager::get()->getHGEManager()->Input_KeyDown(key);
}

bool InputManager::keyUp(int key)
{
    return SystemManager::get()->getHGEManager()->Input_KeyUp(key);
}

bool InputManager::getKeyState(int key)
{
    return SystemManager::get()->getHGEManager()->Input_GetKeyState(key);
}

int InputManager::getKey()
{
    return SystemManager::get()->getHGEManager()->Input_GetKey();
}

hgeVector InputManager::getMousePosition()
{
    float x =0, y = 0;
    SystemManager::get()->getHGEManager()->Input_GetMousePos(&x, &y);
    return hgeVector(x, y);
}

void InputManager::setMousePosition(hgeVector pos)
{
    SystemManager::get()->getHGEManager()->Input_SetMousePos(pos.x, pos.y);
}

int InputManager::getMouseWheelRelative()
{
    return SystemManager::get()->getHGEManager()->Input_GetMouseWheel();
}

InputManager* InputManager::get()
{
    if (input == NULL)
        input = new InputManager();

    return input;
}
