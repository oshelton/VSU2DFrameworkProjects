/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgecolor.h>
#include "SceneManager.h"
#include "TextRenderable.h"
#include "TextRenderableCreator.h"

using namespace std;

Component* TextRenderableCreator::createComponent(const string& name)
{
    TextRenderable* ret = new TextRenderable(name);
    SceneManager::get()->registerRenderableListener(ret);
    return ret;
}

Component* TextRenderableCreator::copyComponent(const string& name, Component* com)
{
    TextRenderable* renderable = static_cast<TextRenderable*>(com);

    TextRenderable* copy = new TextRenderable(name);
    copy->setFont(renderable->getFont());
    copy->setColor(renderable->getColor());
    copy->setBlendMode(renderable->getBlendMode());
    copy->setProportion(renderable->getProportion());
    copy->setTracking(renderable->getTracking());
    copy->setSpacing(renderable->getSpacing());
    copy->setText(renderable->getText());
    copy->setAlignment(renderable->getTextAlignment());

    SceneManager::get()->registerRenderableListener(copy);

    return copy;
}
