/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef TRIANGLERENDERABLE_H_INCLUDED
#define TRIANGLERENDERABLE_H_INCLUDED

#include <vector>
#include <hgecolor.h>
#include "dll.h"
#include "Renderable.h"

class SceneNode;

///Triangle class that is used as a placeholder for triangles to be rendered, easier than using HGE's own struct
struct Triangle
{
public:
    ///First vertex's coordinate.
    hgeVector vert1;
    ///Second vertex's coordinate.
    hgeVector vert2;
    ///Third vertex's coordinate.
    hgeVector vert3;

    ///First vertex's UV coordinates.
    hgeVector uv1;
    ///Second vertex's UV coordinates.
    hgeVector uv2;
    ///Third vertex's UV coordinates.
    hgeVector uv3;

    ///First vertex's color.
    hgeColor color1;
    ///First vertex's color.
    hgeColor color2;
    ///First vertex's color.
    hgeColor color3;

    ///Texture handle.
    int textureHandle;

    ///Blending mode.
    unsigned short blendMode;
};

///Special class for rendering arbitrary triangles to the screen.
class EXPORT_FRAME TriangleRenderable : public Renderable
{
private:
    ///Vector of triangles to be rendered on the screen.
    std::vector<Triangle*> triangles;

    /** Transform a point from local space to drawing space.
    * \param point The point to translate.
    * \param user The SceneNode to translate the point's space into.
    * \return The hgeVector representing the transformed point.
    */
    const hgeVector transformPoint(hgeVector point, SceneNode* const user);
public:
    /** Constructor.
	* \param name The name of the TriangleRenderable that is going to be created.
	*/
    TriangleRenderable(const std::string& name);

    ///Deconstructor.
    ~TriangleRenderable();

    ///Get the type of the Component.
    const std::string getType()
    {
        return "TriangleRenderable";
    }

    /** Add a new Triangle to be rendered by the TriangleRenderable.
    * \param vert1 The coordinates of the first vertex.
    * \param vert2 The coordinates of the second vertex.
    * \param vert3 The coordinates of the third vertex.
    * \param uv1 The texture coordinates of the first vertex.
    * \param uv2 The texture coordinates of the second vertex.
    * \param uv3 The texture coordinates of the third vertex.
    * \param color1 The color of the first vertex.
    * \param color2 The color of the second vertex.
    * \param color3 The color of the third vertex.
    * \param texture The name of the texture resource to be used..
    * \param blendMode The blending mode to use with the new triangle.
    */
    void addTriangle(const hgeVector& vert1, const hgeVector& vert2, const hgeVector& vert3,
                     const hgeVector& uv1, const hgeVector& uv2, const hgeVector& uv3,
                     const hgeColor& color1, const hgeColor& color2, const hgeColor& color3,
                     const std::string& texture, const int& blendMode = BLEND_DEFAULT_Z);

    /** Add a new Triangle to be rendered by the TriangleRenderable.
    * \param vert1 The coordinates of the first vertex.
    * \param vert2 The coordinates of the second vertex.
    * \param vert3 The coordinates of the third vertex.
    * \param uv1 The texture coordinates of the first vertex.
    * \param uv2 The texture coordinates of the second vertex.
    * \param uv3 The texture coordinates of the third vertex.
    * \param color1 The color of the first vertex.
    * \param color2 The color of the second vertex.
    * \param color3 The color of the third vertex.
    * \param texture The int handle of the texture to be used.
    * \param blendMode The blending mode to use with the new triangle.
    */
    void addTriangle(const hgeVector& vert1, const hgeVector& vert2, const hgeVector& vert3,
                     const hgeVector& uv1, const hgeVector& uv2, const hgeVector& uv3,
                     const hgeColor& color1, const hgeColor& color2, const hgeColor& color3,
                     const int& texture = 0, const int& blendMode = BLEND_DEFAULT_Z);

    ///Get a const reference to the vector containing all of the triangles that will be rendered.
    const std::vector<Triangle*>& getTriangles();

    ///Get the number of triangles in the TriangleRenderable.
    const int getNumberOfTriangles();

    ///Remove all added Triangles.
    void clearTriangles();

    ///Get the width of the Renderable, gets the maximum distance between the x components of the Triangles positions.
    const double getWidth();

    ///Get the height of the Renderable, gets the maximum distance between the y components of the Triangles positions.
    const double getHeight();

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam);
};

#endif // TRIANGLERENDERABLE_H_INCLUDED
