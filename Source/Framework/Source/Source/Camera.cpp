#include <hge.h>
/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "SystemManager.h"
#include "Utils.h"
#include "SceneManager.h"
#include "SceneNode.h"
#include "RenderTexture.h"
#include "Camera.h"

using namespace std;

Camera::Camera(const string& name)
{
    this->name = name;
}

Camera::~Camera()
{
    removeAllUsers();
}

void Camera::setName(const string& name)
{
    SceneManager::get()->renameCamera(this->name, name);
}

SceneNode* Camera::getParent()
{
    if (users.size() > 0)
        return users.front();
    else
        return NULL;
}

void Camera::registerUser(SceneNode* node)
{
    if (users.size() > 0)
    {
        users.front()->removeComponent();
        users.clear();
    }
    users.push_back(node);
}

const double Camera::getLeft(RenderTexture* tex)
{
    if (tex != NULL)
    {
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.x - tex->getWidth() / 2;
        }
        else
            return - tex->getWidth() / 2;
    }
    else
    {
        double width = SystemManager::get()->getWindowWidth();
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.x - width / 2;
        }
        else
            return - width / 2;
    }
}

const double Camera::getBottom(RenderTexture* tex)
{
    if (tex != NULL)
    {
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.y - tex->getHeight() / 2;
        }
        else
            return -tex->getHeight() / 2;
    }
    else
    {
        double height = SystemManager::get()->getWindowHeight();
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.y - height / 2;
        }
        else
            return - height / 2;
    }
}

const double Camera::getRight(RenderTexture* tex)
{
    if (tex != NULL)
    {
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.x + tex->getWidth() / 2;
        }
        else
            return tex->getWidth() / 2;
    }
    else
    {
        double width = SystemManager::get()->getWindowWidth();
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.x + width / 2;
        }
        else
            return width / 2;
    }
}

const double Camera::getTop(RenderTexture* tex)
{
    if (tex != NULL)
    {
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.y + tex->getHeight() / 2;
        }
        else
            return tex->getHeight() / 2;
    }
    else
    {
        double height = SystemManager::get()->getWindowHeight();
        if (users.size() > 0)
        {
            hgeVector parentPos = users.front()->getWorldPosition();
            return parentPos.y + height / 2;
        }
        else
            return height / 2;
    }
}

const hgeVector Camera::getCenter()
{
    if (users.size() > 0)
        return users.front()->getWorldPosition();
    else
        return hgeVector(0, 0);
}

const hgeVector Camera::convertToScreenSpace(hgeVector point)
{
    return hgeVector(point.x - getLeft(), -point.y + getTop());
}
