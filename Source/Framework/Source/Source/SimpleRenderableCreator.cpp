/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgecolor.h>
#include "SceneManager.h"
#include "SimpleRenderable.h"
#include "SimpleRenderableCreator.h"

using namespace std;

Component* SimpleRenderableCreator::createComponent(const string& name)
{
    SimpleRenderable* ret = new SimpleRenderable(name);
    SceneManager::get()->registerRenderableListener(ret);
    return ret;
}

Component* SimpleRenderableCreator::copyComponent(const string& name, Component* com)
{
    SimpleRenderable* renderable = static_cast<SimpleRenderable*>(com);

    SimpleRenderable* copy = new SimpleRenderable(name);
    float u, v, width, height;
    u = v = width = height = 0;
    renderable->getTextureCoords(&u, &v, &width, &height);
    copy->setTexture(renderable->getTexture(), u, v, width, height);
    copy->setBlendMode(renderable->getBlendMode());
    copy->setColor(renderable->getColor());

    SceneManager::get()->registerRenderableListener(copy);

    return copy;
}
