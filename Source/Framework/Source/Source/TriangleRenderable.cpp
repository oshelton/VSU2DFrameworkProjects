/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgeresource.h>
#include <hge.h>
#include "SceneManager.h"
#include "SystemManager.h"
#include "Utils.h"
#include "SceneNode.h"
#include "ScriptManager.h"
#include "Camera.h"
#include "TriangleRenderable.h"

using namespace std;

TriangleRenderable::TriangleRenderable(const string& name)
{
    this->name = name;
}

TriangleRenderable::~TriangleRenderable()
{
    clearTriangles();

    removeAllUsers();
    removeFromRenderOriginators();
}

void TriangleRenderable::addTriangle(const hgeVector& vert1, const hgeVector& vert2, const hgeVector& vert3,
                     const hgeVector& uv1, const hgeVector& uv2, const hgeVector& uv3,
                     const hgeColor& color1, const hgeColor& color2, const hgeColor& color3,
                     const std::string& texture, const int& blendMode)
{
    if (ScriptManager::get()->getResourceManager()->GetTexture(texture.c_str()) == 0)
    {
        Utils::get()->writeToLog("Error, cannot load Texture [" + texture + "], aborting operation.");
        return;
    }
    else
    {
        addTriangle(vert1, vert2, vert3, uv1, uv2, uv3, color1, color2, color3,
                    ScriptManager::get()->getResourceManager()->GetTexture(texture.c_str()), blendMode);
    }
}

void TriangleRenderable::addTriangle(const hgeVector& vert1, const hgeVector& vert2, const hgeVector& vert3,
                     const hgeVector& uv1, const hgeVector& uv2, const hgeVector& uv3,
                     const hgeColor& color1, const hgeColor& color2, const hgeColor& color3,
                     const int& texture, const int& blendMode)
{
    Triangle* tri = new Triangle();

    tri->vert1 = vert1;
    tri->vert2 = vert2;
    tri->vert3 = vert3;

    tri->uv1 = uv1;
    tri->uv2 = uv2;
    tri->uv3 = uv3;

    tri->color1 = color1;
    tri->color2 = color2;
    tri->color3 = color3;

    tri->textureHandle = texture;
    tri->blendMode = blendMode;

    triangles.push_back(tri);
}

const vector<Triangle*>& TriangleRenderable::getTriangles()
{
    return triangles;
}

const int TriangleRenderable::getNumberOfTriangles()
{
    return triangles.size();
}

void TriangleRenderable::clearTriangles()
{
    for (unsigned int i = 0; i < triangles.size(); ++i)
        delete triangles[i];
    triangles.clear();
}

const double TriangleRenderable::getWidth()
{
    double min = 0;
    double max = 0;

    if (triangles.size() > 0)
    {
        min = triangles[0]->vert1.x;
        max = triangles[0]->vert1.x;

        if (triangles[0]->vert2.x > max)
            max = triangles[0]->vert2.x;
        if (triangles[0]->vert3.x > max)
            max = triangles[0]->vert3.x;

        if (triangles[0]->vert2.x < min)
            min = triangles[0]->vert2.x;
        if (triangles[0]->vert3.x < min)
            min = triangles[0]->vert3.x;

        for (unsigned int i = 1; i < triangles.size(); ++i)
        {
            if (triangles[i]->vert1.x > max)
                max = triangles[i]->vert1.x;
            if (triangles[i]->vert2.x > max)
                max = triangles[i]->vert2.x;
            if (triangles[i]->vert3.x > max)
                max = triangles[i]->vert3.x;

            if (triangles[i]->vert1.x < min)
                min = triangles[i]->vert1.x;
            if (triangles[i]->vert2.x < min)
                min = triangles[i]->vert2.x;
            if (triangles[i]->vert3.x < min)
                min = triangles[i]->vert3.x;
        }
        return max - min;
    }
    else
        return 0;
}

const double TriangleRenderable::getHeight()
{
    double min = 0;
    double max = 0;

    if (triangles.size() > 0)
    {
        min = triangles[0]->vert1.y;
        max = triangles[0]->vert1.y;

        if (triangles[0]->vert2.y > max)
            max = triangles[0]->vert2.y;
        if (triangles[0]->vert3.y > max)
            max = triangles[0]->vert3.y;

        if (triangles[0]->vert2.y < min)
            min = triangles[0]->vert2.y;
        if (triangles[0]->vert3.y < min)
            min = triangles[0]->vert3.y;

        for (unsigned int i = 1; i < triangles.size(); ++i)
        {
            if (triangles[i]->vert1.y > max)
                max = triangles[i]->vert1.y;
            if (triangles[i]->vert2.y > max)
                max = triangles[i]->vert2.y;
            if (triangles[i]->vert3.y > max)
                max = triangles[i]->vert3.y;

            if (triangles[i]->vert1.y < min)
                min = triangles[i]->vert1.y;
            if (triangles[i]->vert2.y < min)
                min = triangles[i]->vert2.y;
            if (triangles[i]->vert3.y < min)
                min = triangles[i]->vert3.y;
        }
        return max - min;
    }
    else
        return 0;
}

const hgeVector TriangleRenderable::transformPoint(hgeVector point, SceneNode* const user)
{
    hgeVector parentPosition = user->getWorldPosition();

    double angle = atan2(point.y, point.x);
    double radius = sqrt(point.x * point.x + point.y * point.y);

    double rotation = Utils::get()->angleRadians(user->getWorldRotation());

    hgeVector finalPosition((cos(angle + rotation) * radius + parentPosition.x) * user->getWorldScale(), (sin(angle + rotation) * radius + parentPosition.y) * user->getWorldScale());

    return finalPosition;
}

void TriangleRenderable::render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam)
{
    for (unsigned int i = 0; i < triangles.size(); ++i)
    {
        Triangle* tri = triangles[i];

        hgeVector vertex1 = transformPoint(tri->vert1, node);
        vertex1 = cam->convertToScreenSpace(vertex1);

        hgeVector vertex2 = transformPoint(tri->vert2, node);
        vertex2 = cam->convertToScreenSpace(vertex2);

        hgeVector vertex3 = transformPoint(tri->vert3, node);
        vertex3 = cam->convertToScreenSpace(vertex3);

        hgeVertex verts[3];
        verts[0].x = vertex1.x;
        verts[0].y = vertex1.y;
        verts[0].tx = tri->uv1.x;
        verts[0].ty = tri->uv1.y;
        verts[0].col = tri->color1.GetHWColor();
        verts[0].z = node->getZ();

        verts[1].x = vertex2.x;
        verts[1].y = vertex2.y;
        verts[1].tx = tri->uv2.x;
        verts[1].ty = tri->uv2.y;
        verts[1].col = tri->color2.GetHWColor();
        verts[1].z = node->getZ();

        verts[2].x = vertex3.x;
        verts[2].y = vertex3.y;
        verts[2].tx = tri->uv3.x;
        verts[2].ty = tri->uv3.y;
        verts[2].col = tri->color3.GetHWColor();
        verts[2].z = node->getZ();

        hgeTriple triple;
        triple.v[0] = verts[0];
        triple.v[1] = verts[1];
        triple.v[2] = verts[2];
        triple.tex = tri->textureHandle;
        triple.blend = tri->blendMode;

        SystemManager::get()->getHGEManager()->Gfx_RenderTriple(&triple);
    }
}
