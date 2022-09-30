/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef SIMPLEDRAWABLE_H_INCLUDED
#define SIMPLEDRAWABLE_H_INCLUDED

#include <hgecolor.h>
#include "dll.h"
#include "Renderable.h"

class SceneNode;
class hgeSprite;

/**Basic Sprite rendering class.
* This class serves as a wrapper for the hgeSprite class.
* \sa Renderable
*/
class EXPORT_FRAME SimpleRenderable : public Renderable
{
protected:
	///Pointer to the hgeSprite which is actually rendered.
    hgeSprite* sprite;

public:
	/** Constructor.
	* \param name The name of the SimpleRenderable that is going to be created.
	*/
    SimpleRenderable(const std::string& name);
	///Deconstructor.
    ~SimpleRenderable();

    ///Get the type of the Component.
    const std::string getType()
    {
        return "SimpleRenderable";
    }

	/** Set the sprite to be used, overrides other settings as needed.
	* \param spriteName The name of the sprite to be used.
	* \remark This method uses the hgeResourceManager which means spriteName must be defined in a loaded resource script before it can be used.
	*/
    void setSprite(const std::string& spriteName);
	/** Set the texture to be applied to the sprite.
	* \param texName The name of the texture to be used.
	* \remark This method uses the hgeResourceManager which means texName must be defined in a loaded resource script before it can be used.
	*/
    void setTexture(const std::string& texName);
	/** Set the texture to be applied to the sprite.
	* \param handle This is the HGE handle to the texture to be used.
	* \param u UV left coordinate to use.
	* \param v UV top coordinate to use.
	* \param width Width of the texture, if this is greater than the actual texture width the texture will be wrapped.
	* \param height Height of the texture, if this is greater than the actual texture height the texture will be wrapped.
	* \remark Right now the only reason this exists is to allow RenderTextures to apply there textures to SimpleRenderables.
	* \sa RenderTexture::getTexture()
	*/
    void setTexture(const int& handle, const float& u, const float& v, const float& width, const float& height);

    ///Get the texture handle used by the sprite.
    int getTexture();

	/** Get the texture coordinates used by the hgeSprite.
	* \param u The pointer to store the u (left) coordinate in.
	* \param v The pointer to store the v (top) coordinate in.
	* \param width The pointer to store the width of the texture region used.
	* \param height The pointer to store the height of the texture region used.
	* \remark All of these values are in image space which regardless to texture dimensions maps from (0, 0) (top left) to (1, 1) (bottom right), values greater than 1 or less than 0 indicate texture wrapping.
	*/
	void getTextureCoords(float* u, float* v, float* width, float* height);
	/** Set the Texture coords used by the hgeSprite.
	* \param u The left coordinate origin of the texture region to use.
	* \param v The top coordinate origin of the texture region to use.
	* \param width The width of the texture region to use.
	* \param height The height of the texture region to use.
	* \remark All of these values are in image space which regardless to texture dimensions maps from (0, 0) (top left) to (1, 1) (bottom right), values greater than 1 or less than 0 indicate texture wrapping.
	*/
	void setTextureCoords(const float& u, const float& v, const float& width, const float& height, const bool& adjustSize = true);

	/** Set the blend mode of the sprite.
	* \param blendMode The blending mode of the sprite.
	*/
    void setBlendMode(const int& blendMode);
	///Get the blending mode currently used by the sprite.
    int getBlendMode();

	/** Set the color by which to tint the sprint.
	* \param color The color the sprite should be tinted with, includes an alpha component.
	*/
    void setColor(const hgeColor& color);
	///Get the color the sprite is being tinted by.
    hgeColor getColor();

	///Get the raw width of the sprite, does not take into account the scale of any users.
    const double getWidth();
	///Get the raw height of the sprite, does not take into account the scale of any users.
    const double getHeight();

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam);
};

#endif // SIMPLEDRAWABLE_H_INCLUDED
