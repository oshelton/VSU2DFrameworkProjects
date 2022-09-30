/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hge.h>
#include "RenderableListener.h"
#include "SystemManager.h"
#include "UpdateListener.h"
#include "Camera.h"
#include "Utils.h"
#include "RenderTexture.h"

using namespace std;

RenderTexture::RenderTexture(string name, int width, int height)
{
    this->name = name;
	this->width = width;
	this->height = height;
	handle = SystemManager::get()->getHGEManager()->Target_Create(width, height, true);

	cam = NULL;
}

RenderTexture::~RenderTexture()
{
	removeAllUpdateListeners();
	removeAllRenderListeners();
	SystemManager::get()->getHGEManager()->Target_Free(handle);
}

int RenderTexture::getTexture()
{
	return SystemManager::get()->getHGEManager()->Target_GetTexture(handle);
}

void RenderTexture::update()
{
    list<UpdateListener*>::const_iterator iter;
    for (iter = updateListeners.begin(); iter != updateListeners.end(); ++iter)
        (*iter)->update(this);
}

//!automatically clears buffer.
void RenderTexture::render()
{
    if (cam != NULL)
    {
        HGE* hge = SystemManager::get()->getHGEManager();
        hge->Gfx_BeginScene(handle);
        hge->Gfx_Clear(0);

        list<RenderableListener*>::const_iterator iter;
        for (iter = renderListeners.begin(); iter != renderListeners.end(); ++iter)
            (*iter)->render(this);

        hge->Gfx_EndScene();
    }
}
