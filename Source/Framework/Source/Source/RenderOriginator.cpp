/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "RenderableListener.h"
#include "RenderOriginator.h"

using namespace std;

void RenderOriginator::registerRenderableListener(RenderableListener* listener)
{
    list<RenderableListener*>::const_iterator iter;
    for (iter = renderListeners.begin(); iter != renderListeners.end(); ++iter)
    {
        if (*iter == listener)
            return;
    }

    listener->notifyAddedToOriginator(this);
    renderListeners.push_back(listener);
}

void RenderOriginator::removeRenderableListener(RenderableListener* listener)
{
    list<RenderableListener*>::const_iterator iter;
    for (iter = renderListeners.begin(); iter != renderListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            listener->notifyRemovedFromOriginator(this);
            renderListeners.remove(listener);
            break;
        }
    }
}
