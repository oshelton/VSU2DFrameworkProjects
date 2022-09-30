/**
* \author Jack Owen Shelton
* Framework used in both my CS 3520 and CS 4322 projects.
* \date Spring 2009
*/

#ifndef LINERENDERABLE_H_INCLUDED
#define LINERENDERABLE_H_INCLUDED

#include <vector>
#include <string>
#include <hgevector.h>
#include <hgecolor.h>
#include "Renderable.h"
#include "dll.h"

class SceneNode;

///Simple struct for representing lines.
struct EXPORT_FRAME Line
{
public:
    ///Starting point of the line.
    hgeVector point1;
    ///Ending point of the line.
    hgeVector point2;
    ///Color of the line.
    hgeColor color;

    ///Constructor, for conveniance.
    Line(const hgeVector& point1, const hgeVector& point2, const hgeColor& color)
    {
        this->point1 = point1;
        this->point2 = point2;
        this->color = color;
    }
};

/** Renderable class used for rendering shapes from continuous lines.
* The position, rotation, and scale of any SceneNodes using this Component will be taken into account when rendering.
*/
class EXPORT_FRAME LineRenderable : public Renderable
{
private:
    ///Vector of Lines that are used for rendering.
    std::vector<Line> lines;
    /** Transform a point from local space to drawing space.
    * \param point The point to translate.
    * \param user The SceneNode to translate the point's space into.
    * \return The hgeVector representing the transformed point.
    */
    const hgeVector transformPoint(hgeVector point, SceneNode* const user);
public:
    /** Constructor
    * \param name Name of the LineRenderable to be created.
    */
    LineRenderable(const std::string& name);
    ///Deconstructor.
    ~LineRenderable();

    ///Get the type of the Component.
    const std::string getType()
    {
        return "LineRenderable";
    }

    /** Add a point to create a new line.
    * \param point The origin of the lines, or the end point of the new line.
    */
    void addLine(const hgeVector& point1, const hgeVector& point2, const hgeColor& color);
    ///Get a const reference to the list containing the points.
    const std::vector<Line>& getLines();
    ///Remove all points.
    void clearLines();

    /** Get the width of the shape created by the points.
    * \remark This works by subtracting the smallest x coordinate from the largest.
    */
    const double getWidth();
    /** Get the height of the shape created by the points.
    * \remark This works by subtracting the smallest y coordinate from the largest.
    */
    const double getHeight();

    /** Core render method.
    * The other render methods call this method once it has been determined that the object should be rendered.
    * This is the Template method.
    * \param node The node whose position, rotation, and scale are going to be used to render the object.
    * \param screenPosition The position to render the object at transformed into screen space.
    */
    void render(SceneNode* const node, const hgeVector& screenPosition, Camera* const cam);
};

#endif // LINERENDERABLE_H_INCLUDED
