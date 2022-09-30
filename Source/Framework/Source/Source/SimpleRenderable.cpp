/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgesprite.h>
#include <math.h>
#include <hge.h>
#include <hgeresource.h>
#include "SceneManager.h"
#include "Utils.h"
#include "SceneNode.h"
#include "ScriptManager.h"
#include "SimpleRenderable.h"

using namespace std;

SimpleRenderable::SimpleRenderable(const string& name)
{
    this->name = name;
    sprite = NULL;
}

SimpleRenderable::~SimpleRenderable()
{
    if (sprite != NULL)
        delete sprite;
    removeAllUsers();
    removeFromRenderOriginators();
}

void SimpleRenderable::setSprite(const string& spriteName)
{
    if (ScriptManager::get()->getResourceManager()->GetSprite(spriteName.c_str()) == 0)
            Utils::get()->writeToLog("Error, cannot load Sprite [" + spriteName + "]");
    else
    {
        if (sprite != NULL)
            delete sprite;
        sprite = new hgeSprite(*ScriptManager::get()->getResourceManager()->GetSprite(spriteName.c_str()));
        sprite->SetHotSpot(getWidth() / 2, getHeight() / 2);
    }
}

void SimpleRenderable::setTexture(const string& name)
{
    if (ScriptManager::get()->getResourceManager()->GetTexture(name.c_str()) == 0)
        Utils::get()->writeToLog("Error, cannot load Texture [" + name + "]");
    else
	{
		if (sprite != NULL)
		{
			sprite->SetTexture(ScriptManager::get()->getResourceManager()->GetTexture(name.c_str()));
			sprite->SetHotSpot(getWidth() / 2, getHeight() / 2);
		}
		else
		{
			sprite = new hgeSprite(ScriptManager::get()->getResourceManager()->GetTexture(name.c_str()), 0, 0, 128, 128);
			sprite->SetHotSpot(getWidth() / 2, getHeight() / 2);
		}
	}
}

void SimpleRenderable::setTexture(const int& handle, const float& x, const float& y, const float& width, const float& height)
{
    if (sprite != NULL)
    {
        sprite->SetTexture(handle);
        sprite->SetTextureRect(x, y, width, height);
    }
    else
        sprite = new hgeSprite(ScriptManager::get()->getResourceManager()->GetTexture(name.c_str()), x, y, width, height);
    sprite->SetHotSpot(getWidth() / 2, getHeight() / 2);
}

int SimpleRenderable::getTexture()
{
    if (sprite != NULL)
        return sprite->GetTexture();
    else
        return 0;
}

void SimpleRenderable::getTextureCoords(float* u, float* v, float* width, float* height)
{
    if (sprite != NULL)
        sprite->GetTextureRect(u, v, width, height);
}

void SimpleRenderable::setTextureCoords(const float& u, const float& v, const float& width, const float& height, const bool& adjustSize)
{
    if (sprite != NULL)
        sprite->SetTextureRect(u, v, width, height, adjustSize);
}

void SimpleRenderable::setBlendMode(const int& blendMode)
{
    if (sprite != NULL)
        sprite->SetBlendMode(blendMode);
}

int SimpleRenderable::getBlendMode()
{
    if (sprite != NULL)
        return sprite->GetBlendMode();
    return 0;
}

void SimpleRenderable::setColor(const hgeColor& color)
{
    if (sprite != NULL)
        sprite->SetColor(color.GetHWColor());
}

hgeColor SimpleRenderable::getColor()
{
    if (sprite != NULL)
        return hgeColor(sprite->GetColor());
    return hgeColor(0, 0, 0, 0);
}

const double SimpleRenderable::getWidth()
{
    if (sprite != NULL)
        return sprite->GetWidth();
    return 0;
}

const double SimpleRenderable::getHeight()
{
    if (sprite != NULL)
        return sprite->GetHeight();
    return 0;
}

void SimpleRenderable::render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam)
{
    if (sprite != NULL)
    {
        sprite->SetZ(node->getZ());
        sprite->RenderEx(screenPosition.x, screenPosition.y, -Utils::get()->angleRadians(node->getWorldRotation()), node->getWorldScale(), node->getWorldScale());
    }
}
