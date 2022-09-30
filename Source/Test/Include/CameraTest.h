#ifndef CAMERATEST_H_INCLUDED
#define CAMERATEST_H_INCLUDED

#include <string>
#include <SystemState.h>

class SceneNode;

class CameraTest : public SystemState
{
private:
    SceneNode* camNode, *sun, *planet1, *planet2, *moon1, *moon2, *moon3, *moon4;

public:
    std::string getName(){ return "CameraTest";}

    void createScene();

    void clear();

    void FrameFunc();
};

#endif // CAMERATEST_H_INCLUDED
