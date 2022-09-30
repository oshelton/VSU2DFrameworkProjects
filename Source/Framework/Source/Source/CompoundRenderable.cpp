/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "SceneNode.h"
#include "Utils.h"
#include "CompoundRenderable.h"

using namespace std;

CompoundRenderable::CompoundRenderable(const string& name)
{
    this->name = name;
}

CompoundRenderable::~CompoundRenderable()
{
    removeAllUsers();
    removeFromRenderOriginators();
}

void CompoundRenderable::registerUser(SceneNode* node)
{
    if (!isUser(node))
        users.push_back(node);

    list<Renderable*>::iterator iter;
    if (renderables.size() > 0)
    {
        for (iter = renderables.begin(); iter != renderables.end(); ++iter)
            (*iter)->registerUser(node);
    }
}

void CompoundRenderable::removeAllUsers()
{
    std::list<SceneNode*>::const_iterator iter;
    for (iter = users.begin(); iter != users.end(); ++iter)
    {
        (*iter)->removeComponent();
        list<Renderable*>::const_iterator iter2;
        for (iter2 = renderables.begin(); iter2 != renderables.end(); ++iter2)
            (*iter2)->notifyRemoved((*iter));
    }

    users.clear();
}

void CompoundRenderable::notifyRemoved(SceneNode* node)
{
    users.remove(node);

    list<Renderable*>::const_iterator iter;
    for (iter = renderables.begin(); iter != renderables.end(); ++iter)
        (*iter)->notifyRemoved(node);
}

void CompoundRenderable::addRenderable(Renderable* render)
{
    list<Renderable*>::const_iterator iter;
    for (iter = renderables.begin(); iter != renderables.end(); ++iter)
    {
        if ((*iter) == render)
            return;
    }
    renderables.push_back(render);

    list<SceneNode*>::const_iterator iter2;
    for (iter2 = users.begin(); iter2 != users.end(); ++iter2)
        render->registerUser((*iter2));
}

Renderable* CompoundRenderable::removeRenderable(const string& name)
{
    list<Renderable*>::const_iterator iter;
    for (iter = renderables.begin(); iter != renderables.end(); ++iter)
    {
        if ((*iter)->getName() == name)
        {
            list<SceneNode*>::const_iterator iter2;
            for (iter2 = users.begin(); iter2 != users.end(); ++iter2)
                (*iter)->notifyRemoved((*iter2));
            Renderable* toReturn = (*iter);
            renderables.remove((*iter));
            return toReturn;
        }
    }
    Utils::get()->writeToLog("Renderable named: " + name + " does not exist in the CompoundRenderable " + this->name);
    return NULL;
}

const list<Renderable*>& CompoundRenderable::getAttachedRenderables()
{
    return renderables;
}
