/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef COMPONENTCREATOR_H_INCLUDED
#define COMPONENTCREATOR_H_INCLUDED

#include <string>
#include "dll.h"

class Component;

/**Special class for creating Components.
* This class provides an interface for creating different kinds of Components.
* Subclasses of this class can be added to the SceneManager using the registerComponentType method.
* Each Component class should have its own corresponding ComponentCreator subclass.
* \sa SceneManager::registerComponentType(std::string typeName, ComponentCreator* creator)
*/
class EXPORT_FRAME ComponentCreator
{
public:
    ///Required virtual deconstructor.
    virtual ~ComponentCreator(){}

    /**Create a new Component.
    * \param name Name of the created Component.
    * \return A new Component is returned, the exact type depends on the subclasses implementation.
    */
    virtual Component* createComponent(const std::string& name) = 0;
    /**Create a copy of a Component.
    * \param name Name of the newly created Component.
    * \param com The Component to be copied.
    */
    virtual Component* copyComponent(const std::string& name, Component* com) = 0;
};

#endif // COMPONENTCREATOR_H_INCLUDED
