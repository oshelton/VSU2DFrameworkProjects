/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#include <hgecolor.h>
#include <SceneManager.h>
#include <LineRenderable.h>
#include <TextRenderable.h>
#include <SceneNode.h>
#include <Utils.h>
#include "PointShape.h"

using namespace std;

PointShape::PointShape() : convertable(false)
{
    line = static_cast<LineRenderable*>(SceneManager::get()->createComponent("LineRenderable", "outline"));
    SceneNode* node = SceneManager::get()->getRootSceneNode()->createChildSceneNode("outline");
    node->setPosition(hgeVector(0, 0));
    node->attachComponent(line);
    node->setZ(0.3);
}

PointShape::~PointShape()
{
    SceneManager::get()->destroySceneNode("outline");
    SceneManager::get()->destroyComponent("outline", true);
}

const string PointShape::getSummary()
{
    string summary = "Line points: ";

    for (int i = 0; i < points.size(); ++i)
        summary += Utils::get()->formatString("%i=[%.1f %.1f] ", i, points[i].x, points[i].y);

    return summary;
}

void PointShape::addPoint(const hgeVector& point)
{
    points.push_back(point);

    if (points.size() > 1)
        line->addLine(points[points.size() - 2], points[points.size() - 1], hgeColor(1, 1, 1, 1));

    Utils* utils = Utils::get();
    SceneManager* scene = SceneManager::get();

    SceneNode* node = scene->getSceneNode("outline");

    SceneNode* caption = node->createChildSceneNode("caption " + utils->intToString(points.size()));
    caption->setPosition(hgeVector(point.x, point.y - 20));

    TextRenderable* text = static_cast<TextRenderable*>(scene->createComponent("TextRenderable", "caption " + utils->intToString(points.size())));
    text->setFont("mainFont");
    text->setAlignment(ALIGN_CENTER);
    text->setColor(hgeColor(1, 1, 0, 1));
    text->setText(utils->formatString("%i [%.1f %.1f]", points.size() - 1, point.x, point.y));

    caption->attachComponent(text);
}

void PointShape::clearPoints()
{
    Utils* utils = Utils::get();
    for (int i = 1; i <= points.size(); ++i)
    {
        SceneManager::get()->destroySceneNode("caption " + utils->intToString(i));
        SceneManager::get()->destroyComponent("caption " + utils->intToString(i), true);
    }

    points.clear();
    line->clearLines();
    convertable = false;
}

void PointShape::finalize()
{
    if (points.size() > 2)
    {
        line->addLine(points[points.size() - 1], points[0], hgeColor(1, 1, 1, 1));
        convertable = true;
    }
}
