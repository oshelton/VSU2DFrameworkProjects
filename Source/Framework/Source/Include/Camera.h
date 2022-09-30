/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <hgevector.h>
#include "dll.h"
#include "Component.h"

#include "RenderableListener.h"

class SceneNode;
class RenderTexture;
class HGE;

/** Camera class that represents a view in 2d space.
* The Camera class does little more than translate the render space when render is called.
* The Camera class inherits from Component, but a Camera can only ever be attached to one SceneNode at a time.
* The Camera class can listen to multiple RenderOriginators though, which means it can be used to render the main scene as well as multiple RenderTextures at the same time.
* Cameras are managed through the SceneManager's *Camera methods.
* \sa Component, RenderableListener and SceneManager::createCamera(std::string name)
*/
class EXPORT_FRAME Camera : public Component
{
public:
	/** Constructor
	* /param name Name of the Camera being created.
	*/
    Camera(const std::string& name);
	///Required virtual destructor, removes Camera from its parent (if any) and removes it from any RenderOriginators.
    ~Camera();

	/** Overriden setName method from Component, wraps SceneManager->renameCamera.
	* Wraps SceneManager->renameCamera.
	* \param name New name of the Camera, nothing will change if the name is already in use.
    * \sa SceneManager::renameCamera(std::string oldName, std::string newName)
	*/
	void setName(const std::string& name);

	/** Get the SceneNode the Camera is attached to.
	* \return The SceneNode the Camera is attached to or NULL if it is not attached to anything.
	*/
    SceneNode* getParent();
	/** Notifies the Camera that it has been attached to a SceneNode.
	* This method is overriden from the version defined in Component to allow for only one user at a time.
	* This method is an internal method and should not be called directly.
	* \param node SceneNode the Camera has been attached to.
	*/
    void registerUser(SceneNode* node);

	/** Overriden from Component, retrieve this components type.
	* \return Returns "Camera", the class type of this Component.
	*/
    inline const std::string getType()
    {
        return "Camera";
    }

	///Get the left boundary of the Camera's viewing area.
    const double getLeft(RenderTexture* tex= NULL);
	///Get the top boundary of the Camera's viewing area.
    const double getTop(RenderTexture* tex= NULL);
	///Get the right boundary of the Camera's viewing area.
    const double getRight(RenderTexture* tex= NULL);
	///Get the bottom boundary of the Camera's viewing area.
    const double getBottom(RenderTexture* tex= NULL);
	///Get the actual position that the Camera is centered at.
    const hgeVector getCenter();

	/**Special method used to convert a position into screen space.
	* \param point The point to convert.
	* \remark Subclasses of Renderable need to call this to convert their positions into screen coordinates for rendering.
	*/
	const hgeVector convertToScreenSpace(hgeVector point);
};

#endif // CAMERA_H_INCLUDED
