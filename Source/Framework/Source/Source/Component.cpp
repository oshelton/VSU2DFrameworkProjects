/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "SceneNode.h"
#include "GuiManager.h"
#include "SceneManager.h"
#include "Component.h"

using namespace std;

void Component::setName(const string& newName)
{
    SceneManager::get()->renameComponent(name, newName);
}

Component* Component::copy(const std::string& name)
{
    return SceneManager::get()->copyComponent(name, this);
}

void Component::destroy(bool deleteIfInUse)
{
    SceneManager::get()->destroyComponent(this, deleteIfInUse);
}

void Component::removeUser(SceneNode* node)
{
    list<SceneNode*>::const_iterator iter;
    for (iter = users.begin(); iter != users.end(); ++iter)
    {
        if (*iter == node)
        {
            users.remove(node);
            node->removeComponent();
            return;
        }
    }
}

void Component::removeAllUsers()
{
    if (users.size() > 0)
    {
        std::list<SceneNode*>::iterator iter;
        for (iter = users.begin(); iter != users.end(); ++iter)
            (*iter)->removeComponent();
        users.clear();
    }
}
