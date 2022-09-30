/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef GUIMANAGER_H_INCLUDED
#define GUIMANAGER_H_INCLUDED

#include <string>
#include <list>
#include "dll.h"

namespace CEGUI
{
    class HgeRenderer;
    class System;
    class WindowManager;
    class Window;

    class Listbox;
    class Combobox;
    class ProgressBar;
    class PushButton;
    class Checkbox;
    class RadioButton;
    class Slider;
    class Editbox;

    class EventArgs;
}

class HGE;

///This class manages CEGUI with very little direct intervention.
class EXPORT_FRAME GuiManager
{
private:
    ///Pointer to the HGE CEGUI renderer.
    CEGUI::HgeRenderer* guiRenderer;
    ///Pointer to the core CEGUI object.
    CEGUI::System* guiSystem;
    ///Pointer to the CEGUI WindowManager.
    CEGUI::WindowManager* winManager;
    ///Pointer to the CEGUI root Window.
    CEGUI::Window* rootWindow;
    ///Pointer to the CEGUI Window that serves as the console.
    CEGUI::Window* consoleWindow;
    ///Name of the layout file that contains the console Window.
    std::string consoleWindowLayoutFile;
    ///Name of the Console Window.
    std::string consoleWindowName;

    ///Pointer to the singleton instance of the class.
    static GuiManager* manager;

    ///Bool used for keeping track of whether the console is currently available or not.
    bool consoleLoaded;

    ///Bool used for keeping track of whether the left mouse button was pushed last frame.
    bool leftButtonDown;
    ///Bool used for keeping track of whether the right mouse button was pushed last frame.
    bool rightButtonDown;

    /** Constructor.
    * \param hge Simply a pointer to the core HGE object.
    */
    GuiManager();

public:
    ///Deconstructor.
    ~GuiManager();

    ///Initializa the GUI, can't go in the constructor since a RenderWindow needs to exist before the CEGUI renderer is created.
    void initialize();

    /** Set the scheme file used by CEGUI.
    * \param schemeFile File name of the scheme file.
    */
    void setSchemeFile(const std::string& schemeFile);
    /** Set the cursor to be used by CEGUI.
    * \param imageSet File nameof the ImageSet the cursor image can be found in.
    * \param image Name of the image from the ImageSet to use for the cursor.
    */
    void setDefaultCursor(const std::string& imageSet, const std::string& image);
    /** Set the default font used by CEGUI.
    * \param fontName File name of the font.
    */
    void setDefaultFont(const std::string& fontName);

    /** Set the layout used by the console.
    * \param fileName File name of the layout file to use.
    */
    void setConsoleLayoutFile(const std::string& fileName);
    /** Set the name of the Window used for the console.
    * \param name Name of the Window to be used.
    */
    void setConsoleName(const std::string& name);
    /** Write a message to the console.
    * \param text The message to be written to the console.
    */
    void writeToConsole(const std::string& text);
    ///Get the console Window.
    CEGUI::Window* getConsole();
    ///Clear the console of any messages.
    void clearConsole();

    /** Load a new layout, replacing the current one.
    * \param layoutFile File name of the layout to be loaded.
    */
    void loadLayout(const std::string& layoutFile);
    ///Clear the current layout, removes and detroys all widgets.
    void clear();

    /** Get a Window.
    * \param name Name of the Window to retrieve.
    * \return Returns the Window with name as its name or NULL if one does not exist.
    */
    CEGUI::Window* getWindow(const std::string& name);
    /** Get a Listbox.
    * \param name Name of the Listbox to retrieve.
    * \return Returns the Listbox with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::Listbox* getListbox(const std::string& name);
    /** Get a Combobox.
    * \param name Name of the Combobox to retrieve.
    * \return Returns the Comboboxwith name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::Combobox* getCombobox(const std::string& name);
    /** Get a PushButton (Regular button).
    * \param name Name of the PushButton to retrieve.
    * \return Returns the PushButton with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::PushButton* getButton(const std::string& name);
    /** Get a ProgressBar.
    * \param name Name of the ProgressBar to retrieve.
    * \return Returns the ProgressBar with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::ProgressBar* getBar(const std::string& name);
    /** Get a Checkbox.
    * \param name Name of the Checkbox to retrieve.
    * \return Returns the Checkbox with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::Checkbox* getCheckbox(const std::string& name);
    /** Get a RadioButton.
    * \param name Name of the RadioButton to retrieve.
    * \return Returns the RadioButton with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::RadioButton* getRadioButton(const std::string& name);
    /** Get a Slider.
    * \param name Name of the Slider to retrieve.
    * \return Returns the Slider with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::Slider* getSlider(const std::string& name);
    /** Get a Editbox (text box).
    * \param name Name of the Editbox to retrieve.
    * \return Returns the Editbox with name as its name or NULL if one does not exist or the type is incorrect.
    */
    CEGUI::Editbox* getEditbox(const std::string& name);

    ///Hide the mouse cursor.
    void hideMouse();
    ///Show the mouse cursor.
    void showMouse();

    /// Update CEGUI.
    void update();
    ///Render CEGUI.
    void render();

    ///Singleton access method, returns a pointer to the GuiManager.
    static GuiManager* get();
};

#endif // GUIMANAGER_H_INCLUDED
