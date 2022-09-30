/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#include <hgefont.h>
#include <hgeresource.h>
#include <math.h>
#include <hge.h>
#include "SceneManager.h"
#include "SystemManager.h"
#include "Utils.h"
#include "Camera.h"
#include "SceneNode.h"
#include "RenderTexture.h"
#include "ScriptManager.h"
#include "TextRenderable.h"

using namespace std;

TextRenderable::TextRenderable(const string& name) : font(NULL), fontName(""), alignment(ALIGN_CENTER), text("")
{
    this->name = name;
}

TextRenderable::~TextRenderable()
{
    if (font != NULL)
        delete font;
    removeAllUsers();
    removeFromRenderOriginators();
}

void TextRenderable::setFont(const string& name)
{
    if (ScriptManager::get()->getResourceManager()->GetFont(name.c_str()) == 0)
        Utils::get()->writeToLog("Error, cannot load Font [" + name + "]");
    else
    {
        if (font != NULL)
            delete font;
        hgeFont* tmp = ScriptManager::get()->getResourceManager()->GetFont(name.c_str());
        font = new hgeFont(tmp->getFontName());
        fontName = name;
    }
}

void TextRenderable::setBlendMode(const int& blendMode)
{
    if (font != NULL)
        font->SetBlendMode(blendMode);
}

int TextRenderable::getBlendMode()
{
    if (font != NULL)
        return font->GetBlendMode();
    return 0;
}

void TextRenderable::setColor(const hgeColor& color)
{
    if (font != NULL)
        font->SetColor(color.GetHWColor());
}

hgeColor TextRenderable::getColor()
{
    if (font != NULL)
        return hgeColor(font->GetColor());
    else
        return hgeColor(0, 0, 0, 0);
}

void TextRenderable::setProportion(const float& prop)
{
    if (font != NULL)
        font->SetProportion(prop);
}

float TextRenderable::getProportion()
{
    if (font != NULL)
        return font->GetProportion();
    else
        return 0;
}

void TextRenderable::setTracking(const float& tracking)
{
    if (font != NULL)
        font->SetTracking(tracking);
}

float TextRenderable::getTracking()
{
    if (font != NULL)
        return font->GetTracking();
    else
        return 0;
}

void TextRenderable::setSpacing(const float& spacing)
{
    if (font != NULL)
        font->SetSpacing(spacing);
}

float TextRenderable::getSpacing()
{
    if (font != NULL)
        return font->GetSpacing();
    else
        return 0;
}

const double TextRenderable::getWidth()
{
    if (font != NULL)
        return font->GetStringWidth(text.c_str());
    else
        return 0;
}

const double TextRenderable::getHeight()
{
    if (font != NULL)
    {
        int numLines = 0;
        for (int i = 0; i < text.length(); ++i)
        {
            if (text[i] == '\n')
                ++numLines;
        }

        return numLines * font->GetHeight();
    }
    else
        return 0;
}

void TextRenderable::setText(const string& text)
{
    this->text = text;
}

const string& TextRenderable::getText()
{
    return text;
}

void TextRenderable::setAlignment(const TextAlign& align)
{
    alignment = align;
}

const TextAlign& TextRenderable::getTextAlignment()
{
    return alignment;
}

void TextRenderable::render(SceneNode* const node, const hgeVector& screenPosition, Camera* const  cam)
{
    if (font != NULL)
    {
        font->SetZ(node->getZ());
        font->SetScale(node->getWorldScale());
        font->Render(screenPosition.x, screenPosition.y, alignment, text.c_str());
    }
}
