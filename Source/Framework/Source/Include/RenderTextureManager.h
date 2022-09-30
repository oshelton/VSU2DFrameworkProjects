/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef RENDERTEXTUREMANAGER_H_INCLUDED
#define RENDERTEXTUREMANAGER_H_INCLUDED

#include <string>
#include <map>
#include "dll.h"

class RenderTexture;

///This class serves as a way for managing and creating RenderTextures.
class EXPORT_FRAME RenderTextureManager
{
private:
    ///Map containing pointers to all created RenderTextures.
	std::map<std::string, RenderTexture*> textures;
	///Pointer to the singleton instance of the class.
	static RenderTextureManager* manager;

    ///Constructor.
	RenderTextureManager();

public:
	///Deconstructor.
	~RenderTextureManager();

    /** Create a new RenderTexture.
    * \param name Name of the new RenderTexture.
    * \param width Width of the new RenderTexture.
    * \remark If name is already in use the already existing RenderTexture will be returned.
    */
	RenderTexture* createRenderTexture(std::string name, int width, int height);
	/** Get a RenderTexture.
	* \param name The name of the RenderTexture to be retrieved.
	* \return NULL will be returned if no RenderTexture exists with the name name.
	*/
	RenderTexture* getRenderTexture(std::string name);
	/** Destroy a render Texture.
	* \param name The name of the RenderTexture to destroy.
	*/
	void destroyRenderTexture(std::string name);
	/** Destroy a RenderTexture.
	* \param texture Pointer to the RenderTexture to be destroyed.
	*/
	void destroyRenderTexture(RenderTexture* texture);

    /** Render all the RenderTextures.
    * This method is called by  the SceneManager.
    */
    void renderTextures();

    ///Singleton access method, returns a pointer to the RenderTextureManager.
	static RenderTextureManager* get();
};

#endif
