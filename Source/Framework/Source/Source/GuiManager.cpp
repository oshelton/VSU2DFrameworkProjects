/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <angelscript.h>
#include <CEGUI.h>
#include "HgeRenderer.h"
#include "SystemManager.h"
#include "ScriptManager.h"
#include "Utils.h"
#include "InputManager.h"
#include "GuiManager.h"

using namespace CEGUI;
using namespace std;

GuiManager* GuiManager::manager(NULL);

GuiManager::GuiManager() : rootWindow(NULL), consoleWindow(NULL), guiRenderer(NULL), guiSystem(NULL), consoleWindowLayoutFile(""),  consoleWindowName(""), consoleLoaded(false),
                           leftButtonDown(false), rightButtonDown(false)
{
}

GuiManager::~GuiManager()
{
    winManager->destroyWindow(rootWindow);
    winManager = NULL;
    delete guiSystem;
    delete guiRenderer;
    manager = NULL;
}

void GuiManager::initialize()
{
    guiRenderer = new HgeRenderer();
    guiSystem = new System(guiRenderer);

    winManager = WindowManager::getSingletonPtr();

    setSchemeFile("..\\resources\\gui\\schemes\\TaharezLookSkin.scheme");
    setDefaultCursor("TaharezLook", "MouseArrow");
    setConsoleLayoutFile("..\\resources\\gui\\layouts\\console.layout");
    setDefaultFont("BlueHighway-12");
    setConsoleName("console");
}

void GuiManager::setSchemeFile(const string& scheme)
{
    CEGUI::SchemeManager::getSingleton().loadScheme(scheme);
}

void GuiManager::setDefaultCursor(const string& imageSet, const string& image)
{
    guiSystem->setDefaultMouseCursor(imageSet, image);
}

void GuiManager::setDefaultFont(const string& font)
{
    guiSystem->setDefaultFont(font);
}

void GuiManager::setConsoleLayoutFile(const string& file)
{
    consoleWindowLayoutFile = file;
}

void GuiManager::setConsoleName(const string& name)
{
    consoleWindowName = name;
}

void GuiManager::writeToConsole(const string& text)
{
    if (guiSystem != NULL && consoleLoaded)
    {
        Listbox* tmp = static_cast<Listbox*>(getWindow(consoleWindowName));
        ListboxTextItem* item = new ListboxTextItem(text);
        tmp->addItem(item);
    }
}

Window* GuiManager::getConsole()
{
    return consoleWindow;
}

void GuiManager::clearConsole()
{
    static_cast<Listbox*>(getWindow(consoleWindowName))->resetList();
}

void GuiManager::loadLayout(const string& layoutFile)
{
    clear();
    consoleLoaded = true;
    rootWindow = winManager->loadWindowLayout(layoutFile);
    guiSystem->setGUISheet(rootWindow);
    rootWindow->show();
    rootWindow->setMouseAutoRepeatEnabled(false);

    consoleWindow = winManager->loadWindowLayout(consoleWindowLayoutFile);
    consoleWindow->hide();
    rootWindow->addChildWindow(consoleWindow);
}

void GuiManager::clear()
{
    consoleLoaded = false;
    winManager->destroyAllWindows();
    guiSystem->removeAllEvents();
}

Window* GuiManager::getWindow(const string& name)
{
    return winManager->getWindow(name);
}

Listbox* GuiManager::getListbox(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Listbox")
        return static_cast<Listbox*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to Listbox.");
        return NULL;
    }
}

Combobox* GuiManager::getCombobox(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Combobox")
        return static_cast<Combobox*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to Combobox.");
        return NULL;
    }
}

PushButton* GuiManager::getButton(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Button")
        return static_cast<PushButton*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to PushButton.");
        return NULL;
    }
}

ProgressBar* GuiManager::getBar(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/ProgressBar")
        return static_cast<ProgressBar*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to ProgressBar.");
        return NULL;
    }
}

Checkbox* GuiManager::getCheckbox(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Checkbox")
        return static_cast<Checkbox*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to Checkbox.");
        return NULL;
    }
}

RadioButton* GuiManager::getRadioButton(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/RadioButton")
        return static_cast<RadioButton*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to RadioButton.");
        return NULL;
    }
}

Slider* GuiManager::getSlider(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Slider")
        return static_cast<Slider*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to Slider.");
        return NULL;
    }
}

Editbox* GuiManager::getEditbox(const string& name)
{
    Window* tmp = winManager->getWindow(name);
    if (tmp->getType() == "TaharezLook/Editbox")
        return static_cast<Editbox*>(tmp);
    else
    {
        writeToConsole(name + " cannot be cast to Editbox.");
        return NULL;
    }
}

void GuiManager::hideMouse()
{
    MouseCursor::getSingletonPtr()->hide();
}

void GuiManager::showMouse()
{
    MouseCursor::getSingletonPtr()->show();
}

void GuiManager::update()
{
    HGE* hge = SystemManager::get()->getHGEManager();
    guiSystem->injectChar(hge->Input_GetKey());

    if (hge->Input_GetKey() == HGEK_LEFT && hge->Input_KeyDown(HGEK_LEFT))
        guiSystem->injectKeyDown(Key::ArrowLeft);
    else if (hge->Input_GetKey() == HGEK_RIGHT && hge->Input_KeyDown(HGEK_RIGHT))
        guiSystem->injectKeyDown(Key::ArrowRight);
    else if (hge->Input_GetKey() == HGEK_UP && hge->Input_KeyDown(HGEK_UP))
        guiSystem->injectKeyDown(Key::ArrowUp);
    else if (hge->Input_GetKey() == HGEK_DOWN && hge->Input_KeyDown(HGEK_DOWN))
        guiSystem->injectKeyDown(Key::ArrowDown);
    else if (hge->Input_GetKey() == HGEK_BACKSPACE && hge->Input_KeyDown(HGEK_BACKSPACE))
        guiSystem->injectKeyDown(Key::Backspace);
    else if (hge->Input_GetKey() != 0 && hge->Input_KeyDown(hge->Input_GetKey()))
        guiSystem->injectKeyDown(hge->Input_GetKey());


    if (hge->Input_GetKey() == HGEK_LEFT && hge->Input_KeyUp(HGEK_LEFT))
        guiSystem->injectKeyUp(Key::ArrowLeft);
    else if (hge->Input_GetKey() == HGEK_RIGHT && hge->Input_KeyUp(HGEK_RIGHT))
        guiSystem->injectKeyUp(Key::ArrowRight);
    else if (hge->Input_GetKey() == HGEK_UP && hge->Input_KeyUp(HGEK_UP))
        guiSystem->injectKeyUp(Key::ArrowUp);
    else if (hge->Input_GetKey() == HGEK_DOWN && hge->Input_KeyUp(HGEK_DOWN))
        guiSystem->injectKeyUp(Key::ArrowDown);
    else if (hge->Input_GetKey() == HGEK_BACKSPACE && hge->Input_KeyUp(HGEK_BACKSPACE))
        guiSystem->injectKeyUp(Key::Backspace);
    else if (hge->Input_GetKey() != 0 && hge->Input_KeyUp(hge->Input_GetKey()))
        guiSystem->injectKeyUp(hge->Input_GetKey());

    if (!hge->Input_IsMouseOver())
        guiSystem->injectMouseLeaves();

    if (hge->Input_GetKeyState(HGEK_LBUTTON) && !leftButtonDown)
        guiSystem->injectMouseButtonDown(LeftButton);
    else if (!hge->Input_GetKeyState(HGEK_LBUTTON) && leftButtonDown)
        guiSystem->injectMouseButtonUp(LeftButton);

    if (hge->Input_GetKeyState(HGEK_RBUTTON) && !rightButtonDown)
        guiSystem->injectMouseButtonDown(RightButton);
    else if (!hge->Input_GetKeyState(HGEK_RBUTTON) && rightButtonDown)
        guiSystem->injectMouseButtonUp(RightButton);

    if (hge->Input_GetKeyState(HGEK_LBUTTON))
        leftButtonDown = true;
    else
        leftButtonDown = false;

    if (hge->Input_GetKeyState(HGEK_RBUTTON))
        rightButtonDown = true;
    else
        rightButtonDown = false;

    float x, y;
    x = y = 0;
    hge->Input_GetMousePos(&x, &y);
    guiSystem->injectMousePosition(x, y);

    guiSystem->injectTimePulse(hge->Timer_GetDelta());
}

void GuiManager::render()
{
    guiSystem->renderGUI();
}

GuiManager* GuiManager::get()
{
    if (manager == NULL)
        manager = new GuiManager();

    return manager;
}
