/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include "RenderOriginator.h"
#include "RenderTexture.h"
#include "RenderableListener.h"

using namespace std;

void RenderableListener::removeFromRenderOriginators()
{
    while (listeningTo.size() > 0)
        listeningTo.front()->removeRenderableListener(this);
}
