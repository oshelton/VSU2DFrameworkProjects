/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "UpdateOriginator.h"
#include "RenderTexture.h"
#include "UpdateListener.h"

using namespace std;

void UpdateListener::removeFromUpdateOriginators()
{
    while (listeningTo.size() > 0)
        listeningTo.front()->removeUpdateListener(this);
}
