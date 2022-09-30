/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SIMPLERENDERABLECREATOR_H_INCLUDED
#define SIMPLERENDERABLECREATOR_H_INCLUDED

#include "ComponentCreator.h"

class Component;

class SimpleRenderableCreator : public ComponentCreator
{
public:
    /**Create a new SimpleRenderable.
    * \param name Name of the created Component.
    * \return A new Component is returned, the exact type depends
    */
    virtual Component* createComponent(const std::string& name);
    /**Create a copy of a SimpleRenderable.
    * \param name Name of the newly created Component.
    * \param com The Component to be copied.
    */
    virtual Component* copyComponent(const std::string& name, Component* com);
};

#endif // SIMPLERENDERABLECREATOR_H_INCLUDED
