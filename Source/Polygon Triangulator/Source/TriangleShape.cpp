/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#include <hgecolor.h>
#include <SceneManager.h>
#include <TriangleRenderable.h>
#include <Utils.h>
#include <SceneNode.h>
#include "TriangleShape.h"

using namespace std;

TriangleShape::TriangleShape(const string& name)
{
    triangle = static_cast<TriangleRenderable*>(SceneManager::get()->createComponent("TriangleRenderable", name));
    node = SceneManager::get()->getRootSceneNode()->createChildSceneNode(name);
    node->setPosition(hgeVector(0, 0));
    node->attachComponent(triangle);
}

TriangleShape::~TriangleShape()
{
    string name = node->getName();
    SceneManager::get()->destroySceneNode(node);
    SceneManager::get()->destroyComponent(name, true);
}

const string TriangleShape::getSummary()
{
    string summary = "Triangle vertices: ";

    vector<Triangle*> triangles = triangle->getTriangles();

    for (int i = 0; i < triangles.size(); ++i)
        summary += Utils::get()->formatString("%i=[%.1f %.1f] [%.1f %.1f] [%.1f %.1f] ", i, triangles[i]->vert1.x, triangles[i]->vert1.y,
                                                                                            triangles[i]->vert2.x, triangles[i]->vert2.y,
                                                                                            triangles[i]->vert3.x, triangles[i]->vert3.y);

    return summary;
}

void TriangleShape::addTriangle(const hgeVector& v1, const hgeVector& v2, const hgeVector& v3)
{
    Utils* utils = Utils::get();
    double rand = utils->getRandomDouble(0.5, .9);

    hgeColor color = hgeColor(utils->getRandomDouble(0.3, 1.0), utils->getRandomDouble(0.3, 1.0), utils->getRandomDouble(0.3, 1.0), rand);
    triangle->addTriangle(v1, v2, v3, hgeVector(0, 0), hgeVector(0, 0), hgeVector(0, 0), color, color, color);
}

void TriangleShape::hide()
{
    node->setVisible(false);
}

void TriangleShape::show()
{
    node->setVisible(true);
}

void TriangleShape::clearTriangles()
{
    triangle->clearTriangles();
}
