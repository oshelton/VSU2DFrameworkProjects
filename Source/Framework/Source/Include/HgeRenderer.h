/**
* \author Japhett Burt
* \date 2/14/2005
*
* Jack Owen Shelton:
* Framework used in both my CS 3520 and CS 4322 projects.
* I am not the original author of this code.
*/

////////////////////////////////////////////////////////////////////////////////
// HgeRenderer.h
//
// Created By : Japhett Burt
//
// Date Created : 2/14/2005
//
// Purpose : Used to hook into the hge render engine
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __HGERENDERER_H__
#define __HGERENDERER_H__

#include <CEGUIBase.h>
#include <CEGUIRenderer.h>
#include <CEGUITexture.h>

#include <list>
#include <set>

class HGE;
struct hgeQuad;

//The original comments have been removed in favor of Doxygen compatible ones - Jack Owen Shelton.
//Start of CEGUI namespace section
namespace CEGUI
{
    class HgeTexture;

    /** This is a special class that bridges the gap between CEGUI and HGE.
    * This class is one of two that must be implemented in order to allow CEGUI to render, the other is the HgeTexture class.
    */
    class HgeRenderer : public Renderer
    {
    public:
        ///Constructor
        HgeRenderer();

        ///Deconstructor
        ~HgeRenderer();

        /** Used to add a quad to the render queue or render it directly depending on the render queue state.
        * \param dest_rect The coordinates the quad is going to be rendered at.
        * \param z The Z coordinate the quad is going to be rendered at.  I have overriden this so that it always renders at z = 0, on top of everything.
        * \param tex The texture UV coordinates of the texture being rendered to use.
        * \param tex Pointer to a CEGUI texture being rendered.
        * \param colours Vertex colors to use when rendering the quad.
        */
        virtual   void addQuad(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode mode);

        ///Rendered all gueued quads.
        virtual   void doRender(void);

        ///Clearthe render queue
        virtual   void clearRenderList(void);

        /** Enable or disable the queueing of quads from this point on.
        *
        * This only affects queueing.  If queueing is turned off, any calls to addQuad will cause the quad to be rendered directly.  Note that
        * disabling queueing will not cause currently queued quads to be rendered, nor is the queue cleared - at any time the queue can still
        * be drawn by calling doRender, and the list can be cleared by calling clearRenderList.  Re-enabling the queue causes subsequent quads
        * to be added as if queueing had never been disabled.
        *
        * \param setting true to enable queueing, or false to disable queueing (see notes above.
        */
        virtual void setQueueingEnabled(bool setting)
        {
            m_bQueueing = setting;
        }


        /** Create a new HgeTexture.
        * \return The newly created HgeTexture.
        */
        virtual   Texture*   createTexture(void);

        /** Create a new HgeTexture.
        * \param filename The filename ofthe texture to load.
        * \param resourceGroup The resource group the created texture should belong to.
        * \return The newly created HgeTexture
        */
        virtual   Texture*   createTexture(const String& filename, const String& resourceGroup);

        /** Create a new HgeTexture
        * \param size The size of the texture.
        * \return The newly created HgeTexture
        */
        virtual   Texture*   createTexture(float size);

        /** Destroy a HgeTexture.
        * \param texture The HgeTexture to be destroyed.
        */
        virtual   void      destroyTexture(Texture* texture);

        ///Destroy all created HgeTextures.
        virtual void      destroyAllTextures(void);

        /** Return whether queueing is enabled.
        * \return true if queueing is enabled, false if queueing is disabled.
        */
        virtual bool   isQueueingEnabled(void) const
        {
            return m_bQueueing;
        }


        /** Return the current width of the display in pixels
        * \return float value equal to the current width of the display in pixels.
        */
        virtual float   getWidth(void) const
        {
            return m_display_area.getWidth();
        }


        /** Return the current height of the display in pixels
        * \return float value equal to the current height of the display in pixels.
        */
        virtual float   getHeight(void) const
        {
            return m_display_area.getHeight();
        }


        /** Return the size of the display in pixels
        * \return Size object describing the dimensions of the current display.
        */
        virtual Size   getSize(void) const
        {
            return m_display_area.getSize();
        }


        /** Return a Rect describing the screen
        * \return A Rect object that describes the screen area.  Typically, the top-left values are always 0, and the size of the area described is equal to the screen resolution.
        */
        virtual Rect   getRect(void) const
        {
            return m_display_area;
        }


        /** Return the maximum texture size available
        * \return Size of the maximum supported texture in pixels (textures are always assumed to be square)
        */
        virtual   uint   getMaxTextureSize(void) const
        {
            return m_uiMaxTextureSize;
        }


        /** Return the horizontal display resolution dpi
        * \return horizontal resolution of the display in dpi.
        */
        virtual   uint   getHorzScreenDPI(void) const
        {
            return 96;
        }


        /** Return the vertical display resolution dpi
        * \return vertical resolution of the display in dpi.
        */
        virtual   uint   getVertScreenDPI(void) const
        {
            return 96;
        }

    private:

        /** Used to render a quad directly to the screen.
        * \param dest_rect The coordinates the quad is going to be rendered at.
        * \param z The Z coordinate the quad is going to be rendered at.  I have overriden this so that it always renders at z = 0, on top of everything.
        * \param tex The texture UV coordinates of the texture being rendered to use.
        * \param tex Pointer to a CEGUI texture being rendered.
        * \param colours Vertex colors to use when rendering the quad.
        */
        void   renderQuadDirect(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours);


        ///Functor class used to insert-sort quads in the Multiset
        class setSorter
        {
        public:
            bool operator()(const hgeQuad* a, const hgeQuad* b) const;
        };

        Rect m_display_area;

        typedef std::multiset<hgeQuad*, HgeRenderer::setSorter > QuadList;
        ///Set of quads that are queued for rendering.
        QuadList m_quadlist;
        ///setting for queueing control.
        bool m_bQueueing;

        ///List used to track textures.
        std::list<HgeTexture*>   m_texturelist;

        ///Holds maximum supported texture size (in pixels).
        uint m_uiMaxTextureSize;

        ///Pointer to the hge interface.
        HGE   *hge;
    };
}

#endif //__HGERENDERER_H__
