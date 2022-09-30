/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#ifndef ALGORITHMRUNNER_H_INCLUDED
#define ALGORITHMRUNNER_H_INCLUDED

#include <vector>
#include <string>
#include <list>
#include <hgevector.h>
#include "CyclicVector.h"

class PointShape;
class TriangleShape;

///Class for running the Ear Clipping triangulation algorithm on a PointShape.
class AlgorithmRunner
{
private:
    /** Recursive method used in the conversion process of the original version of the algorithm.
    * The points must be in clockwise order.
    * \param points The points to process, adjacency is assumed.
    * \param output The TriangleShape to add any cut ears to.
    */
    void processShapeStandard(std::vector<hgeVector>* points, TriangleShape* output);

    /** Non-recursive method used in the conversion process of the optomized version of the algorithm.
    * The points must be in clockwise order.
    * \param points The points to process, adjacency is assumed.
    * \param output The TriangleShape to add any cut ears to.
    */
    void processShapeOptomized(CyclicVector<hgeVector> points, TriangleShape* output);

    /** Test if a vertex is convex, finds the area of the triangle formed, if the sign is - the triangle is convex, it is concave otherwise.
    * This isn't quite the same thing as the real area, which would require the result to be divided by 2.
    * Vertex 2 is the actual vertex to test.
    * \param v1 The first vertex.
    * \param v2 The second vertex, the one actually tested.
    * \param v3 The third vertex.
    */
    bool vertexConvex(const hgeVector& v1, const hgeVector& v2, const hgeVector& v3);

    /** Test if a point is inside a triangle.
    * \param v1 The first vertex of the triangle.
    * \param v2 The second vertex of the triangle.
    * \param v3 The third vertex of the triangle.
    * \param point The point to test.
    */
    bool pointInsideStandard(const hgeVector& v1, const hgeVector& v2, const hgeVector& v3, const hgeVector& point);

    /** Test if a point is inside a triangle, the optomized version that performs a simple bounding box check.
    * \param minCoords The bottom left corner of the ears bounding box.
    * \param maxCoords The top right corner of the ears bounding box.
    * \param v1 The first vertex of the triangle.
    * \param v2 The second vertex of the triangle.
    * \param v3 The third vertex of the triangle.
    * \param point The point to test.
    */
    bool pointInsideOptomized(const hgeVector& minCoords, const hgeVector& maxCoords, const hgeVector& v1, const hgeVector& v2, const hgeVector& v3, const hgeVector& point);

    /** Calculate the bounding box of a set of three vectors, used by the optomized version of the algorithm.
    * \param p1 The first point.
    * \param p2 The second point.
    * \param p3 The third point.
    * \param minOut The hgeVector to place the bottom left corner of the box into.
    * \param maxOut The hgeVector to place the top right corner of the box into.
    */
    void calculateMaxMin(const hgeVector& p1, const hgeVector& p2, const hgeVector& p3, hgeVector& minOut, hgeVector& maxOut);

    /** Check if the passed CyclicVector of points are ordered in a clockwise fashion.
    * \param points The CyclicVector containing the points to check.
    */
    const bool pointsClockwise(CyclicVector<hgeVector> points);

public:
    ///Constructor, creates or erases the report.
    AlgorithmRunner();

    /** Convert a PointShape that represents a closed Polygon into a collection of Triangles.
    * This method uses the original algorithm implementation.
    * \param shape A pointer to the shape to be converted.
    */
    void convertShape(PointShape* shape, TriangleShape* output1, TriangleShape* output2);
};

#endif // ALGORITHMRUNNER_H_INCLUDED
