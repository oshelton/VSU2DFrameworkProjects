/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "renderTexture.h"
#include "GuiManager.h"
#include "Utils.h"
#include "RenderTextureManager.h"

using namespace std;

RenderTextureManager* RenderTextureManager::manager(NULL);

RenderTextureManager::RenderTextureManager()
{
}

RenderTextureManager::~RenderTextureManager()
{
	map<std::string, RenderTexture*>::const_iterator iter;
	for (iter = textures.begin(); iter != textures.end(); ++iter)
		delete iter->second;

    manager = NULL;

	textures.clear();
}

RenderTexture* RenderTextureManager::createRenderTexture(string name, int width, int height)
{
    if (textures.find(name) == textures.end())
        textures[name] = new RenderTexture(name, width, height);
    else
        Utils::get()->writeToLog("RenderTexture with name [" + name + "] already exists, returning previously existing RenderTexture.");
    return textures[name];
}

RenderTexture* RenderTextureManager::getRenderTexture(string name)
{
    if (textures.find(name) != textures.end())
        return textures[name];
    else
        return NULL;
}

void RenderTextureManager::destroyRenderTexture(string name)
{
    if (textures.find(name) != textures.end())
        destroyRenderTexture(textures[name]);
    else
        Utils::get()->writeToLog("RenderTexture with name [" + name + "] does not exists, ignoring.");
}

void RenderTextureManager::destroyRenderTexture(RenderTexture* tex)
{
    textures.erase(tex->getName());
    delete tex;
}

void RenderTextureManager::renderTextures()
{
    map<string, RenderTexture*>::const_iterator iter;
    for (iter = textures.begin(); iter != textures.end(); ++iter)
        iter->second->render();
}

RenderTextureManager* RenderTextureManager::get()
{
    if (manager == NULL)
        manager = new RenderTextureManager();

    return manager;
}
