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
#include "SystemManager.h"
#include "GuiManager.h"
#include "Utils.h"
#include "Camera.h"
#include "SceneNode.h"
#include "RenderTexture.h"
#include "LineRenderable.h"

using namespace std;

LineRenderable::LineRenderable(const string& name)
{
    this->name = name;
}

LineRenderable::~LineRenderable()
{
    removeAllUsers();
    removeFromRenderOriginators();
}

void LineRenderable::addLine(const hgeVector& point1, const hgeVector& point2, const hgeColor& color)
{
    lines.push_back(Line(point1, point2, color));
}

const vector<Line>& LineRenderable::getLines()
{
    return lines;
}

void LineRenderable::clearLines()
{
    lines.clear();
}

const double LineRenderable::getWidth()
{
    if (lines.size() > 0)
    {
        double max = 0;
        double min = 0;
        if (lines[0].point1.x >= lines[0].point2.x)
        {
            max = lines[0].point1.x;
            min = lines[0].point2.x;
        }
        else
        {
            min = lines[0].point1.x;
            max = lines[0].point2.x;
        }

        for (unsigned int i = 1; i < lines.size(); ++i)
        {
            if (lines[i].point1.x >= lines[i].point2.x)
            {
                max = lines[i].point1.x;
                min = lines[i].point2.x;
            }
            else
            {
                min = lines[i].point1.x;
                max = lines[i].point2.x;
            }
        }
        return max - min;
    }
    else
        return 0;
}

const double LineRenderable::getHeight()
{
    if (lines.size() > 0)
    {
        double max = 0;
        double min = 0;
        if (lines[0].point1.y >= lines[0].point2.y)
        {
            max = lines[0].point1.y;
            min = lines[0].point2.y;
        }
        else
        {
            min = lines[0].point1.y;
            max = lines[0].point2.y;
        }

        for (unsigned int i = 1; i < lines.size(); ++i)
        {
            if (lines[i].point1.y >= lines[i].point2.y)
            {
                max = lines[i].point1.y;
                min = lines[i].point2.y;
            }
            else
            {
                min = lines[i].point1.y;
                max = lines[i].point2.y;
            }
        }
        return max - min;
    }
    else
        return 0;
}

const hgeVector LineRenderable::transformPoint(hgeVector point, SceneNode* const user)
{
    hgeVector parentPosition = user->getWorldPosition();

    double angle = atan2(point.y, point.x);
    double radius = sqrt(point.x * point.x + point.y * point.y);

    double rotation = Utils::get()->angleRadians(user->getWorldRotation());

    hgeVector finalPosition((cos(angle + rotation) * radius + parentPosition.x) * user->getWorldScale(), (sin(angle + rotation) * radius + parentPosition.y) * user->getWorldScale());

    return finalPosition;
}

void LineRenderable::render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam)
{
    for (int i = 0; i < lines.size(); ++i)
    {
        hgeVector finalPosition1 = cam->convertToScreenSpace(transformPoint(lines[i].point1, node));
        hgeVector finalPosition2 = cam->convertToScreenSpace(transformPoint(lines[i].point2, node));

        SystemManager::get()->getHGEManager()->Gfx_RenderLine(finalPosition1.x, finalPosition1.y, finalPosition2.x, finalPosition2.y, lines[i].color.GetHWColor(), node->getZ());
    }
}
