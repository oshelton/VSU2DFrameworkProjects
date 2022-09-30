/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef RENDERABLE_H_INCLUDED
#define RENDERABLE_H_INCLUDED

#include <string>
#include <hgevector.h>
#include "dll.h"
#include "Component.h"
#include "RenderableListener.h"
#include "BindableManaged.h"

class SceneNode;
class Camera;

/** Placeholder class for objects that can be drawn on the screen.
* This class uses the Template pattern to render objects.
*/
class EXPORT_FRAME Renderable : public Component, public RenderableListener
{
public:
    ///Required virtual deconstructor.
    virtual ~Renderable(){}

    ///Abstract, get the raw width of the object being drawn on the screen.
    virtual const double getWidth() = 0;
    ///Abstract, get the raw height of the object being drawn on the screen.
    virtual const double getHeight() = 0;

    /** Overriden render method.
	* \sa RenderableListener.
	*/
    void render();
	/** Overriden render method.
	* \param tex This is only used if the SimpleRenderable is listening to a RenderTexture.
	*/
    void render(RenderTexture* const tex);

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    virtual void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam) = 0;
};

#endif // RENDERABLE_H_INCLUDED
