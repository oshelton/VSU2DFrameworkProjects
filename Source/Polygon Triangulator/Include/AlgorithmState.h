/**
* \author Jack Owen Shelton
* CS3520 Project Polygon Triangulator.
* \date Spring 2009
*/

#ifndef ALGORITHMSTATE_H_INCLUDED
#define ALGORITHMSTATE_H_INCLUDED

#include <SystemState.h>

class AlgorithmRunner;
class PointShape;
class TriangleShape;

///SystemState for controlling the Algorithm tests.
class AlgorithmState : public SystemState
{
private:
    ///Pointer to the AlgorithmRunner class that converts objects.
    AlgorithmRunner* runner;
    ///Pointer to the PointShape that is converted.
    PointShape* outline;
    ///Pointer to the object used to store the results of the unoptomized version of the algorithm.
    TriangleShape* triangles1;
    ///Pointer to the object used to store the results of the optomized version of the algorithm.
    TriangleShape* triangles2;

    ///Used to keep track of whether the left mouse button is down, simulates buffered input.
    bool mouseDown;

    ///Constructor.
    AlgorithmState();

    ///Get whether or not the mouse is inside the control window, if it is don't add any points to the outline.
    bool mouseInsideWindow();

    ///Pointer to the singleton instance.
    static AlgorithmState* state;

public:
    ///Deconstructor.
    ~AlgorithmState();

    ///Reset the shapes.
    void reset();

    ///Public method for performing the conversion.
    void performConversion();

    ///Used to get whether or not the outline can be converted.
    bool canConvert();

    ///Get the name of the SimulationState.
    std::string getName(){ return "AlgorithmState";}

    ///Create the scene, start the test.
    void createScene();

    ///Clear the scene, stop the test.
    void clear();

    ///Update function, updates the simulation.
    void FrameFunc();

    static AlgorithmState* get()
    {
        if (state == NULL)
            state = new AlgorithmState;

        return state;
    }
};

#endif // ALGORITHMSTATE_H_INCLUDED
