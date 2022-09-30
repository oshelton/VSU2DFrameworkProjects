/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgeresource.h>
#include <angelscript.h>
#include "Camera.h"
#include "Camera.h"
#include "SimpleRenderable.h"
#include "SceneNode.h"
#include "ScriptManager.h"
#include "GuiManager.h"
#include "Utils.h"
#include "RenderableListener.h"
#include "UpdateListener.h"
#include "ComponentCreator.h"
#include "RenderTextureManager.h"
#include "SceneManager.h"

using namespace std;

SceneManager* SceneManager::scManager(NULL);

SceneManager::SceneManager()
{
    nullSceneNode = new SceneNode("nullSceneNode");
    rootSceneNode = new SceneNode("rootSceneNode");
    cameras["default"] = new Camera("default");
    cam = cameras["default"];
}

SceneManager::~SceneManager()
{
    delete nullSceneNode;
    delete rootSceneNode;

    while (components.begin() != components.end())
        destroyComponent(components.begin()->second, true);

    while (cameras.size() > 1)
        destroyCamera(cameras.begin()->second, true);

    cam->removeAllUsers();
    cameras.erase(cam->getName());
    delete cam;

    while (creators.begin() != creators.end())
    {
        ComponentCreator* com = creators.begin()->second;
        creators.erase(creators.begin()->first);
        delete com;
    }

    scManager = NULL;
}

SceneNode* SceneManager::getNullSceneNode()
{
    return nullSceneNode;
}

SceneNode* SceneManager::getRootSceneNode()
{
    return rootSceneNode;
}

SceneNode* SceneManager::createSceneNode(const string& name)
{
    if (sceneGraph.find(name) == sceneGraph.end())
    {
        sceneGraph[name] = new SceneNode(name);
        nullSceneNode->attachChildSceneNode(sceneGraph[name]);
    }
    else
        Utils::get()->writeToLog("SceneNode with name [" + name + "] already exists, returning previously existing SceneNode.");
    return sceneGraph[name];
}

SceneNode* SceneManager::createSceneNode(const string& name, hgeVector position, double z, double scale, double rotation)
{
    if (sceneGraph.find(name) == sceneGraph.end())
    {
        sceneGraph[name] = new SceneNode(name);
        sceneGraph[name]->setPosition(position);
        sceneGraph[name]->setZ(z);
        sceneGraph[name]->setScale(scale);
        sceneGraph[name]->setRotation(rotation);
        nullSceneNode->attachChildSceneNode(sceneGraph[name]);
    }
    else
        Utils::get()->writeToLog("SceneNode with name [" + name + "] already exists, returning previously existing SceneNode.");
    return sceneGraph[name];
}

void SceneManager::registerSceneNode(SceneNode* entity)
{
    if (sceneGraph.find(entity->getName()) == sceneGraph.end())
        sceneGraph[entity->getName()] = entity;
    else
        Utils::get()->writeToLog("SceneNode with name [" + entity->getName() + "] already exists, ignoring.");
}

void SceneManager::destroySceneNode(const string& name)
{
    if (sceneGraph.find(name) != sceneGraph.end())
        destroySceneNode(sceneGraph[name]);
    else
        Utils::get()->writeToLog("SceneNode with name [" + name + "] does not exists, ignoring.");
}

void SceneManager::destroySceneNode(SceneNode* entity)
{
    SceneNode* parent = entity->getParent();
    parent->removeChildSceneNodeFromMap(entity);
    sceneGraph.erase(entity->getName());
    entity->destroyAllChildren();
    delete entity;
}

const bool SceneManager::sceneNodeExists(const string& name)
{
    if (sceneGraph.find(name) != sceneGraph.end())
        return true;
    else
        return false;
}

SceneNode* SceneManager::getSceneNode(const string& name)
{
    if (sceneGraph.find(name) != sceneGraph.end())
        return sceneGraph[name];
    else
        Utils::get()->writeToLog("SceneNode with name [" + name + "] does not exists, returning nullSceneNode.");
    return NULL;
}

void SceneManager::renameSceneNode(const string& oldName, const string& newName)
{
    SceneNode* tmp = NULL;
    if (sceneGraph.find(oldName) != sceneGraph.end())
        tmp = sceneGraph[oldName];
    else
    {
        Utils::get()->writeToLog("SceneNode with name [" + oldName + "] does not exists, ignoring.");
        return;
    }

    if (sceneGraph.find(newName) != sceneGraph.end())
    {
        Utils::get()->writeToLog("SceneNode with name [" + newName + "] already exists, ignoring.");
        return;
    }

    SceneNode* tmpParent = tmp->getParent();
    tmpParent->removeChildSceneNode(tmp);
    sceneGraph.erase(oldName);

    sceneGraph[newName] = tmp;
    sceneGraph[newName]->setNameNoRemap(newName);
    tmpParent->attachChildSceneNode(tmp);
}

Camera* SceneManager::createCamera(const string& name)
{
    if (cameras.find(name) == cameras.end())
        cameras[name] = new Camera(name);
    else
        Utils::get()->writeToLog("Camera with name [" + name + "] already exists, returning previously existing Camera.");
    return cameras[name];
}

const bool SceneManager::cameraExists(const string& name)
{
    if (cameras.find(name) != cameras.end())
        return true;
    else
        return false;
}

Camera* SceneManager::getCamera(const string& name)
{
    if (cameras.find(name) != cameras.end())
        return cameras[name];
    else
        Utils::get()->writeToLog("Camera with name [" + name + "] does not exists, returning NULL.");
    return NULL;
}

void SceneManager::destroyCamera(const string& name, const bool& deleteIfInUse)
{
    if (cameras.find(name) != cameras.end())
        destroyCamera(cameras[name], deleteIfInUse);
    else
        Utils::get()->writeToLog("Camera with name [" + name + "] does not exists, ignoring.");
}

void SceneManager::destroyCamera(Camera* cam, const bool& deleteIfInUse)
{
    if (cam != cameras["default"])
    {
        if (!deleteIfInUse)
        {
            if (cam->getNumberOfUsers() > 0)
                return;
        }

        cam->removeAllUsers();
        cameras.erase(cam->getName());
        delete cam;
    }
}

void SceneManager::renameCamera(const string& oldName, const string& newName)
{
    Camera* cam = NULL;
    if (cameras.find(oldName) != cameras.end())
        cam = cameras[oldName];
    else
    {
        Utils::get()->writeToLog("Camera with name [" + oldName + "] does not exists, ignoring.");
        return;
    }

    if (cameras.find(newName) != cameras.end())
    {
        Utils::get()->writeToLog("Camera with name [" + newName + "] already exists, ignoring.");
        return;
    }

    cam->setNameNoRemap(newName);
    cameras.erase(oldName);
    cameras[newName] = cam;
}

void SceneManager::registerComponentType(const string& type, ComponentCreator* creator)
{
    if (creators.find(type) != creators.end())
        Utils::get()->writeToLog("ComponentCreator with type name [" + type + "] already exists, ignoring.");
    else
        creators[type] = creator;
}

Component* SceneManager::createComponent(const string& type, const string& name)
{
    if (creators.find(type) == creators.end())
    {
        Utils::get()->writeToLog("ComponentCreator with type name [" + name + "] does not exist, returning NULL.");
        return NULL;
    }

    if (components.find(name) != components.end())
    {
        Utils::get()->writeToLog("Component with name [" + name + "] already exists, returning previously existing component.");
        return  components[name];
    }
    else
    {
        components[name] = creators[type]->createComponent(name);
        return components[name];
    }
}

const bool SceneManager::componentExists(const string& name)
{
    if (components.find(name) != components.end())
        return true;
    else
        return false;
}

Component* SceneManager::getComponent(const string& name)
{
    if (components.find(name) == components.end())
    {
        Utils::get()->writeToLog("Component with name [" + name + "] does not exist, returning NULL.");
        return NULL;
    }
    else
        return components[name];
}

Component* SceneManager::copyComponent(const string& newName, Component* const com)
{
    if (components.find(newName) != components.end())
    {
        Utils::get()->writeToLog("Component with name [" + newName + "] already exists, returning previously existing component.");
        return components[newName];
    }
    else
    {
        components[newName] = creators[com->getType()]->copyComponent(newName, com);
        return components[newName];
    }
}

void SceneManager::destroyComponent(const string& name, const bool& deleteIfInUse)
{
    if (components.find(name) != components.end())
        destroyComponent(components[name], deleteIfInUse);
    else
        Utils::get()->writeToLog("Component with name [" + name + "] does not exists, ignoring.");
}

void SceneManager::destroyComponent(Component* com, const bool& deleteIfInUse)
{
    if (com != NULL)
    {
        if (!deleteIfInUse)
        {
            if (com->getNumberOfUsers() > 0)
                return;
        }

        components.erase(com->getName());
        delete com;
    }
}

void SceneManager::renameComponent(const string& oldName, const string& newName)
{
    Component* com = NULL;
    if (components.find(oldName) != components.end())
        com = components[oldName];
    else
    {
        Utils::get()->writeToLog("Component with name [" + oldName + "] does not exists, ignoring.");
        return;
    }

    if (components.find(newName) != components.end())
    {
        Utils::get()->writeToLog("Components with name [" + newName + "] already exists, ignoring.");
        return;
    }

    com->setNameNoRemap(newName);
    components.erase(oldName);
    components[newName] = com;
}

void SceneManager::clearScene()
{
    nullSceneNode->destroyAllChildren();
    rootSceneNode->destroyAllChildren();

    while (components.begin() != components.end())
        destroyComponent(components.begin()->second, true);
    components.clear();

    Camera* defCam = cameras["default"];

    while (cameras.size() > 1)
    {
        if (cameras.begin()->first != "default")
            destroyCamera(cameras.begin()->second, true);
    }

    cameras.clear();
    cameras["default"] = defCam;
}

void SceneManager::update()
{
    list<UpdateListener*>::const_iterator iter;
    for (iter = updateListeners.begin(); iter != updateListeners.end(); ++iter)
        (*iter)->update();
}

void SceneManager::render()
{
    RenderTextureManager::get()->renderTextures();

    list<RenderableListener*>::const_iterator iter;
    for (iter = renderListeners.begin(); iter != renderListeners.end(); ++iter)
        (*iter)->render();
}

SceneManager* SceneManager::get()
{
    if (scManager == NULL)
        scManager = new SceneManager();

    return scManager;
}
