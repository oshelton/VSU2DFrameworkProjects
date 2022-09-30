/**
* \author Japhett Burt
* \date 2/14/2005
*
* Jack Owen Shelton:
* Framework used in both my CS 3520 and CS 4322 projects.
* I am not the original author of this code.
*/

////////////////////////////////////////////////////////////////////////////////
// HgeRenderer.cpp
//
// Created By : Japhett Burt
//
// Date Created : 2/14/2005
//
// Purpose : Used to hook into the hge render engine
//
////////////////////////////////////////////////////////////////////////////////
#include "HgeRenderer.h"
#include "HgeTexture.h"
#include <hge.h>

using namespace std;

// Start of CEGUI namespace section
namespace CEGUI
{
    ///////////////////////////////////////
    // Function name   : HgeRenderer
    // Description     : Constructor
    ///////////////////////////////////////
    HgeRenderer::HgeRenderer() :
            hge(0),
            m_bQueueing(true),         //Slightly modified by Owen Shelton.
            m_uiMaxTextureSize(1024)
    {
        // get access to the hge interface
        hge = HGE::hgeCreate(HGE_VERSION);

        // get adn the nset our display area rect with the right screen size
        int iScreenWidth = hge->System_GetState(HGE_SCREENWIDTH);
        int iScreenHeight = hge->System_GetState(HGE_SCREENHEIGHT);

        m_display_area.d_left   = 0;
        m_display_area.d_top   = 0;
        m_display_area.d_right   = (float)iScreenWidth;
        m_display_area.d_bottom   = (float)iScreenHeight;

        d_identifierString = "HGE Renderer";
    }


    /*************************************************************************
    Destructor
    *************************************************************************/
    HgeRenderer::~HgeRenderer(void)
    {
        destroyAllTextures();
        hge->Release();
    }


    /*************************************************************************
    add's a quad to the list to be rendered
    *************************************************************************/
    void HgeRenderer::addQuad(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode mode)
    {
        // if not queueing, render directly (as in, right now!)
        if (!m_bQueueing)
        {
            renderQuadDirect(dest_rect, z, tex, texture_rect, colours);
        }
        else
        {
            hgeQuad *quad = new hgeQuad;

            // the posittion and size
            quad->v[0].x        = dest_rect.d_left;
            quad->v[0].y        = dest_rect.d_top;

            quad->v[1].x        = dest_rect.d_right;
            quad->v[1].y        = dest_rect.d_top;

            quad->v[2].x        = dest_rect.d_right;
            quad->v[2].y        = dest_rect.d_bottom;

            quad->v[3].x        = dest_rect.d_left;
            quad->v[3].y        = dest_rect.d_bottom;

            // the z-buffer
            quad->v[0].z      = 0;
            quad->v[1].z      = 0;
            quad->v[2].z      = 0;
            quad->v[3].z      = 0;

            // the texture
            quad->tex           = ((HgeTexture*)tex)->getHgeTexture();

            // the texture coords
            quad->v[0].tx       = texture_rect.d_left;
            quad->v[0].ty       = texture_rect.d_top;

            quad->v[1].tx       = texture_rect.d_right;
            quad->v[1].ty       = texture_rect.d_top;

            quad->v[2].tx       = texture_rect.d_right;
            quad->v[2].ty       = texture_rect.d_bottom;

            quad->v[3].tx       = texture_rect.d_left;
            quad->v[3].ty       = texture_rect.d_bottom;

            // the vertex colors
            quad->v[0].col      = colours.d_top_left.getARGB();
            quad->v[1].col      = colours.d_top_right.getARGB();
            quad->v[2].col       = colours.d_bottom_right.getARGB();
            quad->v[3].col       = colours.d_bottom_left.getARGB();

            // blending
            quad->blend = BLEND_DEFAULT_Z;

            // insert it into the list
            m_quadlist.insert(quad);
        }

    }


    /*************************************************************************
    perform final rendering for all queued renderable quads.
    *************************************************************************/
    void HgeRenderer::doRender(void)
    {
        // iterate over each quad in the list
        for (QuadList::iterator i = m_quadlist.begin(); i != m_quadlist.end(); ++i)
        {
            hge->Gfx_RenderQuad((*i));
        }
    }


    /*************************************************************************
    clear the queue
    *************************************************************************/
    void HgeRenderer::clearRenderList(void)
    {
        while (!m_quadlist.empty())
        {
            delete (*m_quadlist.begin());
            m_quadlist.erase(m_quadlist.begin());
        }
    }


    /*************************************************************************
    create an empty texture
    *************************************************************************/
    Texture* HgeRenderer::createTexture(void)
    {
        HgeTexture* tex = new HgeTexture(this);
        m_texturelist.push_back(tex);

        return tex;
    }


    /*************************************************************************
    Create a new Texture object and load a file into it.
    *************************************************************************/
    Texture* HgeRenderer::createTexture(const String& filename, const String& resourceGroup)
    {
        HgeTexture* tex = (HgeTexture*)createTexture();
        tex->loadFromFile(filename, resourceGroup);

        return tex;
    }


    /*************************************************************************
    Create a new texture with the given dimensions
    *************************************************************************/
    Texture* HgeRenderer::createTexture(float size)
    {
        HgeTexture* tex = (HgeTexture*)createTexture();
        tex->setHgeTextureSize((uint)size);

        return tex;
    }

    /*************************************************************************
    Destroy a texture
    *************************************************************************/
    void HgeRenderer::destroyTexture(Texture* texture)
    {
        if (texture != NULL)
        {
            HgeTexture* tex = (HgeTexture*)texture;
            m_texturelist.remove(tex);
            delete tex;
        }

    }

    // destroy all textures still active
    void HgeRenderer::destroyAllTextures(void)
    {
        while (!m_texturelist.empty())
        {
            destroyTexture(*(m_texturelist.begin()));
        }
    }

    /*************************************************************************
    render a quad directly to the display
    *************************************************************************/
    void HgeRenderer::renderQuadDirect(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours)
    {
        // create it
        static hgeQuad _quad;

        // set it up
        // the posittion and size
        _quad.v[0].x        = dest_rect.d_left;
        _quad.v[0].y        = dest_rect.d_top;

        _quad.v[1].x        = dest_rect.d_right;
        _quad.v[1].y        = dest_rect.d_top;

        _quad.v[2].x        = dest_rect.d_right;
        _quad.v[2].y        = dest_rect.d_bottom;

        _quad.v[3].x        = dest_rect.d_left;
        _quad.v[3].y        = dest_rect.d_bottom;

        // the z-buffer
        _quad.v[0].z      = 0;
        _quad.v[1].z      = 0;
        _quad.v[2].z      = 0;
        _quad.v[3].z      = 0;

        // texture
        _quad.tex           = ((HgeTexture*)tex)->getHgeTexture();

        // the texture coords
        _quad.v[0].tx       = texture_rect.d_left;
        _quad.v[0].ty       = texture_rect.d_top;

        _quad.v[1].tx       = texture_rect.d_right;
        _quad.v[1].ty       = texture_rect.d_top;

        _quad.v[2].tx       = texture_rect.d_right;
        _quad.v[2].ty       = texture_rect.d_bottom;

        _quad.v[3].tx       = texture_rect.d_left;
        _quad.v[3].ty       = texture_rect.d_bottom;

        // the vertex colors
        _quad.v[0].col      = colours.d_top_left.getARGB();
        _quad.v[1].col      = colours.d_top_right.getARGB();
        _quad.v[2].col       = colours.d_bottom_right.getARGB();
        _quad.v[3].col       = colours.d_bottom_left.getARGB();

        // blending
        _quad.blend = BLEND_DEFAULT_Z;

        // render it
        hge->Gfx_RenderQuad(&_quad);
    }

    bool HgeRenderer::setSorter::operator()(const hgeQuad* a, const hgeQuad* b) const
    {
        return a->v[0].z > b->v[0].z;
    }


} // End of  CEGUI namespace section
