/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SCRIPTMANAGER_H_INCLUDED
#define SCRIPTMANAGER_H_INCLUDED

#include <string>
#include "dll.h"

class hgeResourceManager;
class asIScriptEngine;
class asIScriptContext;
class ScriptBinder;

///This class manages the AngelScript objects and simplifies the script building interface.
class EXPORT_FRAME ScriptManager
{
private:
    ///Pointer to the AngelScript scripting engine.
    asIScriptEngine* engine;
    ///Pointer to the AngelScript script context which is used for calling script functions and objects.
    asIScriptContext* context;
    ///Pointer to the hgeResourceManager, which is used for managing graphical resources.
    hgeResourceManager* rManager;

	///Singleton access method, returns a pointer to the ScriptManager.
    static ScriptManager* manager;

    ///Constructor.
    ScriptManager();

public:
	///Deconstructor.
    ~ScriptManager();

	///Get the AngelScript scripting engine.
    asIScriptEngine* getScriptEngine();
	///Get the AngelScript script context.
    asIScriptContext* getScriptContext();
	///Get the hgeResourceManager, used for retrieving graphical resources.
    hgeResourceManager* getResourceManager();

	/** Add bindings to the ScriptManager.
	* \param binder The object to use to generate the bindings.
	* \remark The passed object will be deleted once the bindings have been generated.
	*/
	void addBindings(ScriptBinder* binder);

	/** Compile and execute the script located at fName.
	* \param fName The file name of the script to compile and run.
	* \remark By default, if the scirpt contains a main function that takes no arguments that function will be executed after compilation completes.
	*/
    void executeScript(std::string fName);
	/** Load a HGE resource script.
	* \param fName The file name of the resource script to load.
	*/
    void loadResourceScript(std::string fName);
	/** Get the ID of a function, necesary in order to call script functions with context.
	* \param moduleName The name of the module the function is in, in this case it will be the relative path of the file the script is located in.
	* \param funcName The name of the function to get the ID of, this only works if there is only one function named funcName in the module (or file in this case).
	* \return Greater than 0 if the operation succeeeds, less than 0 if no function was found or an error occured.
	*/
    int getFuncID(std::string moduleName, std::string funcName);

	///Singleton access method, returns a pointer to the ScriptManager.
    static ScriptManager* get();
};

extern void f();

#endif // SCRIPTMANAGER_H_INCLUDED
