/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgevector.h>
#include <hgecolor.h>
#include <vector>
#include "SceneManager.h"
#include "LineRenderable.h"
#include "LineRenderableCreator.h"

using namespace std;

Component* LineRenderableCreator::createComponent(const string& name)
{
    LineRenderable* ret = new LineRenderable(name);
    SceneManager::get()->registerRenderableListener(ret);
    return ret;
}

Component* LineRenderableCreator::copyComponent(const string& name, Component* com)
{
    LineRenderable* line = static_cast<LineRenderable*>(com);

    LineRenderable* copy = new LineRenderable(name);

    vector<Line> lines = line->getLines();
    for (int i = 0; i < lines.size(); ++i)
        copy->addLine(lines[i].point1, lines[i].point2, lines[i].color);
    SceneManager::get()->registerRenderableListener(copy);

    return copy;
}
