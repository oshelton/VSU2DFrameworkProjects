/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef COMPOUNDRENDERABLECREATOR_H_INCLUDED
#define COMPOUNDRENDERABLECREATOR_H_INCLUDED

#include "ComponentCreator.h"

class EXPORT_FRAME CompoundRenderableCreator : public ComponentCreator
{
public:
    /**Create a new CompoundRenderable.
    * \param name Name of the created CompoundRenderable.
    * \return A new CompoundRenderable.
    */
    virtual Component* createComponent(const std::string& name);
    /**Create a copy of a CompoundRenderable.
    * \param name Name of the newly created CompoundRenderable.
    * \param com The CompoundRenderable to be copied.
    */
    virtual Component* copyComponent(const std::string& name, Component* com);
};

#endif // COMPOUNDRENDERABLECREATOR_H_INCLUDED
