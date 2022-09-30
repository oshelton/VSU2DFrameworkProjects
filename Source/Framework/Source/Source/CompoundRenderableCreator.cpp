/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <list>
#include "CompoundRenderable.h"
#include "CompoundRenderableCreator.h"

using namespace std;

Component* CompoundRenderableCreator::createComponent(const string& name)
{
    return new CompoundRenderable(name);
}

Component* CompoundRenderableCreator::copyComponent(const string& name, Component* com)
{
    CompoundRenderable* compound = static_cast<CompoundRenderable*>(com);

    CompoundRenderable* copy = new CompoundRenderable(name);

    const list<Renderable*> renderables = compound->getAttachedRenderables();
    list<Renderable*>::const_iterator iter;
    for (iter = renderables.begin(); iter != renderables.end(); ++iter)
        copy->addRenderable(*iter);
    return copy;
}
