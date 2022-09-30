/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <assert.h>
#include <angelscript.h>
#include <hge.h>
#include <hgeresource.h>
#include "Renderable.h"
#include "scriptstring.h"
#include "SceneManager.h"
#include "SimpleRenderable.h"
#include "SceneNode.h"
#include "Camera.h"
#include "GuiManager.h"
#include "InputManager.h"
#include "Utils.h"
#include "SystemManager.h"
#include "hgerect.h"
#include "ScriptBinder.h"
#include "ScriptManager.h"

using namespace std;

void MessageCallback(const asSMessageInfo *msg, void *param)
{
    const char *type = "ERR ";
    if ( msg->type == asMSGTYPE_WARNING )
        type = "WARN";
    else if ( msg->type == asMSGTYPE_INFORMATION )
        type = "INFO";

    char buff[512];

    sprintf(buff, "%s (%d, %d) : %s : %s", msg->section, msg->row, msg->col, type, msg->message);
    Utils::get()->writeToLog("Script Manager MSG " + ((string)buff));
}

void print(string s)
{
    GuiManager::get()->writeToConsole(s);
}

ScriptManager* ScriptManager::manager(NULL);

ScriptManager::ScriptManager()
{
    // Create the script engine
    engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    // The script compiler will write any compiler messages to the callback.
    engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

    context = engine->CreateContext();

    rManager = new hgeResourceManager(0);

    // Register the script string type
    RegisterScriptString(engine);
    RegisterScriptStringUtils(engine);

    int r = 0;
    r = engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL); assert (r >= 0);
}

ScriptManager::~ScriptManager()
{
    rManager->Purge();
    context->Release();
    engine->Release();
    manager = NULL;
}

asIScriptEngine* ScriptManager::getScriptEngine()
{
    return engine;
}

asIScriptContext* ScriptManager::getScriptContext()
{
    return context;
}

hgeResourceManager* ScriptManager::getResourceManager()
{
    return rManager;
}

void ScriptManager::addBindings(ScriptBinder* binder)
{
    binder->bind(engine);
    delete binder;
}

void ScriptManager::executeScript(string fName)
{
    int r;

    // We will load the script from a file on the disk.
    FILE *f = fopen(fName.c_str(), "rb");
    if ( f == 0 )
    {
        Utils::get()->writeToLog("Failed to open the script " + fName + ".");
        SystemManager::get()->quitNextUpdate();
    }

    // Determine the size of the file
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    fseek(f, 0, SEEK_SET);

    // On Win32 it is possible to do the following instead
    // int len = _filelength(_fileno(f));

    // Read the entire file
    string script;
    script.resize(len);
    int c =	fread(&script[0], len, 1, f);
    fclose(f);

    if ( c == 0 )
    {
        Utils::get()->writeToLog("Failed to load script file " + fName + ".");
        SystemManager::get()->quitNextUpdate();
    }
    asIScriptModule* mod = engine->GetModule(fName.c_str(), asGM_ALWAYS_CREATE);
    r = mod->AddScriptSection(fName.c_str(), &script[0], len);
    if ( r < 0 )
    {
        Utils::get()->writeToLog("AddScriptSection() failed");
        SystemManager::get()->quitNextUpdate();
    }
    r = mod->Build();
    if ( r < 0 )
    {
       Utils::get()->writeToLog("Build() of " + fName + " failed.");
        SystemManager::get()->quitNextUpdate();
    }
    mod->BindAllImportedFunctions();

    r = mod->GetFunctionIdByName("main");
    if (r >= 0)
    {
        context->Prepare(r);
        context->Execute();
    }
}

void ScriptManager::loadResourceScript(string fName)
{
    rManager->LoadScript(fName.c_str());
}

int ScriptManager::getFuncID(string moduleName, string funcName)
{
    return engine->GetModule(moduleName.c_str(), asGM_ONLY_IF_EXISTS)->GetFunctionIdByName(funcName.c_str());
}

ScriptManager* ScriptManager::get()
{
    if (manager == NULL)
        manager = new ScriptManager();

    return manager;
}
