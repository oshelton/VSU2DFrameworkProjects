/**
* \author Japhett Burt
* \date 2/14/2005
*
* Jack Owen Shelton:
* Framework used in both my CS 3520 and CS 4322 projects.
* I am not the original author of this code.
*/

////////////////////////////////////////////////////////////////////////////////
// HgeTexture.cpp
//
// Created By : Japhett Burt
//
// Date Created : 2/14/2005
//
// Purpose : Used to wrap up the hge texture for CEGUI system
//
////////////////////////////////////////////////////////////////////////////////
#include "HgeTexture.h"
#undef max

// Start of CEGUI namespace section
namespace CEGUI
{

   /*************************************************************************
   Constructor
   *************************************************************************/
   HgeTexture::HgeTexture(Renderer* owner) :
   Texture(owner)
{
   m_hgetexture = NULL;
   hge = HGE::hgeCreate(HGE_VERSION);
}

/*************************************************************************
Destructor
*************************************************************************/
HgeTexture::~HgeTexture(void)
{
   freeHgeTexture();
   hge->Release();
}

/*************************************************************************
Load texture from file.  Texture is made to be same size as image in
file.
*************************************************************************/
void HgeTexture::loadFromFile(const String& filename, const String& resourceGroup)
{
   freeHgeTexture();

   m_hgetexture = hge->Texture_Load(filename.c_str());
   m_width = hge->Texture_GetWidth(m_hgetexture);
   m_height = hge->Texture_GetHeight(m_hgetexture);
}


/*************************************************************************
Load texture from raw memory.
*************************************************************************/
void HgeTexture::loadFromMemory(const void* buffPtr, uint buffWidth, uint buffHeight, PixelFormat format)
{
   //using namespace std;

   freeHgeTexture();

   // calculate square size big enough for whole memory buffer
   uint tex_size = std::max(buffWidth, buffHeight);

   // create a texture
   m_hgetexture = hge->Texture_Create(tex_size, tex_size);

   // store new size;
   m_width = hge->Texture_GetWidth(m_hgetexture);
   m_height = hge->Texture_GetHeight(m_hgetexture);

   //DWORD color = locked_ptr[y*tex_width+x];
   DWORD *locked_ptr = hge->Texture_Lock(m_hgetexture);

   if(locked_ptr)
   {
      ulong* src = (ulong*)buffPtr;
      for (uint y = 0; y < buffHeight; ++y)
      {
         for (uint x = 0; x < buffWidth; ++x)
         {
            locked_ptr[y*m_width+x] = src[x];
         }
         src += buffWidth;
      }


      hge->Texture_Unlock(m_hgetexture);
   }
}


/*************************************************************************
safely release hge texture associated with this Texture
*************************************************************************/
void HgeTexture::freeHgeTexture(void)
{
   if (m_hgetexture != NULL)
   {
      hge->Texture_Free(m_hgetexture);
      m_hgetexture = NULL;
   }

}


/*************************************************************************
allocate a hge texture >= 'size'.  Previous hge texture is lost
*************************************************************************/
void HgeTexture::setHgeTextureSize(uint size)
{
   freeHgeTexture();

   m_hgetexture = hge->Texture_Create(size, size);
    m_width = hge->Texture_GetWidth(m_hgetexture);
   m_height = hge->Texture_GetHeight(m_hgetexture);
}

} // End of  CEGUI namespace section
