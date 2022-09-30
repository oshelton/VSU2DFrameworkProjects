/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SCRIPTBINDER_H_INCLUDED
#define SCRIPTBINDER_H_INCLUDED

#include "dll.h"

class asIScriptEngine;

/** Special class used for generating bindings to AngelScript.
* This class can be subclassed and passed to theScriptManager with the ScriptManager::generateBindings method.
* \sa ScriptManager::generateBindings(ScriptBinder* binder)
*/
class EXPORT_FRAME ScriptBinder
{
public:
    ///Required virtual deconstructor.
    virtual ~ScriptBinder(){}

    /** Method that generates bindings.
    * \param engine The AngelScript script engine that the bindings are to begenerated for and with.
    */
    virtual void bind(asIScriptEngine* engine) = 0;
};

#endif // SCRIPTBINDER_H_INCLUDED
