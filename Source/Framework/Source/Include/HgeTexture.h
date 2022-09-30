/**
* \author Japhett Burt
* \date 2/14/2005
*
* Jack Owen Shelton:
* Framework used in both my CS 3520 and CS 4322 projects.
* I am not the original author of this code.
*/

////////////////////////////////////////////////////////////////////////////////
// HgeTexture.h
//
// Created By : Japhett Burt
//
// Date Created : 2/14/2005
//
// Purpose : Used to wrap up the hge texture for CEGUI system
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __HGETEXTURE_H__
#define __HGETEXTURE_H__

#include <CEGUIBase.h>
#include <CEGUIRenderer.h>
#include <CEGUITexture.h>

#include "HgeRenderer.h"
#include <hge.h>

// Start of CEGUI namespace section
namespace CEGUI
{
    /*!
    \brief
    Texture class that is created by HgeRenderer objects
    */
    class  HgeTexture : public Texture
    {
    private:
        /*************************************************************************
        Friends (to allow construction and destruction)
        *************************************************************************/
        friend   Texture* HgeRenderer::createTexture(void);
        friend   Texture* HgeRenderer::createTexture(const String& filename, const String& resourceGroup);
        friend   Texture* HgeRenderer::createTexture(float size);
        friend   void     HgeRenderer::destroyTexture(Texture* texture);


        /*************************************************************************
        Construction & Destruction (by Renderer object only)
        *************************************************************************/
        HgeTexture(Renderer* owner);
        virtual ~HgeTexture(void);

    public:
        /*!
        \brief
        Returns the current pixel width of the texture

        \return
        ushort value that is the current width of the texture in pixels
        */
        virtual   ushort getWidth(void) const
        {
            return m_width;
        }


        /*!
        \brief
        Returns the current pixel height of the texture

        \return
        ushort value that is the current height of the texture in pixels
        */
        virtual   ushort getHeight(void) const
        {
            return m_height;
        }


        /*!
        \brief
        Loads the specified image file into the texture.  The texture is resized as required to hold the image.

        \param filename
        The filename of the image file that is to be loaded into the texture

        \return
        Nothing.
        */
        virtual void loadFromFile(const String& filename, const String& resourceGroup);


        /*!
        \brief
        Loads (copies) an image in memory into the texture.  The texture is resized as required to hold the image.

        \param buffPtr
        Pointer to the buffer containing the image data

        \param buffWidth
        Width of the buffer (in 0xAARRGGBB pixels)

        \param buffHeight
        Height of the buffer (in 0xAARRGGBB pixels)

        \return
        Nothing.
        */
        virtual void loadFromMemory(const void* buffPtr, uint buffWidth, uint buffHeight, PixelFormat format);


        /*!
        \brief
        Return a pointer to the internal HgeTexture object

        \return
        Pointer to the HTEXTURE currently being used by this Texture object
        */
        HTEXTURE getHgeTexture(void) const
        {
            return m_hgetexture;
        }


        //
        /*!
        \brief
        set the size of the internal hge texture.  Previous hge texture is lost.

        \param size
        pixel size of the new internal texture.  This will be rounded up to a power of 2.

        \return
        Nothing.
        */
        void   setHgeTextureSize(uint size);


    private:

        /*************************************************************************
        Implementation Functions
        *************************************************************************/
        // safely free hge texture (can be called multiple times with no ill effect)
        void   freeHgeTexture(void);


        /*************************************************************************
        Implementation Data
        *************************************************************************/
        HTEXTURE m_hgetexture;      //!< The 'real' texture.

        ushort m_width;         //!< cached width of the texture
        ushort m_height;      //!< cached height of the texture

        // the hge inteface
        HGE *hge;
    };

} // End of  CEGUI namespace section

#endif //__HGETEXTURE_H__
