/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef TEXTRENDERABLE_H_INCLUDED
#define TEXTRENDERABLE_H_INCLUDED

#include <hgecolor.h>
#include "dll.h"
#include "Renderable.h"

class hgeFont;
class SceneNode;
class RenderTexture;

enum TextAlign
{
    ALIGN_LEFT,
    ALIGN_RIGHT,
    ALIGN_CENTER,
};

/** Renderable class that provides functionality for rendering text in the scene.
* \remark This class uses bitmap fonts and HGE's own .fnt format.  A tool is available with the HGE sdk to make generating this file easier.
*/
class EXPORT_FRAME TextRenderable : public Renderable
{
private:
    ///Pointer to the hgeFont that is actually rendered.
    hgeFont* font;

    ///The font being used, kept track of here since there is no way to retrieve it from the font.
    std::string fontName;

    ///Horizontal alignment of the text.
    TextAlign alignment;

    ///The text to be rendered.
    std::string text;

public:
    /** Constructor.
	* \param name The name of the TextRenderable that is going to be created.
	*/
	TextRenderable(const std::string& name);
	///Deconstructor.
	~TextRenderable();

	///Mandatory overriden getType method from Component.
	const std::string getType()
	{
	    return "TextRenderable";
	}

	/** Set the font file to be used by the TextRenderable.
	* \param name The name of the font to be used.
	*/
	void setFont(const std::string& name);
	///Retrieve the font being used.
	const std::string& getFont(){ return fontName; }

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

    /** Set the default width multiplier of the font.
    * \param prop The proportion to use, default is 0.
    */
    void setProportion(const float& prop);
    ///Get the width proportion multiplier.
    float getProportion();

    /** Set the font tracking in pixels.
    * \param tracking The tracking value, can be negative.
    * \remark I really have no idea what this does.
    */
    void setTracking(const float& tracking);
    ///Get the font tracking value.
    float getTracking();

    /** Set the line spacing multiplier.
    * \param spacing The line spacing multiplier to use.
    */
    void setSpacing(const float& spacing);
    ///Get the line spacing multiplier.
    float getSpacing();

    ///Get the pixel width of the font object.
    const double getWidth();
    ///Get the pixel height of the font object.
    const double getHeight();

    /** Set the text to be rendered to the screen.
    * \param text The text to be rendered on screen.
    */
    void setText(const std::string& text);
    ///Get the text to be rendered to the screen.
    const std::string& getText();

    /** Set the horizontal alignment of the text.
    * \param align The horizontal alignment to beused.
    */
    void setAlignment(const TextAlign& align);
    ///Get the text alignment.
    const TextAlign& getTextAlignment();

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam);
};

#endif // TEXTRENDERABLE_H_INCLUDED
