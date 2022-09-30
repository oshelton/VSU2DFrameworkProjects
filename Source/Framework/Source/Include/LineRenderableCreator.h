/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef LINERENDERABLECREATOR_H_INCLUDED
#define LINERENDERABLECREATOR_H_INCLUDED

#include "ComponentCreator.h"

///Special class for creating LineRenderables.
class LineRenderableCreator : public ComponentCreator
{
public:
    /**Create a new LineRenderable.
    * \param name Name of the created Component.
    * \return A new Component is returned, the exact type depends
    */
    virtual Component* createComponent(const std::string& name);
    /**Create a copy of a LineRenderable.
    * \param name Name of the newly created Component.
    * \param com The Component to be copied.
    */
    virtual Component* copyComponent(const std::string& name, Component* com);
};

#endif // LINERENDERABLECREATOR_H_INCLUDED
