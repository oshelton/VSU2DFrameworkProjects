/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgevector.h>
#include <hgecolor.h>
#include <vector>
#include "SceneManager.h"
#include "TriangleRenderable.h"
#include "TriangleRenderableCreator.h"

using namespace std;

Component* TriangleRenderableCreator::createComponent(const string& name)
{
    TriangleRenderable* ret = new TriangleRenderable(name);
    SceneManager::get()->registerRenderableListener(ret);
    return ret;
}

Component* TriangleRenderableCreator::copyComponent(const string& name, Component* com)
{
    TriangleRenderable* original = static_cast<TriangleRenderable*>(com);

    TriangleRenderable* copy = new TriangleRenderable(name);

    vector<Triangle*> triangles = original->getTriangles();
    for (unsigned int i = 0; i < triangles.size(); ++i)
    {
        Triangle* tri = triangles[i];
        copy->addTriangle(tri->vert1, tri->vert2, tri->vert3, tri->uv1, tri->uv2, tri->uv3,
                          tri->color1, tri->color2, tri->color3, tri->textureHandle, tri->blendMode);
    }

    SceneManager::get()->registerRenderableListener(copy);

    return copy;
}
