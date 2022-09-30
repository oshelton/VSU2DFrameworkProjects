/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include <hgevector.h>
#include "dll.h"

class HGE;

///Input management class.
class EXPORT_FRAME InputManager
{
private:
    ///Pointer to the singleton instance of the class.
    static InputManager* input;

public:
    ///Deconstructor.
    ~InputManager();

    /** Check if a key is down (pressed).
    * \param key The KeyCode of the key to check.
    */
    bool keyDown(int key);
    /** Check if a key is up(not pressed).
    * \param key The KeyCode of the key to check.
    */
    bool keyUp(int key);
    /** Check if a key is up or down.
    * \param key The KeyCode to check.
    * \return True if key is down, false if not.
    */
    bool getKeyState(int key);
    /** Get the last key pressed since the last update.
    * \return The KeyCode of the key pressed.
    */
    int getKey();

    ///Get the mouses position.
    hgeVector getMousePosition();
    /** Set the mouse's pposition.
    * \param pos This vector repereents the new mouse coordinates, in screen space (0 - screen width, 0 - screen height).
    */
    void setMousePosition(hgeVector pos);
    /** Get the relative movement of the mouse scroll wheel since the last update.
    * \return This method returns the number of notches the mouse wheel was scrolled, it will be positive if it was scrolled forward, negative if backward.
    */
    int getMouseWheelRelative();

    ///Singleton access method, returns a pointer to the InputManager.
    static InputManager* get();
};

#endif // INPUTMANAGER_H_INCLUDED
