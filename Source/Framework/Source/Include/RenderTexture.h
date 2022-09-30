/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef RENDERTEXTURE_H_INCLUDED
#define RENDERTEXTURE_H_INCLUDED

#include <string>
#include <list>
#include "dll.h"
#include "RenderOriginator.h"
#include "UpdateOriginator.h"

class RenderListener;
class Camera;

/** This class represents an HGE renderTexture.
* This class acts almost like a sub scene which is why it inherits from both RenderOriginator and UpdateOriginator.
*/
class EXPORT_FRAME RenderTexture : public RenderOriginator, public UpdateOriginator
{
protected:
    ///Name of this RenderTexture.
	std::string name;
	///Handle to the created HGE render target.
	int handle;
	///Simple values for storing the width and height of the render target.
	unsigned int width, height;

public:
    /** Constructor.
    * \param name The name to be associated with the RenderTexture.
    * \param width The width of the render target to be created.
    * \param height The height of the render target to be created.
    * \remark As a general rule, width ans height should both be powers of two since some GPUs are unable to load textures with non-power of two dimensions or they can but at a high performance cost.
    * \remark RenderTextures will only allow for one Camera to be attached to them at a time.
    */
	RenderTexture(std::string name, int width, int height);
	///Deconstructor.
	 ~RenderTexture();

    ///Get the name of the RenderTexture.
	inline std::string getName(){return name;}

    ///Get the width of the RenderTexture.
	inline int getWidth(){return width;}
	///Get the height of the RenderTexture.
	inline int getHeight(){return height;}

    ///Get the handle to the resulting HGE texture.
	int getTexture();

    /**Overriden update method, calls the update method of all registered UpdateListeners.
    * \sa UpdateListener
    */
    void update();
    /** Overriden render method, calls the render method of all registered RenderListeners.
    * The RenderTexture is passed to all RenderableListeners.
    * \sa RenderableListener, RenderOriginator
    */
	void render();
};

#endif
