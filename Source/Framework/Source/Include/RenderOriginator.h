/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef RENDERORIGINATOR_H_INCLUDED
#define RENDERORIGINATOR_H_INCLUDED

#include <list>
#include "dll.h"

class RenderableListener;
class Camera;

/** Special class that handles rendering.
* This class simply provides an interface through which RenderableListeners can be attached and be notified when they need to be rendered.
* \remark This class fills the role of "subject" or "originator" in the Observer pattern.
* \sa RenderableListener
*/
class EXPORT_FRAME RenderOriginator
{
protected:
    ///List of RenderableListeners attached to this RenderOriginator.
    std::list<RenderableListener*> renderListeners;
    ///Camera* attached to the RenderOriginator.
    Camera* cam;

public:
    ///Required virtual deconstructor.
    virtual ~RenderOriginator(){}

    /** Register a new RenderableListener to receive render notifications
    * \param listener The RenderableListener to add.
    * \remark If listener is already registered, this method will not do anything.
    */
    virtual void registerRenderableListener(RenderableListener* listener);

    /** Remove a RenderableListener, it will no longer be notified when the RenderOriginator renders.
    *  \param listener The listener to be removed.
    * \remark If listener is not registered nothing will happen.
    */
    virtual void removeRenderableListener(RenderableListener* listener);

    /** This method removes all registered RenderableListeners.
    * \remark This method should be called in the destructor of any subclasses of RenderOriginator to ensure that all the RenderListeners have been notified of the RenderOriginators destruction.
    */
    inline void removeAllRenderListeners()
    {
        while (renderListeners.size() > 0)
            removeRenderableListener(renderListeners.front());
    }

    /** Assign a Camera to the RenderOriginator.
    * \param cam The Camera to assign, Cameras don't need to know if they are being used or not.
    */
    virtual void assignCamera(Camera* cam)
    {
        this->cam = cam;
    }

    ///Get the Camera assigned to the RenderOriginator or NULL if one has not been assigned.
    virtual Camera* getCamera()
    {
        return cam;
    }

    ///Remove and return the Camera assigned to the RenderOriginator, or NULL if one has not been assigned.
    virtual Camera* removeCamera()
    {
        Camera* cam2 = cam;
        cam = NULL;
        return cam2;
    }

    /** Abstract render method.
    * In most cases simply iterating over the registered RenderableListeners and calling their render methods is enough.
    */
    virtual void render() = 0;
};

#endif // RENDERORIGINATOR_H_INCLUDED
