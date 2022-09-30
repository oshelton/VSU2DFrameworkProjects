/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef UTILBINDER_H_INCLUDED
#define UTILBINDER_H_INCLUDED

#include "dll.h"
#include "ScriptBinder.h"

class asIScriptEngine;

/** Special class used for generating AngelScript bindings for the Utility class and some other core types.
* This class provides AngelScript bindings for the hgeColor, hgeRect, hgeVector, and Utils classes.  hge has been removed from the front of the registered HGE classes and hgeVector has been renamed to Vector2.
* \sa ScriptBinder
*/
class UtilBinder : public ScriptBinder
{
public:
    /** Method that generates bindings.
    * \param engine The AngelScript script engine that the bindings are to begenerated for and with.
    */
    void bind(asIScriptEngine* engine);
};


#endif // UTILBINDER_H_INCLUDED
