/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#ifndef TRIANGLESHAPE_H_INCLUDED
#define TRIANGLESHAPE_H_INCLUDED

#include <string>
#include <hgevector.h>

class SceneNode;
class TriangleRenderable;

///Small class representing the converted polygon outline.  Simply used for rendering the results to the screen.
class TriangleShape
{
private:
    ///Pointer to the TriangleRenderable used to render the results to screen.
    TriangleRenderable* triangle;

    ///Main SceneNode the TrangleRenderable is attached to.
    SceneNode* node;

public:
    ///Constructor, sets up triangle.
    TriangleShape(const std::string& name);
    ///Deconstructor.
    ~TriangleShape();

    ///Get a summary of all triangles in the TriangleShape.
    const std::string getSummary();

    /** Add a triangle to the TriangleShape.
    * Random colors are used for the triangles.
    * \param v1 The first vertex.
    * \param v2 The second vertex.
    * \param v3 The third vertex.
    */
    void addTriangle(const hgeVector& v1, const hgeVector& v2, const hgeVector& v3);

    ///Hide the TriangleShape.
    void hide();
    ///Show the TriangleShape.
    void show();

    ///Reset the shape.
    void clearTriangles();
};

#endif // TRIANGLESHAPE_H_INCLUDED
