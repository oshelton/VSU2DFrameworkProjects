/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <list>
#include "SceneManager.h"
#include "Camera.h"
#include "Utils.h"
#include "RenderTexture.h"
#include "SceneNode.h"
#include "Renderable.h"

using namespace std;

void Renderable::render()
{
    list<SceneNode*>::const_iterator iter;
    for (iter = users.begin(); iter != users.end(); ++iter)
    {
        SceneNode* parent = (*iter);
        if (parent->isVisible())
        {
            double radius = sqrt((getWidth() * getWidth()) + (getHeight() * getHeight()));
            if (Utils::get()->onScreen(parent->getWorldPosition(), parent->getWorldScale() * radius))
            {
                Camera* cam = SceneManager::get()->getCamera();
                hgeVector screenPosition = cam->convertToScreenSpace(parent->getWorldPosition());
                render(parent, screenPosition, cam);
            }
        }
    }
}

void Renderable::render(RenderTexture* const tex)
{
    list<SceneNode*>::const_iterator iter;
    for (iter = users.begin(); iter != users.end(); ++iter)
    {
        SceneNode* parent = (*iter);
        if (parent->isVisible())
        {
            double radius = sqrt((getWidth() * getWidth()) + (getHeight() * getHeight()));
            if (Utils::get()->onScreen(tex, parent->getWorldPosition(), parent->getWorldScale() * radius))
            {
                Camera* cam = tex->getCamera();
                hgeVector screenPosition = cam->convertToScreenSpace(parent->getWorldPosition());
                render(parent, screenPosition, cam);
            }
        }
    }
}
