/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#ifndef POINTSHAPE_H_INCLUDED
#define POINTSHAPE_H_INCLUDED

#include <string>
#include <hgevector.h>
#include "CyclicVector.h"

class LineRenderable;

///Class that represents the outline of a polygon.
class PointShape
{
private:
    ///LineRenderable used to draw the outline as it is created.
    LineRenderable* line;

    /**List containing all points in the outline, just for conveniance.
    * A vector is used since in this situation random access will help performance far more than
    */
    CyclicVector<hgeVector> points;

    bool convertable;

public:
    ///Constructor, sets up the LineRenderable.
    PointShape();
    ///Deconstructor.
    ~PointShape();

    ///Get a summary of the PointShape.
    const std::string getSummary();

    /** Add a point to the outline
    * \param point The point to be added to the outline.
    */
    void addPoint(const hgeVector& point);

    ///Get a list containing all points used by the polygonal outline.
    inline CyclicVector<hgeVector> getPoints(){ return points; }

    ///Reset the object.
    void clearPoints();

    ///Finalize the shape, just adds a line between the first and last point and sets convertable to true if it has more than three points.
    void finalize();

    ///Get whether this PointShape can be converted into a TriangleShape.
    inline const bool& isConvertable(){ return convertable; }
};

#endif // POINTSHAPE_H_INCLUDED
