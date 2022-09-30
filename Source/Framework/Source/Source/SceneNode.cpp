/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <math.h>
#include <angelscript.h>
#include <hgerect.h>
#include "Camera.h"
#include "SimpleRenderable.h"
#include "ScriptManager.h"
#include "SceneManager.h"
#include "Renderable.h"
#include "Utils.h"
#include "GuiManager.h"
#include "SceneNode.h"

using namespace std;

SceneNodeIterator::SceneNodeIterator(SceneNode* parent, std::map<std::string, SceneNode*>* childNodes)
{
    this->parent = parent;
    children = childNodes;
    iter = children->begin();
}

const bool SceneNodeIterator::hasNext()
{

    if (iter == children->end() || ++iter == children->end())
    {
        --iter;
        return false;
    }
    else
        return true;
}

SceneNode* SceneNodeIterator::next()
{
    if (++iter == children->end())
    {
        --iter;
        return NULL;
    }
    else
    {
        ++iter;
        return iter->second;
    }
}

SceneNode* SceneNodeIterator::previous()
{
    if (iter == children->begin())
        return children->begin()->second;
    else
    {
        --iter;
        return iter->second;
    }
}

SceneNode* SceneNodeIterator::current()
{
    if (iter == children->end())
        return NULL;
    else
        return iter->second;
}

void SceneNodeIterator::remove()
{
    if (iter == children->begin())
    {
        parent->removeChildSceneNode(iter->second);
        iter = children->begin();
    }
    else
    {
        std::map<std::string, SceneNode*>::iterator iter2 = ++iter;
        --iter;

        parent->removeChildSceneNode(iter->second);
        iter = iter2;
    }
}

void SceneNodeIterator::destroy()
{
    if (iter == children->begin())
    {
        parent->destroyChildSceneNode(iter->second);
        iter = children->begin();
    }
    else
    {
        std::map<std::string, SceneNode*>::iterator iter2 = ++iter;
        --iter;

        parent->destroyChildSceneNode(iter->second);
        iter = iter2;
    }
}

SceneNode::SceneNode(const string& name) :
        parent(NULL), inheritScale(true), InheritRotation(true), visible(true),  position(0, 0), z(0.5), scale(1), rotation(0), component(NULL)
{
    this->name = name;
}

SceneNode::~SceneNode()
{
    removeComponent();
    destroyAllChildren();
}

void SceneNode::setParent(SceneNode* parent)
{
    if (this->parent != NULL)
        this->parent->removeChildSceneNodeFromMap(this);
    this->parent = parent;
}

SceneNode* SceneNode::getParent()
{
    return parent;
}

SceneNode* SceneNode::createChildSceneNode(const string& name)
{
    if (children.find(name) != children.end())
    {
        Utils::get()->writeToLog("Replacing child entity [" + name + "] of entity [" + this->name + "]. createChildSceneNode(string name)");
        SceneManager::get()->destroySceneNode(name);
    }

    children[name] = SceneManager::get()->createSceneNode(name);
    children[name]->setParent(this);
    return children[name];
}

SceneNode* SceneNode::attachChildSceneNode(const string& name)
{
    SceneNode* toAdd = SceneManager::get()->getSceneNode(name);
    attachChildSceneNode(toAdd);
    return children[name];
}

void SceneNode::attachChildSceneNode(SceneNode* entity)
{
    if (entity->getParent() != this)
    {
        if (entity->getParent() != NULL)
            entity->getParent()->removeChildSceneNodeFromMap(entity);
        entity->setParent(this);
        children[entity->getName()] = entity;
    }
}

SceneNode* SceneNode::removeChildSceneNode(const string& name)
{
    if (children.find(name) == children.end())
    {
        Utils::get()->writeToLog("SceneNode with name [" + name + "] is not a child of [" + this->name + "].  removeChildSceneNode(string name)");
        return NULL;
    }
    else
    {

        SceneNode* ret = children[name];
        if (parent != SceneManager::get()->getNullSceneNode())
        {
            SceneManager::get()->getNullSceneNode()->attachChildSceneNode(ret);
            children.erase(name);
        }

        return ret;
    }
}

void SceneNode::removeChildSceneNode(SceneNode* entity)
{
    if (children.find(entity->getName()) == children.end())
        Utils::get()->writeToLog("SceneNode with name [" + entity->getName() + "] is not a child of [" + name + "].  removeChildSceneNode(SceneNode@ ent)");
    else
    {
        if (parent != SceneManager::get()->getNullSceneNode())
        {
            SceneManager::get()->getNullSceneNode()->attachChildSceneNode(entity);
            children.erase(entity->getName());
        }
    }
}

void SceneNode::removeChildSceneNodeFromMap(SceneNode* entity)
{
    children.erase(entity->getName());
}

void SceneNode::destroy()
{
    SceneManager::get()->destroySceneNode(this);
}

void SceneNode::destroyChildSceneNode(const string& name)
{
    if (children.find(name) == children.end())
        Utils::get()->writeToLog("SceneNode with name [" + name + "] is not a child of [" + this->name + "]. destroyChildSceneNode(string name)");
    else
        SceneManager::get()->destroySceneNode(children[name]);
}

void SceneNode::destroyChildSceneNode(SceneNode* entity)
{
    if (children.find(entity->getName()) == children.end())
        Utils::get()->writeToLog("SceneNode with name [" + entity->getName() + "] is not a child of [" + name + "]. destroyChildSceneNode(SceneNode@ ent)");
    else
        SceneManager::get()->destroySceneNode(entity);
}

void SceneNode::destroyAllChildren()
{
    while (children.begin() != children.end())
        destroyChildSceneNode(children.begin()->second);
}

SceneNodeIterator SceneNode::getChildNodeIterator()
{
    return SceneNodeIterator(this, &children);
}

void SceneNode::attachComponent(const string& name)
{
    if (component != NULL)
        component->notifyRemoved(this);

    component = SceneManager::get()->getComponent(name);
    component->registerUser(this);
}

void SceneNode::attachComponent(Component* com)
{
    if (component != NULL)
        component->notifyRemoved(this);

    component = com;
    component->registerUser(this);
}

Component* SceneNode::getComponent()
{
    return component;
}

Component* SceneNode::removeComponent()
{
    if (component != NULL)
    {
        component->notifyRemoved(this);
        component = NULL;
        return component;
    }
    return NULL;
}

void SceneNode::setPosition(const hgeVector& position)
{
    this->position.x = position.x;
    this->position.y = position.y;
}

const hgeVector SceneNode::getPosition()
{
    return hgeVector(position.x, position.y);
}

const hgeVector SceneNode::getWorldPosition()
{
    if (parent == NULL || parent == SceneManager::get()->getNullSceneNode() || parent == SceneManager::get()->getRootSceneNode())
        return position;
    else
    {
        Utils* utils = Utils::get();

        hgeVector parentPosition = parent->getWorldPosition();

        double radius = sqrt(position.x * position.x + position.y * position.y);
        double angle = atan2(position.y, position.x);
        hgeVector returnVector(cos((angle + utils->angleRadians(parent->getWorldRotation()))) * radius, sin((angle + utils->angleRadians(parent->getWorldRotation()))) * radius);

        returnVector.x *=  (parent->getWorldScale());
        returnVector.y *=  (parent->getWorldScale());

        returnVector.x += parentPosition.x;
        returnVector.y += parentPosition.y;
        return returnVector;
    }
}

void SceneNode::translate(const hgeVector translateVec, const TransformSpace& tSpace)
{
    Utils* utils = Utils::get();
    switch (tSpace)
    {
    case TS_LOCAL:
        position.x += (-sin(utils->angleRadians(rotation)) * -translateVec.x + cos(utils->angleRadians(rotation)) * translateVec.y);
        position.y += (sin(utils->angleRadians(rotation)) * translateVec.y + cos(utils->angleRadians(rotation)) * -translateVec.x);
        break;
    case TS_PARENT:
        position.x += translateVec.x;
        position.y += -translateVec.y;
        break;
    case TS_GLOBAL:
        double globalRotation = utils->angleRadians(parent->getWorldRotation());
        position.x += (-sin(utils->angleRadians(rotation) + globalRotation) * translateVec.x + cos(utils->angleRadians(rotation) + globalRotation) * translateVec.y);
        position.y += (sin(utils->angleRadians(rotation) + globalRotation) * translateVec.y + cos(utils->angleRadians(rotation) + globalRotation) * translateVec.x);
        break;
    }
}

void SceneNode::setScale(const double& scale)
{
    this->scale = scale;
}

double SceneNode::getScale()
{
    return scale;
}

double SceneNode::getWorldScale()
{
    if (inheritScale && parent != NULL)
        return scale * parent->getWorldScale();
    else
        return scale;
}

void SceneNode::rotate(const double& angle)
{
    rotation += angle;
    if (rotation >= 360)
        rotation -= 360;
    else if (rotation <= -360)
        rotation += 360;
}

void SceneNode::setRotation(const double heading)
{
    rotation =  heading;
}

double SceneNode::getRotation()
{
    return rotation;
}

double SceneNode::getWorldRotation()
{
    if (InheritRotation && parent != NULL && parent != SceneManager::get()->getRootSceneNode())
        return getRotation() + parent->getWorldRotation();
    else
        return getRotation();
}

void SceneNode::setZ(const double& z)
{
    this->z = z;
}

double SceneNode::getZ()
{
    return z;
}

void SceneNode::setInheritScale(const bool& inherit)
{
    inheritScale = inherit;
}

bool SceneNode::doesInheritScale()
{
    return inheritScale;
}

void SceneNode::setInheritRotation(const bool& inherit)
{
    InheritRotation = inherit;
}

bool SceneNode::doesInheritRotation()
{
    return InheritRotation;
}

void SceneNode::setVisible(const bool& visible)
{
    this->visible = visible;
}

bool SceneNode::isVisible()
{
    return visible;
}

void SceneNode::setName(const string& name)
{
    SceneManager::get()->renameSceneNode(this->name, name);
}

void SceneNode::setNameNoRemap(const string& name)
{
    this->name = name;
}

const string& SceneNode::getName()
{
    return name;
}
