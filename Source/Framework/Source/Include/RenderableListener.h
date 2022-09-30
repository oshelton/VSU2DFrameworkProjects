/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef RENDERABLELISTENER_H_INCLUDED
#define RENDERABLELISTENER_H_INCLUDED

#include <list>
#include "dll.h"

class RenderTexture;
class RenderOriginator;

/** Special class that listens for render messages from RenderOriginators.
* \remark This class fills the role of "Observer" in the observer pattern.
*/
class EXPORT_FRAME RenderableListener
{
private:
    ///List of RenderOriginators this RenderableListener is listening to.
    std::list<RenderOriginator*> listeningTo;

public:
    ///Required virtual deconstructor.
    virtual ~RenderableListener(){}

    /** Notify the RenderableListener that it has been registered to a RenderOriginator.
    * \param origin The RenderOriginator that the RenderableListener was registered with.
    * \remark This is an internal method and should not be called manually.
    */
    inline void notifyAddedToOriginator(RenderOriginator* origin)
    {
        listeningTo.push_back(origin);
    }
    /** Notify the RenderableListener that it has been removed from a RenderOriginator.
    * \param origin The RenderOriginator that the RenderableListener was removed from.
    * \remark This is an internal method and should not be called manually.
    */
    inline void notifyRemovedFromOriginator(RenderOriginator* origin)
    {
        listeningTo.remove(origin);
    }

    ///Get the number of RenderOriginators
    inline const unsigned int getNumberOriginators()
    {
        return listeningTo.size();
    }

    /** Remove the RenderableListener from all of the RenderOriginators that use it.
    * \remark This should be called in the deconstructor of all subclasses of RenderableListener.
    */
    void removeFromRenderOriginators();

    ///Standard render method.
	virtual void render() = 0;
	///Special render method used by RenderTextures.
	virtual void render(RenderTexture* const tex) = 0;
};

#endif // DRAWABLELISTENER_H_INCLUDED
