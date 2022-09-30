/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "UpdateListener.h"
#include "UpdateOriginator.h"

using namespace std;

void UpdateOriginator::registerUpdateListener(UpdateListener* listener)
{
    list<UpdateListener*>::const_iterator iter;
    for (iter = updateListeners.begin(); iter != updateListeners.end(); ++iter)
    {
        if (*iter == listener)
            return;
    }

    listener->notifyAddedToOriginator(this);
    updateListeners.push_back(listener);
}

void UpdateOriginator::removeUpdateListener(UpdateListener* listener)
{
    list<UpdateListener*>::const_iterator iter;
    for (iter = updateListeners.begin(); iter != updateListeners.end(); ++iter)
    {
        if (*iter == listener)
        {
            listener->notifyRemovedFromOriginator(this);
            updateListeners.remove(listener);
            break;
        }
    }
}
